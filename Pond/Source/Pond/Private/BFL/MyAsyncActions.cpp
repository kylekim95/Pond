// Fill out your copyright notice in the Description page of Project Settings.
#include "BFL/MyAsyncActions.h"
#include "Engine/LatentActionManager.h"
#include "GameFramework/MovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/ShapeComponent.h"
#include "DrawDebugHelpers.h"

void UMyAsyncActions::LatentActorMovement(
    UObject *WorldContext, 
    FLatentActionInfo LatentInfo, 
    ELatentActionInputPins InputPins, 
    ELatentActionOutputPins &OutputPins,
    TArray<FVector>& PathPoints,
    AActor* ActorToMove,
    bool& Grounded,
    float& Velocity
)
{
    UWorld* World = GEngine->GetWorldFromContextObject(WorldContext, EGetWorldErrorMode::ReturnNull);
    if(World == nullptr){
        UE_LOG(LogTemp, Error, TEXT("UMyAsyncActions::LatentActorMovement : Invalid World"));
        return;
    }
    FLatentActionManager& LatentActionManager = World->GetLatentActionManager();
    FLatentActorMovement* ExistingAction = LatentActionManager.FindExistingAction<FLatentActorMovement>(LatentInfo.CallbackTarget, LatentInfo.UUID);
    if(InputPins == ELatentActionInputPins::Start){
        if(ExistingAction == nullptr){
            FLatentActorMovement* Action = new FLatentActorMovement(
                World, LatentInfo, OutputPins, PathPoints, ActorToMove, Grounded, Velocity
            );
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID, Action);
        }
    }
    else if(InputPins == ELatentActionInputPins::Interrupt){
        if(ExistingAction != nullptr){
            ExistingAction->bInterrupt = true;
        }
    }
}

float AdjacentVacantSphereRadius(UWorld* World, bool Grounded, FVector Location, float _MaxRadius, float _MinRadius, float Tolerance){
    float MaxRadius = _MaxRadius;
    float MinRadius = _MinRadius;
    float Radius = (MaxRadius + MinRadius) / 2.0f;
    bool Cont = true;
    while(Cont){
        FHitResult HitResult;
        FCollisionShape CollisionShape;
        Radius = (MaxRadius + MinRadius) / 2.0f;
        CollisionShape.SetSphere(Radius);
        World->SweepSingleByChannel(
            HitResult,
            Location, Location, FQuat::Identity,
            Grounded ? ECollisionChannel::ECC_WorldStatic : ECollisionChannel::ECC_PhysicsBody,
            CollisionShape
        );
        if(HitResult.bBlockingHit)
            MaxRadius = Radius;
        else{
            if(MaxRadius - MinRadius <= Tolerance)
                Cont = false;
            MinRadius = Radius;
        }
    }
    return Radius;
}

bool PassedPlane(FVector Normal, FVector PointOnPlane, FVector LocationToTest){
    float Constant = -FVector::DotProduct(Normal, PointOnPlane);
    float Eval = FVector::DotProduct(Normal, LocationToTest) + Constant;
    return Eval >= -0.001f;
}

float PointToPlaneDistance(FVector Point, FVector PlaneNormal, FVector PointOnPlane){
    float D = -FVector::DotProduct(PlaneNormal, PointOnPlane);
    return (FMath::Abs(FVector::DotProduct(PlaneNormal, Point) + D) / PlaneNormal.Length());
}

void FLatentActorMovement::UpdateOperation(FLatentResponse &Response)
{
    if(bInterrupt){
        Output = ELatentActionOutputPins::OnInterrupted;
        Response.FinishAndTriggerIf(true, LatentActionInfo.ExecutionFunction, LatentActionInfo.Linkage, LatentActionInfo.CallbackTarget);
        return;
    }
    if(bInit){
        bInit = false;
        for(int i = 1; i < PathPoints.Num() - 1; i++){
            FVector Previous = PathPoints[i - 1];
            FVector Current = PathPoints[i];
            FVector Next = PathPoints[i + 1];

            FVector PToCDir = Current - Previous;
            float PToCDist = PToCDir.Length();
            PToCDir.Normalize();
            FVector CToNDir = Next - Current;
            float CToNDist = CToNDir.Length();
            CToNDir.Normalize();
            
            float Radius = FMath::Clamp(AdjacentVacantSphereRadius(World, Grounded, Current, (PToCDist > CToNDist ? CToNDist : PToCDist), 0.0f, 50.0f), 50.0f, 500.0f);
            BoundarySpheres.Add(FBoundarySphere(Current, Radius, Current - PToCDir * Radius, PToCDir, Current + CToNDir * Radius, CToNDir));
        }
        //DEBUG
        #if WITH_EDITOR
        for(int i = 0; i < BoundarySpheres.Num(); i++){
            DrawDebugSphere(World, BoundarySpheres[i].Center, BoundarySpheres[i].Radius, 20, FLinearColor(0.0f, 1.0f, 0.0f, 0.5f).ToFColor(true), true);
            DrawDebugSolidPlane(
                World, 
                FPlane(BoundarySpheres[i].EntranceLocation, BoundarySpheres[i].EntranceNormal), 
                BoundarySpheres[i].EntranceLocation, FVector2D(25.0f, 25.0f),
                FLinearColor(1.0f, 0.0f, 0.0f, 0.5f).ToFColor(true),
                true
            );
            DrawDebugSolidPlane(
                World, 
                FPlane(BoundarySpheres[i].ExitLocation, BoundarySpheres[i].ExitNormal), 
                BoundarySpheres[i].ExitLocation, FVector2D(25.0f, 25.0f),
                FLinearColor(0.0f, 0.0f, 1.0f, 0.5f).ToFColor(true),
                true  
            );
        }
        #endif
        Output = ELatentActionOutputPins::OnStarted;
        Response.TriggerLink(LatentActionInfo.ExecutionFunction, LatentActionInfo.Linkage, LatentActionInfo.CallbackTarget);
        return;
    }    
    float DeltaTime = Response.ElapsedTime();
    FVector CurrentLocation = ActorToMove->GetActorLocation();
    FVector CurrentForward = ActorToMove->GetActorRightVector();
    if(TargetPointIndex >= PathPoints.Num()){
        Output = ELatentActionOutputPins::OnCompleted;
        Response.FinishAndTriggerIf(true, LatentActionInfo.ExecutionFunction, LatentActionInfo.Linkage, LatentActionInfo.CallbackTarget);
        return;
    }
    if(bWithinBoundary){
        if(PassedPlane(BoundarySpheres[TargetPointIndex].ExitNormal, BoundarySpheres[TargetPointIndex].ExitLocation, ActorToMove->GetActorLocation())){
            bWithinBoundary = false;
            TargetPointIndex++;
        }
        else{
            //Yaw
            FVector StartForward = BoundarySpheres[TargetPointIndex].EntranceNormal;
            FVector TargetForward = BoundarySpheres[TargetPointIndex].ExitNormal;
            FVector StartRight = FVector::CrossProduct(FVector::UpVector, StartForward); StartRight.Normalize();
            FVector StartUp = FVector::CrossProduct(StartForward, StartRight); StartUp.Normalize();
            FVector TargetRight = FVector::CrossProduct(FVector::UpVector, TargetForward); TargetRight.Normalize();
            FVector TargetUp = FVector::CrossProduct(TargetForward, TargetRight); TargetUp.Normalize();
            
            //This only works for Yaw
            FVector StartForwardXY = StartForward;
            StartForwardXY.Z = 0; StartForwardXY.Normalize();
            FVector TargetForwardXY = TargetForward;
            TargetForwardXY.Z = 0; TargetForwardXY.Normalize();
            FQuat StartRotationYaw = FQuat::FindBetweenNormals(FVector::RightVector, StartForwardXY);
            FQuat TargetRotationYaw = FQuat::FindBetweenNormals(FVector::RightVector, TargetForwardXY);
            StartRotationYaw = FQuat(0, 0, StartRotationYaw.Z, StartRotationYaw.W); StartRotationYaw.Normalize();
            TargetRotationYaw = FQuat(0, 0, TargetRotationYaw.Z, TargetRotationYaw.W); TargetRotationYaw.Normalize();
            float CurrentDistance = PointToPlaneDistance(
                CurrentLocation,
                FVector::CrossProduct(TargetForwardXY, FVector::UpVector),
                BoundarySpheres[TargetPointIndex].ExitLocation
            );
            float MaxDistance = PointToPlaneDistance(
                BoundarySpheres[TargetPointIndex].EntranceLocation,
                FVector::CrossProduct(TargetForwardXY, FVector::UpVector),
                BoundarySpheres[TargetPointIndex].ExitLocation
            );
            float YawAlpha = FMath::Clamp(1 - (CurrentDistance / MaxDistance), 0.0f, 1.0f);
            FQuat CurrentRotationYaw = FQuat::FastLerp(StartRotationYaw, TargetRotationYaw, YawAlpha);

            //Pitch
            FVector StartGlobalForward = FVector::CrossProduct(StartRight, FVector::UpVector); StartGlobalForward.Normalize();
            FVector TargetGlobalForward = FVector::CrossProduct(TargetRight, FVector::UpVector); TargetGlobalForward.Normalize();
            FVector CrossStarts = FVector::CrossProduct(StartForward, StartGlobalForward);
            FVector CrossTargets = FVector::CrossProduct(TargetForward, TargetGlobalForward);
            float StartRotationPitch = FMath::RadiansToDegrees(FMath::Asin(CrossStarts.Length()));
            float TargetRotationPitch = FMath::RadiansToDegrees(FMath::Asin(CrossTargets.Length()));
            CrossStarts.Normalize(); CrossTargets.Normalize();
            if(StartRight.Equals(CrossStarts)){
                StartRotationPitch *= -1.0f;
            }
            if(TargetRight.Equals(CrossTargets)){
                TargetRotationPitch *= -1.0f;
                TargetUp *= -1.0f;
            }
            FRotator StartRotator(0.0f, 0.0f, StartRotationPitch);
            FRotator TargetRotator(0.0f, 0.0f, TargetRotationPitch);
            CurrentDistance = PointToPlaneDistance(
                CurrentLocation,
                TargetUp,
                BoundarySpheres[TargetPointIndex].ExitLocation
            );
            MaxDistance = PointToPlaneDistance(
                BoundarySpheres[TargetPointIndex].EntranceLocation,
                TargetUp,
                BoundarySpheres[TargetPointIndex].ExitLocation
            );
            float PitchAlpha = FMath::Clamp(1 - (CurrentDistance / MaxDistance), 0.0f, 1.0f);
            FRotator PitchResult = FMath::Lerp(StartRotator, TargetRotator, PitchAlpha);

            ActorToMove->SetActorRotation(CurrentRotationYaw * PitchResult.Quaternion());
        }
        ActorToMove->SetActorLocation(CurrentLocation + ActorToMove->GetActorRightVector() * Velocity * DeltaTime);
    }
    else{
        if(TargetPointIndex >= BoundarySpheres.Num()){
            FVector Direction = PathPoints[TargetPointIndex + 1] - CurrentLocation;
            Direction.Normalize();
            ActorToMove->SetActorLocation(CurrentLocation + Direction * Velocity * DeltaTime);
            if(ActorToMove->GetActorLocation().Equals(PathPoints[TargetPointIndex + 1])){
                TargetPointIndex++;
            }
        }
        else if(PassedPlane(BoundarySpheres[TargetPointIndex].EntranceNormal, BoundarySpheres[TargetPointIndex].EntranceLocation, ActorToMove->GetActorLocation())){
            bWithinBoundary = true;
        }
        else{
            FVector Direction = BoundarySpheres[TargetPointIndex].EntranceLocation - CurrentLocation;
            Direction.Normalize();
            ActorToMove->SetActorLocation(CurrentLocation + Direction * Velocity * DeltaTime);
        }
    }
    Output = ELatentActionOutputPins::OnUpdated;
    Response.TriggerLink(LatentActionInfo.ExecutionFunction, LatentActionInfo.Linkage, LatentActionInfo.CallbackTarget);
    return;
}