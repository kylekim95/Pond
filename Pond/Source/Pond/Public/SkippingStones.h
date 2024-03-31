// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SkippingStones.generated.h"

USTRUCT(BlueprintType)
struct FThrowDesc
{
	GENERATED_BODY()

	FThrowDesc(){}
	FThrowDesc(float _LinearForce, const FVector _Direction, float _Torque, const FRotator _Orientation){
		LinearForce		= _LinearForce;
		Direction		= _Direction;
		Torque			= _Torque;
		Orientation 	= _Orientation;
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Test Variables")
	float LinearForce = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Test Variables")
	FVector Direction = FVector::ForwardVector;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Test Variables")
	float Torque = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Test Variables")
	FRotator Orientation;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class POND_API USkippingStones : public UActorComponent
{
	GENERATED_BODY()

public:	
	USkippingStones();

	//UActorComponent Interface.	
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
	void OnOverlapBegin(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex, 
		bool bFromSweep, 
		const FHitResult& SweepResult
	);
	UFUNCTION()
	void OnOverlapEnd(
		class UPrimitiveComponent* OverlappedComp, 
		class AActor* OtherActor, 
		class UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex
	);
	UFUNCTION()
	void OnHitComponent(
		UPrimitiveComponent* HitComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		FVector NormalImpulse,
		const FHitResult& Hit
	);

	UFUNCTION()
	void Throw(FThrowDesc ThrowDesc);

	//~ State
	bool Overlapping = false;
	TObjectPtr<AActor> OverlappingActor;
	bool Collided = false;
	bool Stable = false;
	FThrowDesc Current;

	//~ Constants
	float VelocityThreshold = 100.0f;
	
	float LinearForceThreshold = 100.0f;
	float TorqueThreshold = 100.0f;

protected:
	TObjectPtr<UPrimitiveComponent> PrimitiveComponent;
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;
};