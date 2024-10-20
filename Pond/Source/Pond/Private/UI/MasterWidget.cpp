// Fill out your copyright notice in the Description page of Project Settings.
#include "UI/MasterWidget.h"
//Complete DataTypes
#include "Components/CanvasPanel.h"
#include "Components/NamedSlot.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/Image.h"
#include "UI/CyclingMenuWidget.h"
//InPrompto
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Blueprint/WidgetTree.h"

UMasterWidget::UMasterWidget(const FObjectInitializer& ObjectInitializer)
    : UUserWidget(ObjectInitializer)
{
    static ConstructorHelpers::FObjectFinder<UDataTable> CursorDTFinder(TEXT("/Script/Engine.DataTable'/Game/MyContent/DataTables/DT_Cursor.DT_Cursor'"));
    CursorDT = CursorDTFinder.Object;
}

void UMasterWidget::NativeConstruct(){
    ViewModel = NewObject<UMasterWidgetViewModel>();
    ViewModel->Delegates["CursorPosition"].AddUObject(this, &UMasterWidget::OnCursorPositionChanged);
    ViewModel->Delegates["CursorIcons"].AddUObject(this, &UMasterWidget::OnCursorIconsChanged);
    ViewModel->Delegates["InteractOptionIndex"].AddUObject(this, &UMasterWidget::OnInteractOptionIndexChanged);

    NamedSlotPanelSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(NamedSlot);

    TArray<FName> IconNames = CursorDT->GetRowNames();
    for(auto Name : IconNames){
        FCursor* RowContent = CursorDT->FindRow<FCursor>(Name, TEXT("HelloWorld!"));
        Contents.Add(Name, RowContent->CursorMaterial);
    }
}

void UMasterWidget::OnCursorPositionChanged(ViewModelPropertyBase* PropertyBase){
    ViewModelProperty<FVector2D>* Property = (ViewModelProperty<FVector2D>*)PropertyBase;
    NamedSlotPanelSlot->SetPosition(Property->Get());

    UWidgetLayoutLibrary::SlotAsCanvasSlot(Debug)->SetPosition(Property->Get());
}

void UMasterWidget::OnCursorIconsChanged(ViewModelPropertyBase* PropertyBase){
    ViewModelProperty<TArray<FName>>* Property = (ViewModelProperty<TArray<FName>>*)PropertyBase;
    TArray<UWidget*> Content;
    int ind = 0;
    for(auto Name : Property->Get()){
        UImage* Temp;
        if(ImagePool.Num() > ind){
            Temp = ImagePool[ind];
        }
        else{
            Temp = WidgetTree->ConstructWidget<UImage>();
            ImagePool.Add(Temp);
        }
        Temp->SetBrushFromMaterial(Contents[Name]);
        ind++;
        Content.Add(Temp);
    }
    CyclingMenuWidget->SetMenuItems(Content);
}

void UMasterWidget::OnInteractOptionIndexChanged(ViewModelPropertyBase* PropertyBase){
    ViewModelProperty<int>* Property = (ViewModelProperty<int>*)PropertyBase;
    CyclingMenuWidget->CenterIndex = Property->Get();
}
