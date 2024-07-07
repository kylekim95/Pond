// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "WS_Position.generated.h"

USTRUCT(BlueprintType)
struct FSpawnableLocationDescription
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector position;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> tags;
};

UCLASS()
class POND_API UWS_Position : public UWorldSubsystem
{
	GENERATED_BODY()
	
public:
	UWS_Position();
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	//QueryStr example: "( ( Occluded & Water ) | Hidden )"
	void Query(TSet<FVector>& Output, FString QueryStr);

private:
	const FString FilePath = "HelloWorld.json";
	TArray<FSpawnableLocationDescription> SpawnableLocations;
	TMap<FString, FVector> IdToVector;
	TMap<FString, TSet<FString>> LocationsByTag;
};
