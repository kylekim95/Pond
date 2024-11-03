// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/MyCustomCursorWidget.h"
#include "Components/Image.h"
#include "UI/FCursor.h"

USTRUCT()
struct FCursorDTEntry : public FTableRowBase
{
    UMaterial* CursorMaterial;
    FString Descriptor;
};

UMyCustomCursorWidget::UMyCustomCursorWidget(const FObjectInitializer& ObjectInitializer)
    :UUserWidget(ObjectInitializer)
{
    static ConstructorHelpers::FObjectFinder<UDataTable> CursorsDTLoader(TEXT("/Script/Engine.DataTable'/Game/MyContent/DataTables/Cursors.Cursors'"));
    if(CursorsDTLoader.Succeeded())
    {
        Cursors = CursorsDTLoader.Object;
    }
}

void UMyCustomCursorWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if(Cursors)
    {
        auto NameList = Cursors->GetRowNames();
        for(auto Element : NameList)
        {
            CursorMap.Add(Element, Cursors->FindRow<FCursor>(Element, FString("")));
        }
    }
}

void UMyCustomCursorWidget::SetCursorImg(FName CursorName)
{
    if(CursorMap.Find(CursorName) != nullptr)
        CustomCursor->SetBrushFromMaterial(CursorMap[CursorName]->CursorMaterial);
}