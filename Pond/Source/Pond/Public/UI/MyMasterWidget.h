// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyMasterWidget.generated.h"

/**
 * 
 */

class UMyCustomCursorWidget;
class UWidgetAnimation;

UCLASS()
class POND_API UMyMasterWidget : public UUserWidget
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UMyCustomCursorWidget* CustomCursorWidget;

public:
	UMyMasterWidget(const FObjectInitializer& ObjectInitializer);
	virtual void NativeConstruct() override;
	void UpdateCursorPosition(const FVector2D& Value);
	void OnHoverInteractable(bool Interactable);
};
