// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "Materials/MaterialParameterCollectionInstance.h"

#include "MyPlayerController.generated.h"

/**
 * 
 */

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class UMyMasterWidget;
class UWidgetComponent;
class AMyPromptWidgetActor;

UCLASS()
class POND_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputMappingContext* InputMappingContext;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* LookAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* ScrollAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=MPC, meta=(AllowPrivateAccess = "true"))
	UMaterialParameterCollection* MPC_OnHighlightAsset;
	UMaterialParameterCollectionInstance* MPC_OnHighlight;

	UPROPERTY(EditAnywhere, Category=UI)
	TSubclassOf<class UMyMasterWidget> MasterWidgetClass;

public:
	AMyPlayerController();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	void OnLookAction(const FInputActionValue& Value);
	void OnScrollAction(const FInputActionValue& Value);

	UMyMasterWidget* MasterWidget;
	AActor* ActorOnHover;
	TArray<UActorComponent*> InteractableComponents;

	float TimerValue = 0.0f;
};
