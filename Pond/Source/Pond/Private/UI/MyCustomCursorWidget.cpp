// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/MyCustomCursorWidget.h"
#include "Components/Image.h"

UMyCustomCursorWidget::UMyCustomCursorWidget(const FObjectInitializer& ObjectInitializer)
    :UUserWidget(ObjectInitializer)
{
    if(CustomCursorImg == nullptr)
    {
        static ConstructorHelpers::FObjectFinder<UTexture2D> DefaultCursorImgLoader(*DefaultCustomCursorImgRef);
        if(DefaultCursorImgLoader.Succeeded()){
            CustomCursorImg = DefaultCursorImgLoader.Object;
        }
    }
}

void UMyCustomCursorWidget::NativeConstruct()
{
    Super::NativeConstruct();
    CustomCursor->SetBrushFromTexture(CustomCursorImg);
}