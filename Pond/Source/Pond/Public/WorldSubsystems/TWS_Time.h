// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "TWS_Time.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FNotifyTimeDelegate, float, Time);

USTRUCT(BlueprintType)
struct FIncident_Time : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	float SpawnableTimeStart;
	UPROPERTY(EditAnywhere)
	float SpawnableTimeEnd;
};

UCLASS()
class POND_API UTWS_Time : public UTickableWorldSubsystem
{
	GENERATED_BODY()
	
public:
	UTWS_Time();
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	virtual void Tick(float DeltaTime) override;
	virtual TStatId GetStatId() const override;

	UPROPERTY(BlueprintAssignable)
	FNotifyTimeDelegate NotifyTimeDelegate;

private:
	UDataTable* DT_Incidents_Time;
	float Time = 0.0f;
	float TimeSpeed = 0.25f;
	
	TMap<FString, bool> Spawnable;
	TArray<TTuple<float, FString>> StartTimes;
	TArray<TTuple<float, FString>> EndTimes;
	int StartTimesInd = 0;
	int EndTimesInd = 0;
};
