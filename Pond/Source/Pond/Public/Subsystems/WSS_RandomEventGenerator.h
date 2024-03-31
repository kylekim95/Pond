// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "REGEvent.h"
#include "WSS_RandomEventGenerator.generated.h"

/**
 * 
 */

UCLASS()
class POND_API UWSS_RandomEventGenerator : public UWorldSubsystem
{
	GENERATED_BODY()
	
public:
	//	USubsystem
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    virtual void Deinitialize() override;
	//	~USubsystem

	//Gives the subsystem information used to determine which events should be invoked
	UFUNCTION(BlueprintCallable)
	void Notify(TArray<FInfluence> Incidents);
	void Assess();

	UFUNCTION(BlueprintCallable)
	void AddEvent(UREGEvent* NewEvent);

private:
	TMap<FString, float> Environment;
	TMap<FString, UREGEvent*> Events;
	TMap<FString, float> InvokeMeter;

	FTimerHandle TimerHandle;

	UREGEvent* Test;
	UREGEvent* Test12;
};