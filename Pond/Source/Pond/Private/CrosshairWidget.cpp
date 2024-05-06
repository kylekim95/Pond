// Fill out your copyright notice in the Description page of Project Settings.


#include "CrosshairWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Animation/WidgetAnimation.h"

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

    // ReOrderDelegate.BindDynamic(this, &UCrosshairWidget::ReOrderOptions);
    ReOrderDelegate.BindUFunction(this, "ReOrderOptions");
    BindToAnimationFinished(ScrollUp, ReOrderDelegate);
    BindToAnimationFinished(ScrollDown, ReOrderDelegate);
}

void UCrosshairWidget::MoveCursor(FVector2D Input)
{
    UCanvasPanelSlot* CanvasPanelSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(CursorWrapper);
    if(IsValid(CanvasPanelSlot)){
        // FVector2D CurrentPosition = CanvasPanelSlot->GetPosition();
        // Input.Normalize();
        // Input.Y *= -1;
        CanvasPanelSlot->SetPosition(Input);
    }
}

void UCrosshairWidget::ScrollInteractOptions(float Input)
{
    if(!InteractOptionsDisplayed) return;

    float Direction = FMath::Sign(Input);
    if(Direction > 0){
        if(CurrentSelectedOptionIndex + 1 < InteractOptions.Num()){
            PlayAnimation(ScrollUp);
            CurrentSelectedOptionIndex++;
        }
    }
    else if(Direction < 0){
        if(CurrentSelectedOptionIndex - 1 >= 0){
            PlayAnimation(ScrollDown);
            CurrentSelectedOptionIndex--;
        }
    }
}

void UCrosshairWidget::ReOrderOptions()
{
    // for(auto Element : InteractOptions)
    //     UE_LOG(LogTemp, Warning, TEXT("%s"), *(Element));

    InteractOptions_Selected->SetText(FText::FromString(InteractOptions[CurrentSelectedOptionIndex]));
    
    if(CurrentSelectedOptionIndex == 0){
        InteractOptions_NotSelected_Up->SetText(FText::FromString(""));
    }
    else{
        InteractOptions_NotSelected_Up->SetText(FText::FromString(InteractOptions[CurrentSelectedOptionIndex - 1]));
    }
    
    if(CurrentSelectedOptionIndex == InteractOptions.Num() - 1){
        InteractOptions_NotSelected_Down->SetText(FText::FromString(""));
    }
    else{
        InteractOptions_NotSelected_Down->SetText(FText::FromString(InteractOptions[CurrentSelectedOptionIndex + 1]));
    }
}

void UCrosshairWidget::InteractOptionsFade(bool inout)
{
    if(inout && !InteractOptionsDisplayed){
        CurrentSelectedOptionIndex = 0;
        ReOrderOptions();
        PlayAnimation(OptionsFadeIn);
        InteractOptionsDisplayed = true;
    }
    else if(!inout && InteractOptionsDisplayed){
        PlayAnimation(OptionsFadeOut);
        InteractOptionsDisplayed = false;
        InteractOptions.Empty();
    }
}