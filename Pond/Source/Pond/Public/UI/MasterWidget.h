// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI/MVVM/ViewModelBase.h"
#include "MasterWidget.generated.h"

class UCanvasPanel;
class UNamedSlot;
class UCanvasPanelSlot;
class UImage;
class UCyclingMenuWidget;

USTRUCT()
struct FCursor : public FTableRowBase
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere)
	UMaterial* CursorMaterial;
};

UCLASS()
class UMasterWidgetViewModel : public UViewModelBase
{
	GENERATED_BODY()
	PROPERTY(FVector2D, CursorPosition);
	PROPERTY(TArray<FName>, CursorIcons);
	PROPERTY(int, InteractOptionIndex);
public:
	UMasterWidgetViewModel(){
		INIT(CursorPosition)
		INIT(CursorIcons)
		INIT(InteractOptionIndex)
	}
};

UCLASS()
class TUTORIAL_API UMasterWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
	UCanvasPanel* CanvasPanel;
	UPROPERTY(meta = (BindWidget))
	UNamedSlot* NamedSlot;
	UCanvasPanelSlot* NamedSlotPanelSlot;
	UPROPERTY(meta = (BindWidget))
	UCyclingMenuWidget* CyclingMenuWidget;
	UDataTable* CursorDT;
	TMap<FName, UMaterial*> Contents;
	TArray<UImage*> ImagePool;

	UPROPERTY(meta = (BindWidget))
	UImage* Debug;

public:
	UMasterWidget(const FObjectInitializer& ObjectInitializer);
	virtual void NativeConstruct() override;
	UMasterWidgetViewModel* ViewModel;
private:
	void OnCursorPositionChanged(ViewModelPropertyBase* PropertyBase);
	void OnCursorIconsChanged(ViewModelPropertyBase* PropertyBase);
	void OnInteractOptionIndexChanged(ViewModelPropertyBase* PropertyBase);
};
