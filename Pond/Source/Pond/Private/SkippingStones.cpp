// Fill out your copyright notice in the Description page of Project Settings.

#include "SkippingStones.h"
#include "WaterSubsystem.h"
#include "BuoyancyManager.h"

// Sets default values for this component's properties
USkippingStones::USkippingStones()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = true;
	PrimaryComponentTick.TickGroup = TG_PrePhysics;
	// ...
}

// Called when the game starts
void USkippingStones::BeginPlay()
{
	Super::BeginPlay();

	SimulatingComponent = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	if(SimulatingComponent){
		SimulatingComponent->AddImpulse(InitialDirection * InitialForceScalarValue);
	}

	StaticMeshComponent = GetOwner()->FindComponentByClass<UStaticMeshComponent>();
}

// Called every frame
void USkippingStones::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	//Slowly tilt the rock so that its pitch is equal to the entry angle
	if(StaticMeshComponent){
		FRotator CurrentRotation = StaticMeshComponent->GetRelativeRotation();
		FRotator NewRotation = FRotator(FMath::Lerp(CurrentRotation.Pitch, 30.0f, 0.5f), CurrentRotation.Yaw, CurrentRotation.Roll);
		StaticMeshComponent->SetRelativeRotation(NewRotation.Quaternion());
	}
	//Apply drag to the rock
	//Hopefully this will make the trajectory of the rock more realistic
}

void USkippingStones::OnOverlapBegin(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex, 
	bool bFromSweep, 
	const FHitResult& SweepResult
){
	
}

void USkippingStones::OnOverlapEnd(
	class UPrimitiveComponent* OverlappedComp, 
	class AActor* OtherActor, 
	class UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex
){

}

void USkippingStones::ApplyDrag()
{

}