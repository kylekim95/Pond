// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

/**
 * 
 */

class UUserWidget;

UCLASS()
class POND_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category="UI")
	TSubclassOf<class UUserWidget> CrosshairWidgetClass;
	UPROPERTY()
	class UUserWidget* CrosshairWidget;

public:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
};
