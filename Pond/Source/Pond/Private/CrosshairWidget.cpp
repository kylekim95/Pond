// Fill out your copyright notice in the Description page of Project Settings.


#include "CrosshairWidget.h"
#include "Components/Image.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Blueprint/WidgetLayoutLibrary.h"

UCrosshairWidget::UCrosshairWidget(const FObjectInitializer& ObjectInitializer)
    :UUserWidget(ObjectInitializer)
{
    static ConstructorHelpers::FObjectFinder<UTexture2D> DefaultCursorImgLoader(TEXT("/Script/Engine.Texture2D'/Game/UserContent/Crosshair.Crosshair'"));
    if(DefaultCursorImgLoader.Succeeded()){
        DefaultCursorImg = DefaultCursorImgLoader.Object;
    }
}

void UCrosshairWidget::NativeConstruct()
{
    Super::NativeConstruct();
    CustomCursor->SetBrushFromTexture(DefaultCursorImg);
}

void UCrosshairWidget::MoveCursor(FVector2D Input)
{
    UCanvasPanelSlot* CanvasPanelSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(CursorWrapper);
    if(IsValid(CanvasPanelSlot)){
        // FVector2D CurrentPosition = CanvasPanelSlot->GetPosition();
        // Input.Normalize();
        // Input.Y *= -1;
        CanvasPanelSlot->SetPosition(Input);

        UE_LOG(LogTemp, Warning, TEXT("%f, %f"), Input.X, Input.Y);
    }
}