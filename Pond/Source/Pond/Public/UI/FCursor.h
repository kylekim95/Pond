// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "FCursor.generated.h"

/**
 * 
 */

class UMaterial;

USTRUCT(BlueprintType)
struct FCursor : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMaterial* CursorMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Descriptor;
};
