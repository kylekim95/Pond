// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyCustomCursorWidget.generated.h"

/**
 * 
 */

class UImage;

UCLASS()
class POND_API UMyCustomCursorWidget : public UUserWidget
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UImage* CustomCursor;
	UPROPERTY(EditAnywhere)
	UTexture2D* CustomCursorImg;

public:
	UMyCustomCursorWidget(const FObjectInitializer& ObjectInitializer);
	virtual void NativeConstruct() override;

private:
	FString DefaultCustomCursorImgRef = "/Script/Engine.Texture2D'/Game/MyContent/Blueprints/UI/Crosshair.Crosshair'";
};
