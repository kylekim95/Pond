// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "WorldSubsystems/WS_Network.h"
#include "WS_UserPreference.generated.h"

UCLASS()
class POND_API UWS_UserPreference : public UWorldSubsystem
{
	GENERATED_BODY()
	
public:
	UWS_UserPreference();
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	virtual void PostInitialize() override;
	virtual void OnWorldBeginPlay(UWorld& InWorld) override;

	void UpdateUserPreferenceVector(TArray<float> Influence, TArray<float> Strength);

	TArray<FString> PreferredIncidents;

private:
	UWS_Network* WS_Network;

	const int NumEmotions = 5;
	//PreferredIncidents list updated if difference is larger than this value
	const float Threshold = 0.25f;
	TArray<float> UserPreferenceVector;
	TArray<float> PrevUserPreferenceVector;

	FHttpRequestCompleteDelegate OnPreferredIncidentsDelegate;
	void OnPreferredIncidents(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnected);
};

USTRUCT(BlueprintType)
struct FPreferredIncidents
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TArray<float> user_state;
};
