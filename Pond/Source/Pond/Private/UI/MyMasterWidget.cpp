// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MyMasterWidget.h"
#include "UI/MyCustomCursorWidget.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/CanvasPanelSlot.h"
#include "Animation/WidgetAnimation.h"
#include "MyInteractable.h"

UMyMasterWidget::UMyMasterWidget(const FObjectInitializer& ObjectInitializer)
    :UUserWidget(ObjectInitializer)
{
    
}

void UMyMasterWidget::NativeConstruct()
{
    Super::NativeConstruct();
}

void UMyMasterWidget::UpdateCursorPosition(const FVector2D& Value)
{
    UCanvasPanelSlot* CustomCursorWidgetCanvasPanelSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(CustomCursorWidget);
    CustomCursorWidgetCanvasPanelSlot->SetPosition(Value);
}