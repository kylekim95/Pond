// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CyclingMenuWidget.generated.h"

class UHorizontalBox;
class UHorizontalBoxSlot;
class UNamedSlot;

UCLASS()
class TUTORIAL_API UCyclingMenuWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
	UHorizontalBox* HorizontalBox;
	TArray<UNamedSlot*> MenuItems;
	TArray<UHorizontalBoxSlot*> MenuItemHBSlots;
	TArray<UWidget*> MenuItemContent;

public:
	UCyclingMenuWidget(const FObjectInitializer& ObjectInitializer);
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float DeltaTime) override;
	void SetMenuItems(TArray<UWidget*> NewItems);
	int CenterIndex = 0;
	int VisualCenterIndex = 0;
};
