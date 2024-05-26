// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyCustomCursorWidget.generated.h"

/**
 * 
 */

class UImage;
struct FCursor;

UCLASS()
class POND_API UMyCustomCursorWidget : public UUserWidget
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UImage* CustomCursor;
	UPROPERTY(EditAnywhere)
	class UDataTable* Cursors;

	TMap<FName, FCursor*> CursorMap;

public:
	UMyCustomCursorWidget(const FObjectInitializer& ObjectInitializer);
	virtual void NativeConstruct() override;
	void SetCursorImg(FName CursorName);

private:

};
