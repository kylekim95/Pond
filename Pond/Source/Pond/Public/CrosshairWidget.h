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
struct FInputActionValue;

UCLASS()
class POND_API UCrosshairWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UCanvasPanel* CursorWrapper;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UImage* CustomCursor;

	UTexture2D* DefaultCursorImg;

public:
	UCrosshairWidget(const FObjectInitializer& ObjectInitializer);
	void NativeConstruct();

	void MoveCursor(FVector2D Input);
};
