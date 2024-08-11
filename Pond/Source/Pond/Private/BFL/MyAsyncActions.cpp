// Fill out your copyright notice in the Description page of Project Settings.
#include "BFL/MyAsyncActions.h"
#include "Engine/LatentActionManager.h"
#include "GameFramework/MovementComponent.h"
#include "DrawDebugHelpers.h"

void UMyAsyncActions::LatentActorMovement(
    UObject *WorldContext, 
    FLatentActionInfo LatentInfo, 
    ELatentActionInputPins InputPins, 
    ELatentActionOutputPins &OutputPins,
    const TArray<FVector>& Path,
    AActor* Actor,
    TArray<FVector>& BoundaryNormals,
    TArray<FVector>& PointsOnBoundary,
    float& CurrentVelocity
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
                LatentInfo, OutputPins, World, Path, Actor, BoundaryNormals, PointsOnBoundary, CurrentVelocity
            );
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID, Action);
        }
    }
    else if(InputPins == ELatentActionInputPins::Cancel){
        if(ExistingAction != nullptr){
            ExistingAction->bCancel = true;
        }
    }
}

bool PassedPlane(FVector Normal, FVector PointOnPlane, FVector LocationToTest){
    float Constant = -FVector::DotProduct(Normal, PointOnPlane);
    float Eval = FVector::DotProduct(Normal, LocationToTest) + Constant;
    return Eval >= -0.001f;
}

void FLatentActorMovement::UpdateOperation(FLatentResponse &Response)
{
    if(bCancel){
        Output = ELatentActionOutputPins::OnCancelled;
        Response.FinishAndTriggerIf(true, LatentActionInfo.ExecutionFunction, LatentActionInfo.Linkage, LatentActionInfo.CallbackTarget);
        return;
    }
    if(bInit){
        bInit = false;
        //INIT Boundary plane
        BoundaryNormals.Add(Path[1] - Path[0]);
        BoundaryNormals[0].Normalize();
        PointsOnBoundary.Add(Path[0]);
        for(int i = 1; i < Path.Num() - 1; i++){
            FVector Previous = Path[i - 1];
            FVector Current = Path[i];
            FVector Direction = Current - Previous;
            Direction.Normalize();
            BoundaryNormals.Add(Direction);
            PointsOnBoundary.Add(
                (((Current - Previous).Length() > TurnDistance) ? Path[i] - Direction * TurnDistance : (Path[i - 1]))
            );
        }
        int LastIndex = Path.Num() - 1;
        BoundaryNormals.Add(Path[LastIndex] - Path[LastIndex - 1]);
        BoundaryNormals[0].Normalize();
        PointsOnBoundary.Add(Path[LastIndex]);

        FVector CurrentForward = Actor->GetActorForwardVector();
        FVector TargetForward = BoundaryNormals[0];
        FRotator DeltaRotation(FQuat::FindBetweenNormals(CurrentForward, TargetForward));
        DeltaRotation.Add(0, -90.0f, 0);
        Actor->AddActorLocalRotation(DeltaRotation);

        Output = ELatentActionOutputPins::OnStarted;
        Response.TriggerLink(LatentActionInfo.ExecutionFunction, LatentActionInfo.Linkage, LatentActionInfo.CallbackTarget);
        return;
    }
    
    float DeltaTime = Response.ElapsedTime();
    if(PassedPlane(BoundaryNormals[TargetPointIndex], PointsOnBoundary[TargetPointIndex], Actor->GetActorLocation())){
        TargetPointIndex++;
        if(TargetPointIndex >= Path.Num()){
            CurrentVelocity = 0;
            Output = ELatentActionOutputPins::OnCompleted;
            Response.FinishAndTriggerIf(true, LatentActionInfo.ExecutionFunction, LatentActionInfo.Linkage, LatentActionInfo.CallbackTarget);
            return;
        }
    }
    else{
        FVector PointOnLine = Path[TargetPointIndex - 1];
        FVector PointOnLine2 = Path[TargetPointIndex];
        FVector A = PointOnLine2 - PointOnLine;
        A.Normalize();

        FVector PointOutOfLine = Actor->GetActorLocation();
        FVector B = PointOutOfLine - PointOnLine;
        float Distance = FVector::CrossProduct(B, A).Length();
        
        FVector PointOutOfLine2 = PointsOnBoundary[TargetPointIndex - 1];
        FVector B2 = PointOutOfLine2 - PointOnLine;
        float Distance2 = FVector::CrossProduct(B2, A).Length();

        float RotationAlpha = FMath::Clamp(1.0f - (Distance / Distance2), 0.0f, 1.0f);

        FQuat StartRotation = FQuat::FindBetweenNormals(FVector::RightVector, BoundaryNormals[TargetPointIndex - 1]);
        FQuat TargetRotation = FQuat::FindBetweenNormals(FVector::RightVector, BoundaryNormals[TargetPointIndex]);
        Actor->SetActorRotation(FQuat::FastLerp(StartRotation, TargetRotation, RotationAlpha));

        CurrentVelocity = MaxVelocity;
        // if(TargetPointIndex == Path.Num() - 1){
        //     float VelocityAlpha = 1 - (PointsOnBoundary[TargetPointIndex] - Actor->GetActorLocation()).Length() / (PointsOnBoundary[TargetPointIndex] - Path[TargetPointIndex - 1]).Length();
        //     CurrentVelocity = FMath::Lerp(MaxVelocity, 0.0f, VelocityAlpha);
        // }

        FVector NewLocation = Actor->GetActorLocation() + Actor->GetActorRightVector() * CurrentVelocity * DeltaTime;

        //FIX LOCATION AND ROTATION.PITCH
        FHitResult HitResult;
        World->LineTraceSingleByChannel(
            HitResult,
            FVector(NewLocation.X, NewLocation.Y, 10000.0f),
            FVector(NewLocation.X, NewLocation.Y, -10000.0f),
            ECollisionChannel::ECC_PhysicsBody
        );
        if(HitResult.bBlockingHit){
            NewLocation = HitResult.Location;
        }
        Actor->SetActorLocation(NewLocation);
    }
}