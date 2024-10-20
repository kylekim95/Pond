// Fill out your copyright notice in the Description page of Project Settings.
#include "UI/CyclingMenuWidget.h"

#include "Components/HorizontalBox.h"
#include "Components/NamedSlot.h"
#include "Blueprint/WidgetTree.h"
#include "Components/HorizontalBoxSlot.h"
//DEBUG
#include "Components/Image.h"

UCyclingMenuWidget::UCyclingMenuWidget(const FObjectInitializer& ObjectInitializer)
    : UUserWidget(ObjectInitializer)
{

}

void UCyclingMenuWidget::NativeConstruct()
{
    Super::NativeConstruct();

    WidgetTree->RootWidget = HorizontalBox;
    for(int i = 0; i < 3; i++){
        UNamedSlot* Temp = WidgetTree->ConstructWidget<UNamedSlot>();
        MenuItems.Add(Temp);
        UHorizontalBoxSlot* TempSlot = HorizontalBox->AddChildToHorizontalBox(Temp);
        MenuItemHBSlots.Add(TempSlot);
        TempSlot->SetSize(FSlateChildSize(ESlateSizeRule::Fill));
    }
}

void UCyclingMenuWidget::NativeTick(const FGeometry& MyGeometry, float DeltaTime)
{
    Super::NativeTick(MyGeometry, DeltaTime);

    if(VisualCenterIndex != CenterIndex){
        int Magnitude = CenterIndex - VisualCenterIndex;
        int Direction = -1 * FMath::Sign(Magnitude);
        Magnitude = FMath::Abs(Magnitude);

        int end_point = MenuItems.Num();
        for(int i = 0; i < MenuItems.Num(); i++){
            FVector2D RendTrans = MenuItems[i]->GetRenderTransform().Translation;
            MenuItems[i]->SetRenderTranslation(FVector2D(RendTrans.X + 50 * Direction, 0.0f));
            if(Direction < 0){
                if(MenuItems[i]->GetRenderTransform().Translation.X == (-50 * (i + 1))){
                    MenuItems[i]->SetRenderTranslation(FVector2D(50 * (end_point - 1 - i), 0.0f));
                }
            }
            else{
                if(MenuItems[i]->GetRenderTransform().Translation.X == (50 * (end_point - i))){
                    MenuItems[i]->SetRenderTranslation(FVector2D(-50 * i, 0.0f));
                }
            }
        }
        VisualCenterIndex = CenterIndex;
    }
}

void UCyclingMenuWidget::SetMenuItems(TArray<UWidget*> NewItems)
{
    MenuItemContent.Empty();
    for(auto Content : NewItems){
        MenuItemContent.Add(Content);
    }
    int cnt = 0;
    int i;
    for(i = 1; i < MenuItems.Num() && cnt < MenuItemContent.Num(); i++){
        MenuItems[i]->SetContent(MenuItemContent[cnt]);
        cnt++;
    }
    for(;i < MenuItems.Num(); i++){
        MenuItems[i]->RemoveChildAt(0);
    }
}