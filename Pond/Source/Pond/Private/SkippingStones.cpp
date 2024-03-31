// Fill out your copyright notice in the Description page of Project Settings.

#include "SkippingStones.h"
#include "WaterSubsystem.h"
#include "WaterBodyActor.h"
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

	//~ Begin Initialization
	PrimitiveComponent = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	StaticMeshComponent = GetOwner()->FindComponentByClass<UStaticMeshComponent>();
	//~ End Initialization

	StaticMeshComponent->OnComponentBeginOverlap.AddDynamic(this, &USkippingStones::OnOverlapBegin);
	StaticMeshComponent->OnComponentEndOverlap.AddDynamic(this, &USkippingStones::OnOverlapEnd);
	StaticMeshComponent->OnComponentHit.AddDynamic(this, &USkippingStones::OnHitComponent);

	Throw(FThrowDesc(200.0f, FVector::ForwardVector, 2000.0f, FRotator(20.0f, 0.0f, 0.0f)));
}

void USkippingStones::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(PrimitiveComponent && StaticMeshComponent){
		if(!Stable){
			//Do nothing
		}
		else if(!Collided && Overlapping && OverlappingActor.IsA(AWaterBody::StaticClass())){
			Current.LinearForce *= 0.9f;
			Current.Torque *= 0.9f;

			if(Current.Torque < TorqueThreshold)
				Stable = false;

			if(!Stable) return;
			
			PrimitiveComponent->SetPhysicsLinearVelocity(FVector::Zero());
			StaticMeshComponent->SetPhysicsAngularVelocityInDegrees(FVector::Zero());
			
			// FRotator Temp = PrimitiveComponent->GetRelativeRotation();
			// Temp.Yaw += 1.0f;
			// PrimitiveComponent->SetRelativeRotation(Temp.Quaternion());
			PrimitiveComponent->AddImpulse(Current.Orientation.RotateVector(Current.Direction) * Current.LinearForce);
			StaticMeshComponent->AddAngularImpulseInDegrees(Current.Orientation.RotateVector(FVector::UpVector) * Current.Torque, NAME_None, true);
		}
		else if(!Collided && !Overlapping){
			// FRotator CurrentOrientation = StaticMeshComponent->GetRelativeRotation();
			// float CurrentPitch = CurrentOrientation.Pitch;
			// FRotator NewOrientation = FRotator(FMath::Lerp(CurrentPitch, Current.Orientation.Pitch, 0.5f), CurrentOrientation.Yaw, CurrentOrientation.Roll);
			// StaticMeshComponent->SetRelativeRotation(NewOrientation.Quaternion());

			//Horizontal Drag
			FVector VelocityDirection_XY = PrimitiveComponent->GetPhysicsLinearVelocity();
			float ZLength = VelocityDirection_XY.Z;
			VelocityDirection_XY.Z = 0;
			float Length = VelocityDirection_XY.Length();
			VelocityDirection_XY.Normalize();

			Length = FMath::FInterpTo(Length, VelocityThreshold, 0.25f, 0.1f);

			PrimitiveComponent->SetPhysicsLinearVelocity(VelocityDirection_XY * Length + FVector(0.0f, 0.0f, ZLength));
		}
		else if(Collided){
			Stable = false;
		}
	}
}

void USkippingStones::OnOverlapBegin(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex,
	bool bFromSweep, 
	const FHitResult& SweepResult
){
	Overlapping = true;
	OverlappingActor = OtherActor;
}

void USkippingStones::OnOverlapEnd(
	class UPrimitiveComponent* OverlappedComp, 
	class AActor* OtherActor, 
	class UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex
){
	Overlapping = false;
	OverlappingActor = nullptr;
}

void USkippingStones::OnHitComponent(
	UPrimitiveComponent* HitComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	FVector NormalImpulse,
	const FHitResult& Hit
){
	Collided = true;
}

void USkippingStones::Throw(FThrowDesc ThrowDesc)
{
	if(PrimitiveComponent && StaticMeshComponent){
		Stable = true;
		Current.Direction = ThrowDesc.Direction;
		Current.LinearForce = ThrowDesc.LinearForce;
		Current.Orientation = ThrowDesc.Orientation;
		Current.Torque = ThrowDesc.Torque;

		PrimitiveComponent->AddImpulse(Current.Direction * Current.LinearForce);
		
		StaticMeshComponent->SetRelativeRotation(Current.Orientation.Quaternion());
		StaticMeshComponent->AddAngularImpulseInDegrees(Current.Orientation.RotateVector(FVector::UpVector) * Current.Torque, NAME_None, true);
	}
}