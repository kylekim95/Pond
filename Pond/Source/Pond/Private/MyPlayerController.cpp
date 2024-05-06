// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "CrosshairWidget.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/PanelSlot.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Camera/CameraComponent.h"
#include "Interactable.h"

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
            // Look
            EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMyPlayerController::Look);
            // Interact
            EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &AMyPlayerController::Interact);
            // ChangeInteractOptions
            EnhancedInputComponent->BindAction(ChangeInteractOptionAction, ETriggerEvent::Triggered, this, &AMyPlayerController::ChangeInteractOption);
        }
    }
}

void AMyPlayerController::Look(const FInputActionValue &Value)
{
    FVector2D InputVector = Value.Get<FVector2D>();
    
    FVector2D CurrentMousePosition;
    UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld());
    CrosshairWidget->MoveCursor(CurrentMousePosition);

    UCameraComponent* PlayerCamera = GetPawn()->GetComponentByClass<UCameraComponent>();
    FHitResult HitResult;
    FVector CameraPosition = GetPawn()->GetActorLocation();
    FVector MousePosition;
    FVector TraceDirection;
    FCollisionQueryParams CollisionQueryParams;
    DeprojectMousePositionToWorld(MousePosition, TraceDirection);
    float TraceDistance = 10000.0f;
    GetWorld()->LineTraceSingleByChannel(HitResult, CameraPosition, CameraPosition + TraceDistance * TraceDirection, ECC_Visibility, CollisionQueryParams);

    if(HitResult.GetActor()){
        if(ActorOnHover != HitResult.GetActor()){
            InteractOptions.Empty();
            ActorOnHover = HitResult.GetActor();
            TArray<UActorComponent*> ActorComponents = HitResult.GetActor()->GetComponentsByInterface(UInteractable::StaticClass());
            for(auto Element : ActorComponents){
                IInteractable* InteractableComponent = Cast<IInteractable>(Element);
                InteractOptions.Add(InteractableComponent);
                CrosshairWidget->InteractOptions.Add(InteractableComponent->GetOptionDesc());
            }
        }
    }
    else{
        InteractOptions.Empty();
        ActorOnHover = nullptr;
    }

    if(InteractOptions.IsEmpty()){
        CrosshairWidget->InteractOptionsFade(false);
    }
    else{
        CrosshairWidget->InteractOptionsFade(true);
    }
}

void AMyPlayerController::Interact(const FInputActionValue& Value)
{
	InteractOptions[CrosshairWidget->CurrentSelectedOptionIndex]->OnInteract(this->GetPawn());
}

void AMyPlayerController::ChangeInteractOption(const FInputActionValue& Value)
{
	// UE_LOG(LogTemp, Warning, TEXT("Controller::ChangeInteractOption"));
    float RealValue = Value.Get<float>();

    // UE_LOG(LogTemp, Warning, TEXT("%f"), RealValue);
    //1 up -1 down
    CrosshairWidget->ScrollInteractOptions(RealValue);
}