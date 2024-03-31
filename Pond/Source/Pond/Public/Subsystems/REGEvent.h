// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "REGEvent.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FInfluence
{
	GENERATED_USTRUCT_BODY()

	FString Tag = "";
	float Strength = 0.0f;

	FInfluence(){}
	FInfluence(FString _Tag, float _Strength){
		Tag = _Tag;
		Strength = _Strength;
	}
};

UCLASS()
class POND_API UREGEvent : public UObject
{
	GENERATED_BODY()

public:
	FString Name = "PlaceHolder";
	virtual float GetScore(TMap<FString, float> Environment);
	virtual void Invoke();
	TArray<FInfluence> InfluencedBy;
	TArray<FInfluence> InfluenceWorldBy;
};
