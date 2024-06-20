// Fill out your copyright notice in the Description page of Project Settings.


#include "MyTestInteractableComponent.h"

// Sets default values for this component's properties
UMyTestInteractableComponent::UMyTestInteractableComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMyTestInteractableComponent::BeginPlay()
{
	Super::BeginPlay();

	
	UStaticMeshComponent* Temp = Cast<UStaticMeshComponent>(GetOwner()->FindComponentByClass(UStaticMeshComponent::StaticClass()));
	Temp->SetRenderCustomDepth(true);
	// ...
	
}


// Called every frame
void UMyTestInteractableComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UMyTestInteractableComponent::_OnInteract(AActor *Interactable)
{
	UE_LOG(LogTemp, Warning, TEXT("MyTestInteractableComponent::_OnInteract"));
}