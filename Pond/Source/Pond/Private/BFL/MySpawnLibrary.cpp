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

    if(AngleBetween < 45.0f){
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