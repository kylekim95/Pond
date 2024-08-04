// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MySpawnLibrary.generated.h"

/**
 * 
 */
UCLASS()
class POND_API UMySpawnLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
	UFUNCTION(BlueprintCallable, Category="Spawner", meta = (WorldContext = "WorldContextObject"))
	static bool WithinPlayerFOV(FVector TargetPosition, FVector PlayerPosition, FVector PlayerForwardVector, UObject* WorldContextObject);
	UFUNCTION(BlueprintCallable, Category="Spawner", meta = (WorldContext = "WorldContextObject"))
	static void TessellatePath(USplineComponent* Path, UObject* WorldContextObject);
};
