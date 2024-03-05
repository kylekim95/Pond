// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SkippingStones.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class POND_API USkippingStones : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USkippingStones();

	//~ Begin UActorComponent Interface.	
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	//~ End UActorComponent Interface

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

	UPROPERTY(EditAnywhere, Category="Test")
	float InitialForceScalarValue = 500.0f;
	UPROPERTY(EditAnywhere, Category="Test")
	FVector InitialDirection = FVector(0.99f, 0.1f, 0.0f);
	float EntryAngle = 20.0f;

	void ApplyDrag();

protected:
	TObjectPtr<UPrimitiveComponent> SimulatingComponent;
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;
};
