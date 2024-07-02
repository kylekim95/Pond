// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "WorldSubsystems/WS_Network.h"
#include "WorldSubsystems/WS_SpawnableLocations.h"
#include "WS_IncidentSpawner.generated.h"

//Processed data for ease of spawn
USTRUCT(BlueprintType)
struct FIncidentsSpawnData
{
	GENERATED_BODY()

	bool TempPlaceholder = false;
};

UCLASS()
class POND_API UWS_IncidentSpawner : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	UWS_IncidentSpawner();
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	virtual void PostInitialize() override;
	virtual void OnWorldBeginPlay(UWorld& InWorld) override;

	void UpdateUserState(TArray<float> Target, TArray<float> Influence);

private:
	UDataTable* IncidentsRawDataTable;
	UWS_Network* WS_Network;
	UWS_SpawnableLocations* WS_SpawnableLocations;
	TMap<FString, FIncidentsSpawnData> IncidentsSpawnDataMap;
	TArray<float> UserState;
	TArray<float> PrevUserState;
    TArray<TTuple<FString, double>> Candidates;

	FHttpRequestCompleteDelegate OnGetIncidentsDelegate;
	void OnGetIncidents(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnected);
	FHttpRequestCompleteDelegate OnNewIncidentDelegate;
	void OnNewIncident(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnected);
	FHttpRequestCompleteDelegate OnClosestNeighborDelegate;
	void OnClosestNeighbor(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnected);
};

//Raw data from Incident creator
USTRUCT(BlueprintType)
struct FIncidentsRawData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FString Description;
	UPROPERTY(EditAnywhere)
	float SpawnableTimeStart;
	UPROPERTY(EditAnywhere)
	float SpawnableTimeEnd;
	UPROPERTY(EditAnywhere)
	FString SpawnableLocationTags;
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> ActorToSpawn;
};

//HTTP 'new_incident' POST request JSON struct
USTRUCT(BlueprintType)
struct FNewIncident
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FString name;
	UPROPERTY(EditAnywhere)
	FString description;
};

//HTTP 'closest_neighbor' POST request JSON struct
USTRUCT(BlueprintType)
struct FClosestNeighbor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TArray<float> user_state;
};