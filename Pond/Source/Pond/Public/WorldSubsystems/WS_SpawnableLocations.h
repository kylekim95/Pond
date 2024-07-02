// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "WS_SpawnableLocations.generated.h"

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
class POND_API UWS_SpawnableLocations : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	UWS_SpawnableLocations();
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	TSet<FSpawnableLocationDescription*> Query(FString QueryStr);

private:
	const FString FilePath = "HelloWorld.json";

	TArray<FSpawnableLocationDescription> SpawnableLocations;
	TMap<unsigned long long, TSet<FSpawnableLocationDescription*>> SetMap;
	TMap<FString, unsigned long long> MemHash;

	unsigned long long HashFunction(FString str);
	const unsigned long long Capacity = 1000;
};