// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interaction/InteractableComponent.h"
#include "PrintOnInteract2.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TUTORIAL_API UPrintOnInteract2 : public UActorComponent, public IInteractableComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPrintOnInteract2();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual FName GetInteractionIconName() override;
	virtual FName GetInteractionName() override;
	virtual void OnInteract(FInteraction InteractionStruct) override;
};