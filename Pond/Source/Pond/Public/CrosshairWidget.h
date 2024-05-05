// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CrosshairWidget.generated.h"

/**
 * 
 */

class UInputAction;
class UImage;
class UCanvsPanel;
class UTextBox;
class UWidgetAnimation;
struct FInputActionValue;

UCLASS()
class POND_API UCrosshairWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UCanvasPanel* CursorWrapper;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UImage* CustomCursor;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* InteractOptions_NotSelected_Up;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* InteractOptions_Selected;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* InteractOptions_NotSelected_Down;

	UPROPERTY(Transient, meta=(BindWidgetAnim))
	TObjectPtr<UWidgetAnimation> ScrollUp;
	UPROPERTY(Transient, meta=(BindWidgetAnim))
	TObjectPtr<UWidgetAnimation> ScrollDown;
	UPROPERTY(Transient, meta=(BindWidgetAnim))
	TObjectPtr<UWidgetAnimation> OptionsFadeIn;
	UPROPERTY(Transient, meta=(BindWidgetAnim))
	TObjectPtr<UWidgetAnimation> OptionsFadeOut;

	UTexture2D* DefaultCursorImg;

public:
	UCrosshairWidget(const FObjectInitializer& ObjectInitializer);
	void NativeConstruct();

	void MoveCursor(FVector2D Input);
	void ScrollInteractOptions(float Input);

	UFUNCTION()
	void ReOrderOptions();

	void InteractOptionsFade(bool inout);
	TArray<FString> InteractOptions;

private:
	FWidgetAnimationDynamicEvent ReOrderDelegate;

	int CurrentSelectedOptionIndex = 0;

	bool InteractOptionsDisplayed = false;
};
