// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI/Deprecated/AnimWidget.h"
#include "MyPromptWidget.generated.h"

class UWidgetAnimation;

/**
 * 
 */
UCLASS()
class POND_API UMyPromptWidget : public UUserWidget, public IAnimWidget
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* FadeIn;
	UPROPERTY(EditAnywhere, meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* FadeOut;

public:
	virtual bool PlayAnimationByName(FName AnimName) override;
};
