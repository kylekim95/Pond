// Fill out your copyright notice in the Description page of Project Settings.
#include "Interaction/Interactable.h"

// Sets default values for this component's properties
UInteractable::UInteractable()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}
// Called when the game starts
void UInteractable::BeginPlay()
{
	Super::BeginPlay();
	AActor* Owner = GetOwner();
	TArray<UActorComponent*> InteractableComponents = Owner->GetComponentsByInterface(UInteractableComponent::StaticClass());
	for(auto Component : InteractableComponents){
		IInteractableComponent* CastedComponent = Cast<IInteractableComponent>(Component);
		InteractableComponentMap.Add(CastedComponent->GetInteractionIconName(), CastedComponent);
	}
}

void UInteractable::Interact(FInteraction InteractionStruct)
{
	FName InteractionType = InteractionStruct.InteractionType;
	if(InteractableComponentMap.Find(InteractionType) != nullptr){
		InteractableComponentMap[InteractionType]->OnInteract(InteractionStruct);
	}
}

TArray<FName> UInteractable::GetInteractOptionIcons()
{
	TArray<FName> ReturnVal;
	for(auto InteractableComponent : InteractableComponentMap){
		ReturnVal.Add(InteractableComponent.Value->GetInteractionIconName());
	}
	return ReturnVal;
}

TArray<FName> UInteractable::GetInteractOptions()
{
	TArray<FName> ReturnVal;
	for(auto InteractableComponent : InteractableComponentMap){
		ReturnVal.Add(InteractableComponent.Value->GetInteractionName());
	}
	return ReturnVal;
}