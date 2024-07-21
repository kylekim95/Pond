// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "WS_Spawner.generated.h"

USTRUCT(BlueprintType)
struct FIncident_Type : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FString Description;
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> ActorToSpawn;
	UPROPERTY(EditAnywhere)
	TArray<FString> SpawnablePositionTags;
};

UCLASS()
class POND_API UWS_Spawner : public UWorldSubsystem
{
	GENERATED_BODY()
	
public:
	UWS_Spawner();
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	void OnWorldBeginPlay(UWorld& InWorld) override;

private:
	UDataTable* DT_Incidents_Type;
	TMap<FString, TSubclassOf<AActor>> AtoSMap;
	TMap<FString, TArray<FString>> TagsMap;
};
