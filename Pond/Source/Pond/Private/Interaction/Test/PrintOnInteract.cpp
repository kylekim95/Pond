// Fill out your copyright notice in the Description page of Project Settings.
#include "Interaction/Test/PrintOnInteract.h"

// Sets default values for this component's properties
UPrintOnInteract::UPrintOnInteract()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UPrintOnInteract::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UPrintOnInteract::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

FName UPrintOnInteract::GetInteractionIconName(){
	return "Inspect";
}

FName UPrintOnInteract::GetInteractionName(){
	return "PrintOnInteract";
}

void UPrintOnInteract::OnInteract(FInteraction InteractionStruct){
	FString Temp = InteractionStruct.Interactor->GetFullName();
	UE_LOG(LogTemp, Warning, TEXT("%s"), *Temp);
}