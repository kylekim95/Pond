// Fill out your copyright notice in the Description page of Project Settings.


#include "AC_Interactable.h"

// Sets default values for this component's properties
UAC_Interactable::UAC_Interactable()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAC_Interactable::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

// Called every frame
void UAC_Interactable::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UAC_Interactable::_OnInteract(AActor* Interactor)
{
	UE_LOG(LogTemp, Warning, TEXT("Hello World!"));
}

FString UAC_Interactable::GetOptionDesc()
{
	return "Default Interactable OptionDesc";
}