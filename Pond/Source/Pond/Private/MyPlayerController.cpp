// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "CrosshairWidget.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/PanelSlot.h"
#include "Blueprint/WidgetLayoutLibrary.h"

void AMyPlayerController::BeginPlay()
{
    Super::BeginPlay();
		
    if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
    {
        Subsystem->AddMappingContext(DefaultMappingContext, 0);
    }

    SetupPlayerInputComponent();

    CrosshairWidget = CreateWidget<UCrosshairWidget>(this, CrosshairWidgetClass);
    CrosshairWidget->AddToPlayerScreen();
}

void AMyPlayerController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    CrosshairWidget->RemoveFromParent();
    CrosshairWidget = nullptr;

    Super::EndPlay(EndPlayReason);
}

// Called to bind functionality to input
void AMyPlayerController::SetupPlayerInputComponent()
{
    if(APawn* PossessedPawn = GetPawn())
    {
        if(UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
        {
            // Moving
            EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Started, this, &AMyPlayerController::Move);
            // Look
            EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMyPlayerController::Look);
        }
    }
}

void AMyPlayerController::Move(const FInputActionValue &Value)
{
	UE_LOG(LogTemp, Warning, TEXT("Controller::MOVE"));
}

void AMyPlayerController::Look(const FInputActionValue &Value)
{
    FVector2D InputVector = Value.Get<FVector2D>();
	// UE_LOG(LogTemp, Warning, TEXT("Controller::Look %lf, %lf"), InputVector.X, InputVector.Y);

    // CrosshairWidget->MoveCursor(InputVector);
    
    FVector2D Temp;
    UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld());
    CrosshairWidget->MoveCursor(Temp);
}