// Fill out your copyright notice in the Description page of Project Settings.


#include "SkippingStones.h"

// Sets default values for this component's properties
USkippingStones::USkippingStones()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = false;
	PrimaryComponentTick.TickGroup = TG_PrePhysics;

	// ...
}

// Called when the game starts
void USkippingStones::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void USkippingStones::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	// ...
	
}

// Called every frame
void USkippingStones::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	Update(DeltaTime);
	// ...
}

void USkippingStones::Update(float DeltaTime)
{

}