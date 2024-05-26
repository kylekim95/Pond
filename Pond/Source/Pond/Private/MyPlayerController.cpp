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

void AMyPlayerController::OnLookAction(const FInputActionValue& Value)
{
    FVector2D _Value = Value.Get<FVector2D>();

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
                ActorOnHover = HitResult.GetActor();

                FBox BoundingBox = ActorOnHover->GetComponentsBoundingBox();
                FVector Center, Extents;
                BoundingBox.GetCenterAndExtents(Center, Extents);
                TArray<FVector> Points = {
                    Center + FVector(Extents.X,     Extents.Y,      Extents.Z),
                    Center + FVector(-Extents.X,    Extents.Y,      Extents.Z),
                    Center + FVector(Extents.X,     -Extents.Y,     Extents.Z),
                    Center + FVector(Extents.X,     Extents.Y,      -Extents.Z),
                    Center + FVector(-Extents.X,    -Extents.Y,     Extents.Z),
                    Center + FVector(-Extents.X,    Extents.Y,      -Extents.Z),
                    Center + FVector(Extents.X,     -Extents.Y,     -Extents.Z),
                    Center + FVector(-Extents.X,    -Extents.Y,     -Extents.Z)
                };
                FIntVector2 Min, Max(0, 0);
                GetViewportSize(Min.X, Min.Y);
                for(auto Element : Points){
                    FVector2D Temp;
                    ProjectWorldLocationToScreen(Element, Temp);
                    if(Temp.X < Min.X) Min.X = Temp.X;
                    if(Temp.X > Max.X) Max.X = Temp.X;
                    if(Temp.Y < Min.Y) Min.Y = Temp.Y;
                    if(Temp.Y > Min.Y) Max.Y = Temp.Y;
                }
                MasterWidget->ChangeCursor("Thunder");
            }
        }
        else
        {
            if(ActorOnHover != nullptr)
            {
                ActorOnHover = nullptr;
                MasterWidget->ChangeCursor("Circle");
            }
        }
    }
    else
    {
        if(ActorOnHover != nullptr)
        {
            ActorOnHover = nullptr;
            MasterWidget->ChangeCursor("Circle");
        }
    }
}

void AMyPlayerController::OnScrollAction(const FInputActionValue& Value)
{
    
}