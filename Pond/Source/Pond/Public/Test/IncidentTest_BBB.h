// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Incident.h"
#include "IncidentTest_BBB.generated.h"

/**
 * 
 */

class UMyTestInteractableComponent;

UCLASS()
class POND_API AIncidentTest_BBB : public AIncident
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* StaticMeshComponent;
	UPROPERTY(EditAnywhere)
	UStaticMesh* StaticMesh;
	
	UMyTestInteractableComponent* InteractableComponent;

public:
	AIncidentTest_BBB();
};
