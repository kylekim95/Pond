// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractableComponent.generated.h"

USTRUCT()
struct FInteraction{
	GENERATED_BODY()
	FName InteractionType;
	AActor* Interactor;
};

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInteractableComponent : public UInterface
{
	GENERATED_BODY()
};

class POND_API IInteractableComponent
{
	GENERATED_BODY()
public:
	virtual FName GetInteractionIconName() = 0;
	virtual FName GetInteractionName() = 0;
	virtual void OnInteract(FInteraction InteractionStruct) = 0;
};
