// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "Blueprint/UserWidget.h"

void AMyPlayerController::BeginPlay()
{
    Super::BeginPlay();

    // SetShowMouseCursor(true);

    CrosshairWidget = CreateWidget<UUserWidget>(this, CrosshairWidgetClass);
    CrosshairWidget->AddToPlayerScreen();
}

void AMyPlayerController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    CrosshairWidget->RemoveFromParent();
    CrosshairWidget = nullptr;

    Super::EndPlay(EndPlayReason);
}
