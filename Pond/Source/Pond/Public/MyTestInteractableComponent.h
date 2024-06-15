// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MyInteractable.h"
#include "MyTestInteractableComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class POND_API UMyTestInteractableComponent : public UActorComponent, public IMyInteractable
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMyTestInteractableComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void _OnInteract(AActor* Interactable) override;
};
