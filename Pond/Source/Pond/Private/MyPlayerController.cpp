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
#include "UI/MyPromptWidgetActor.h"

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

    if(IsValid(PromptWidgetClass))
    {
        PromptWidgetActor = Cast<AMyPromptWidgetActor>(GetWorld()->SpawnActor(AMyPromptWidgetActor::StaticClass()));
        PromptWidgetActor->ChangeWidgetClass(PromptWidgetClass);
    }
}

void AMyPlayerController::OnLookAction(const FInputActionValue& Value)
{
    FVector2D _Value = Value.Get<FVector2D>();

    // UE_LOG(LogTemp, Warning, TEXT("[%f, %f]"), _Value.X, _Value.Y);

    FVector2D CurrentMousePosition = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld());
    MasterWidget->UpdateCursorPosition(CurrentMousePosition);

    UCameraComponent* PlayerCamera = GetPawn()->GetComponentByClass<UCameraComponent>();
    FVector CameraPosition = GetPawn()->GetActorLocation();
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
                UE_LOG(LogTemp, Warning, TEXT("%s"), *(HitResult.GetActor()->GetName()));
                ActorOnHover = HitResult.GetActor();
                PromptWidgetActor->AttachToActor(
                    ActorOnHover,
                    FAttachmentTransformRules::SnapToTargetIncludingScale
                );
                PromptWidgetActor->PlayAnimationByName("FadeIn");
            }
        }
        else
        {
            if(ActorOnHover != nullptr)
            {
                UE_LOG(LogTemp, Warning, TEXT("nullptr"));
                ActorOnHover = nullptr;
                PromptWidgetActor->PlayAnimationByName("FadeOut");
            }
        }
    }
    else
    {
        if(ActorOnHover != nullptr)
        {
            UE_LOG(LogTemp, Warning, TEXT("nullptr"));
            ActorOnHover = nullptr;
            PromptWidgetActor->PlayAnimationByName("FadeOut");
        }
    }
}

void AMyPlayerController::OnScrollAction(const FInputActionValue& Value)
{
    
}