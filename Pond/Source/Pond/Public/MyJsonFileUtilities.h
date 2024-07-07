// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "WorldSubsystems/WS_Position.h"
#include "MyJsonFileUtilities.generated.h"

/**
 * 
 */

UCLASS()
class POND_API UMyJsonFileUtilities : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
	UFUNCTION(BlueprintCallable, Category = "FileIO")
	static void LoadJsonFromFilePath(TArray<FSpawnableLocationDescription>& Output, FString FilePath);
	UFUNCTION(BlueprintCallable, Category = "FileIO")
	static void SaveJsonToFilePath(TArray<FSpawnableLocationDescription> Input, FString FilePath);
};