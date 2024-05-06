// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIC_DEM.generated.h"

/**
 * 
 */

class UBehaviorTree;

UCLASS()
class POND_API AAIC_DEM : public AAIController
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=AI, meta=(AllowPrivateAccess = "true"))
	UBehaviorTree* BT_DEM;

public:
	virtual void BeginPlay() override;

	// UFUNCTION(BlueprintCallable)
	// void HelloWorld();
};
