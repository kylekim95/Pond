// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

/**
 * 
 */

class UInputMappingContext;
class UInputAction;
class UCrosshairWidget;
class IInteractable;
struct FInputActionValue;

UCLASS()
class POND_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;
	
	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* LookAction;
	/** Interact Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* InteractAction;
	/** ChangeInteractOption Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* ChangeInteractOptionAction;

	UPROPERTY(EditAnywhere, Category="UI")
	TSubclassOf<class UCrosshairWidget> CrosshairWidgetClass;

public:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
	void SetupPlayerInputComponent();

	void Look(const FInputActionValue& Value);
	void Interact(const FInputActionValue& Value);
	void ChangeInteractOption(const FInputActionValue& Value);

	UCrosshairWidget* CrosshairWidget;

private:
	float MaxRotation = 10.0f;
	AActor* ActorOnHover;
	TArray<IInteractable*> InteractOptions;
};