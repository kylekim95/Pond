// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MyJsonFileUtilities.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FSpawnableLocationDescription
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector position;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> tags;
};

UCLASS()
class POND_API UMyJsonFileUtilities : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
	UFUNCTION(BlueprintCallable, Category = "FileIO")
	static void LoadJsonFromFilePath(TArray<FSpawnableLocationDescription>& Output, FString FilePath);
	UFUNCTION(BlueprintCallable, Category = "FileIO")
	static void SaveJsonToFilePath(TArray<FSpawnableLocationDescription> Input, FString FilePath);
};