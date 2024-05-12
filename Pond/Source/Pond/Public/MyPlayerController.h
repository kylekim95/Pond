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
struct FInputActionValue;
class UMyMasterWidget;

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

	UPROPERTY(EditAnywhere, Category=UI)
	TSubclassOf<class UMyMasterWidget> MasterWidgetClass;
	
public:
	AMyPlayerController();
	virtual void BeginPlay() override;

private:
	void OnLookAction(const FInputActionValue& Value);
	void OnScrollAction(const FInputActionValue& Value);

	UMyMasterWidget* MasterWidget;
	AActor* ActorOnHover;
};
