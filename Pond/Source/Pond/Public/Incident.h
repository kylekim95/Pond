// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Incident.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FActionDelegate, FString, Params);

UENUM(BlueprintType)
enum class ETerminationType : uint8
{
	REGULAR = 0,
	INTERRUPT = 1
};
template<typename T>
struct TResult
{
	ETerminationType TerminationType;
	T Value;
};

UCLASS()
class POND_API AIncident : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	AIncident();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	TPromise<TResult<int>>* Promise;
	bool bCont = true;
	TQueue<FActionDelegate>* ActionSequence;
	TQueue<FString> ActionParams;

public:
	UFUNCTION(BlueprintCallable)
	void EnqueueAction(FActionDelegate ActionDelegate, FString Params);
	UFUNCTION(BlueprintCallable)
	void SetPromiseValue(ETerminationType TerminationType, int Value);
};
