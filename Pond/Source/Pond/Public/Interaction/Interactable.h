// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interaction/InteractableComponent.h"
#include "Interactable.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class POND_API UInteractable : public UActorComponent
{
	GENERATED_BODY()

	TMap<FName, IInteractableComponent*> InteractableComponentMap;

public:	
	// Sets default values for this component's properties
	UInteractable();
	void Interact(FInteraction InteractionStruct);
	TArray<FName> GetInteractOptionIcons();
	TArray<FName> GetInteractOptions();
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
};
