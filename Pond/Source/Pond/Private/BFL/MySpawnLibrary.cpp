// Fill out your copyright notice in the Description page of Project Settings.
#include "BFL/MySpawnLibrary.h"

#include "DrawDebugHelpers.h"
#include "Components/SplineComponent.h"

bool UMySpawnLibrary::WithinPlayerFOV(FVector TargetPosition, FVector PlayerPosition, FVector PlayerForwardVector, UObject* WorldContextObject)
{    
    FVector PToT = TargetPosition - PlayerPosition;
    PToT.Normalize();
    PlayerForwardVector.Normalize();
    
    float AngleBetween = FMath::RadiansToDegrees(FMath::Acos(PToT.CosineAngle2D(PlayerForwardVector)));

    if(AngleBetween < 85.0f / 2.0f){
        FHitResult HitResult;
        WorldContextObject->GetWorld()->LineTraceSingleByChannel(
            HitResult,
            PlayerPosition,
            TargetPosition,
            ECollisionChannel::ECC_PhysicsBody
        );
        if(!HitResult.bBlockingHit)
            return true;
    }
    return false;
}

void UMySpawnLibrary::TessellatePath(USplineComponent* Path, UObject *WorldContextObject)
{   
    //PathFinder defaults Z value to 10.0f above the floor
    for(int j = 0; j < Path->GetNumberOfSplinePoints(); j++){
        FHitResult HitResult;
        WorldContextObject->GetWorld()->LineTraceSingleByChannel(
            HitResult,
            Path->GetTransformAtSplinePoint(j, ESplineCoordinateSpace::World).GetLocation(),
            Path->GetTransformAtSplinePoint(j, ESplineCoordinateSpace::World).GetLocation() + FVector(0, 0, -Path->GetTransformAtSplinePoint(j, ESplineCoordinateSpace::World).GetLocation().Z),
            ECollisionChannel::ECC_PhysicsBody
        );
        if(HitResult.bBlockingHit){
            Path->SetLocationAtSplinePoint(j, HitResult.Location, ESplineCoordinateSpace::World);
        }
    }
    //Path section length is maximum 100.0 units
    for(int j = 0; j < Path->GetNumberOfSplinePoints() - 1; j++){
        float A = Path->GetDistanceAlongSplineAtSplinePoint(j);
        float B = Path->GetDistanceAlongSplineAtSplinePoint(j + 1);
        
        int Cnt = 0;
        while(B - A > 100.0f){
            A = (A + B)/2.0f;
            FVector Temp = Path->GetLocationAtDistanceAlongSpline(A, ESplineCoordinateSpace::World);
            Path->AddSplinePointAtIndex(Temp, j + 1 + Cnt, ESplineCoordinateSpace::World);
            Cnt++;
        }
        j += Cnt;
    }
    //Update tangent fo spline points
    for(int j = 0; j < Path->GetNumberOfSplinePoints() - 1; j++){
        FVector A = Path->GetLocationAtSplinePoint(j, ESplineCoordinateSpace::World);
        FVector B = Path->GetLocationAtSplinePoint(j + 1, ESplineCoordinateSpace::World);
        FVector Diff = B - A; 
        Diff.Normalize();
        Path->SetTangentAtSplinePoint(j, Diff * 75.0f, ESplineCoordinateSpace::World);
        Path->SetTangentAtSplinePoint(j + 1, Diff * 75.0f, ESplineCoordinateSpace::World);
    }
}