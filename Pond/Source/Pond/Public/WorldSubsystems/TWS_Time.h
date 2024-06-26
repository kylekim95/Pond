// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "TWS_Time.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FNotifyTimeDelegate, float, Time);

UCLASS()
class POND_API UTWS_Time : public UTickableWorldSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	virtual void Tick(float DeltaTime) override;
	virtual TStatId GetStatId() const override;
	float GetCurrentTime();

	//Only if you need constant notifications
	UPROPERTY(BlueprintAssignable)
	FNotifyTimeDelegate NotifyTimeDelegate;

private:
	float Timer;
	float TimerSpeedMultiplier;
};
