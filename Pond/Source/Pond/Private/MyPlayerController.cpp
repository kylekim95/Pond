// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "UI/MyMasterWidget.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Camera/CameraComponent.h"
#include "MyInteractable.h"
#include "Components/WidgetComponent.h"

AMyPlayerController::AMyPlayerController()
{
    
}

void AMyPlayerController::BeginPlay()
{
    Super::BeginPlay();

    if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
    {
        Subsystem->AddMappingContext(InputMappingContext, 0);
    }

    if(APawn* PossessedPawn = GetPawn())
    {
        if(UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
        {
            EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMyPlayerController::OnLookAction);
            EnhancedInputComponent->BindAction(ScrollAction, ETriggerEvent::Started, this, &AMyPlayerController::OnScrollAction);
        }
    }

    if(IsValid(MasterWidgetClass))
    {
        MasterWidget = CreateWidget<UMyMasterWidget>(this, MasterWidgetClass);
        MasterWidget->AddToPlayerScreen();
    }
}

void AMyPlayerController::Tick(float DeltaTime){
    if(TimerValue > 0 && MPC_OnHighlight != nullptr){
        TimerValue -= DeltaTime * 500.0f;
        MPC_OnHighlight->SetScalarParameterValue("Timer", TimerValue);
    }
}

void AMyPlayerController::OnLookAction(const FInputActionValue& Value)
{
    FVector2D _Value = Value.Get<FVector2D>();

    FVector2D CurrentMousePosition = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld());

    MasterWidget->UpdateCursorPosition(CurrentMousePosition);

    UCameraComponent* PlayerCamera = GetPawn()->GetComponentByClass<UCameraComponent>();
    FVector CameraPosition = GetPawn()->GetActorLocation() + PlayerCamera->GetRelativeLocation();
    FVector MousePosition;
    FVector TraceDirection;
    DeprojectMousePositionToWorld(MousePosition, TraceDirection);
    FHitResult HitResult;
    FCollisionQueryParams CollisionQueryParams;
    float TraceDistance = 10000.0f;
    GetWorld()->LineTraceSingleByChannel(HitResult, CameraPosition, CameraPosition + TraceDistance * TraceDirection, ECC_Visibility, CollisionQueryParams);

    if(HitResult.GetActor())
    {
        InteractableComponents = HitResult.GetActor()->GetComponentsByInterface(UMyInteractable::StaticClass());

        if(!InteractableComponents.IsEmpty())
        {
            if(ActorOnHover != HitResult.GetActor())
            {
                if(ActorOnHover != nullptr)
                    Cast<UStaticMeshComponent>(ActorOnHover->GetComponentByClass(UStaticMeshComponent::StaticClass()))->SetCustomDepthStencilValue(0);
                ActorOnHover = HitResult.GetActor();

                MasterWidget->ChangeCursor("Inspect");
                Cast<UStaticMeshComponent>(ActorOnHover->GetComponentByClass(UStaticMeshComponent::StaticClass()))->SetCustomDepthStencilValue(1);
                
                if(MPC_OnHighlightAsset){
                    MPC_OnHighlight = GetWorld()->GetParameterCollectionInstance(MPC_OnHighlightAsset);
                    if(MPC_OnHighlight){
                        FVector2D Screen;
                        ProjectWorldLocationToScreen(ActorOnHover->GetActorLocation(), Screen);
                        UE_LOG(LogTemp, Warning, TEXT("%f, %f"), Screen.X, Screen.Y);
                        MPC_OnHighlight->SetVectorParameterValue("StartScreenPosition", FVector4(Screen.X, Screen.Y, 0, 0));
                        TimerValue = 500.0f;
                    }
                }
            }
        }
        else
        {
            if(ActorOnHover != nullptr)
            {
                Cast<UStaticMeshComponent>(ActorOnHover->GetComponentByClass(UStaticMeshComponent::StaticClass()))->SetCustomDepthStencilValue(0);
                ActorOnHover = nullptr;
                MasterWidget->ChangeCursor("Circle");
            }
        }
    }
    else
    {
        if(ActorOnHover != nullptr)
        {
            Cast<UStaticMeshComponent>(ActorOnHover->GetComponentByClass(UStaticMeshComponent::StaticClass()))->SetCustomDepthStencilValue(0);
            ActorOnHover = nullptr;
            MasterWidget->ChangeCursor("Circle");
        }
    }
}

void AMyPlayerController::OnScrollAction(const FInputActionValue& Value)
{
    
}