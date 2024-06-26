// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EditorUtilityWidget.h"
#include "EUW_IncidentsSpawnableLocation.generated.h"

UCLASS()
class POND_API UEUW_IncidentsSpawnableLocation : public UEditorUtilityWidget
{
	GENERATED_BODY()
	
public:
	UEUW_IncidentsSpawnableLocation();

private:
	UDataTable* IncidentsSpawnLocationDataTable;
};

USTRUCT(BlueprintType)
struct IncidentsSpawnLocationData : FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	FVector Position;
	UPROPERTY(EditAnywhere)
	FString Tags;
};