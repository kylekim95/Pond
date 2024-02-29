// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "BuoyancyTypes.h"

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
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	//~ End UActorComponent Interface

	//~ Begin UObject Interface.	
	// virtual void GetResourceSizeEx(FResourceSizeEx& CumulativeResourceSize) override;
	// virtual void PostLoad() override;
	// virtual void Serialize(FArchive& Ar) override;
	//~ End UObject Interface

	virtual void Update(float DeltaTime);

protected:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = Buoyancy)
	FBuoyancyData BuoyancyData;

public:	
		
};
