// Fill out your copyright notice in the Description page of Project Settings.


#include "Incident.h"
#include "WSS_UserTracker.h"

// Sets default values
AIncident::AIncident()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AIncident::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AIncident::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}