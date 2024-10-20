// Fill out your copyright notice in the Description page of Project Settings.
#include "ObserverController.h"
//Complete DataTypes
#include "InputMappingContext.h"
#include "InputAction.h"
#include "InputActionValue.h"
#include "Camera/CameraComponent.h"
#include "UI/MasterWidget.h"
#include "Interaction/Interactable.h"
//InPrompto
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Blueprint/WidgetLayoutLibrary.h"

AObserverController::AObserverController()
{
    static ConstructorHelpers::FObjectFinder<UInputMappingContext> IMC_Default_Finder(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/MyContent/EnhancedInput/InputMappingContext/IMC_Default.IMC_Default'"));
    IMC_Default = IMC_Default_Finder.Object;
    static ConstructorHelpers::FObjectFinder<UInputMappingContext> IMC_InteractionMenu_Finder(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/MyContent/EnhancedInput/InputMappingContext/IMC_InteractionMenu.IMC_InteractionMenu'"));
    IMC_InteractionMenu = IMC_InteractionMenu_Finder.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction> IA_MoveCursor_Finder(TEXT("/Script/EnhancedInput.InputAction'/Game/MyContent/EnhancedInput/InputAction/IA_MoveCursor.IA_MoveCursor'"));
	IA_MoveCursor = IA_MoveCursor_Finder.Object;
	static ConstructorHelpers::FObjectFinder<UInputAction> IA_ScrollOption_Finder(TEXT("/Script/EnhancedInput.InputAction'/Game/MyContent/EnhancedInput/InputAction/IA_ScrollOption.IA_ScrollOption'"));
	IA_ScrollOption = IA_ScrollOption_Finder.Object;
	static ConstructorHelpers::FObjectFinder<UInputAction> IA_Interact_Finder(TEXT("/Script/EnhancedInput.InputAction'/Game/MyContent/EnhancedInput/InputAction/IA_Interact.IA_Interact'"));
	IA_Interact = IA_Interact_Finder.Object;

    static ConstructorHelpers::FClassFinder<UMasterWidget> MasterWidgetFinder(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/MyContent/UI/Blueprints/BP_MasterWidget.BP_MasterWidget_C'"));
    MasterWidgetBP = MasterWidgetFinder.Class;
}

void AObserverController::BeginPlay()
{
    Super::BeginPlay();

    if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer())){
        Subsystem->AddMappingContext(IMC_Default, 0);
    }
    if(UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent)){
		EnhancedInputComponent->BindAction(IA_MoveCursor, ETriggerEvent::Triggered, this, &AObserverController::OnMoveCursor);
		EnhancedInputComponent->BindAction(IA_ScrollOption, ETriggerEvent::Triggered, this, &AObserverController::OnScrollOption);
        EnhancedInputComponent->BindAction(IA_Interact, ETriggerEvent::Started, this, &AObserverController::OnInteract);
	}

    MasterWidget = CreateWidget<UMasterWidget>(this, MasterWidgetBP);
    if(MasterWidget)
        MasterWidget->AddToViewport();
    MasterWidget->ViewModel->SetCursorIcons(TArray<FName>({"Circle"}));
}

void AObserverController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AObserverController::OnPossess(APawn *InPawn)
{
    Super::OnPossess(InPawn);

    PawnCameraComponent = InPawn->GetComponentByClass<UCameraComponent>();
}

void AObserverController::OnMoveCursor(const FInputActionValue& InputActionValue)
{
    FVector2D CursorPosition = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld());
    // UE_LOG(LogTemp, Warning, TEXT("CursorPosition: %s"), *(CursorPosition.ToString()));
    MasterWidget->ViewModel->SetCursorPosition(CursorPosition);

    FHitResult HitResult;
    FVector Start = GetPawn()->GetActorLocation() + PawnCameraComponent->GetRelativeLocation();
    float TraceDistance = 10000.0f;
    FVector DeprojMousePosition, DeprojMouseDirection;
    DeprojectMousePositionToWorld(DeprojMousePosition, DeprojMouseDirection);
    FVector End = Start + TraceDistance * DeprojMouseDirection;
    GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECollisionChannel::ECC_Visibility);
    if(HitResult.bBlockingHit){
        if(ActorOnHover == HitResult.GetActor())
            return;
        ActorOnHover = HitResult.GetActor();
        Interactable = Cast<UInteractable>(ActorOnHover->GetComponentByClass(UInteractable::StaticClass()));
        if(Interactable){
            if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer())){
                Subsystem->AddMappingContext(IMC_InteractionMenu, 1);
            }
            InteractOptionIndex = 0;
            MasterWidget->ViewModel->SetCursorIcons(Interactable->GetInteractOptionIcons());
            InteractOptions = Interactable->GetInteractOptions();
        }
        else{
            MasterWidget->ViewModel->SetCursorIcons(TArray<FName>({"Circle"}));
        }
    }
    else{
        if(ActorOnHover != nullptr){
            if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer())){
                Subsystem->RemoveMappingContext(IMC_InteractionMenu);
            }
            ActorOnHover = nullptr;
            Interactable = nullptr;
            MasterWidget->ViewModel->SetCursorIcons(TArray<FName>({"Circle"}));
        }
    }
}

void AObserverController::OnScrollOption(const FInputActionValue& InputActionValue)
{
    int ScrollDirection = InputActionValue.Get<float>();
    // UE_LOG(LogTemp, Warning, TEXT("ScrollDirection: %d"), ScrollDirection);

    int prev = InteractOptionIndex;
    InteractOptionIndex = FMath::Clamp((InteractOptionIndex + ScrollDirection), 0, InteractOptions.Num() - 1);
    if(prev != InteractOptionIndex)
        MasterWidget->ViewModel->SetInteractOptionIndex(InteractOptionIndex);
    // UE_LOG(LogTemp,Warning, TEXT("InteratOptionIndex : %d"), InteractOptionIndex);
}

void AObserverController::OnInteract(const FInputActionValue& InputActionValue)
{
    Interactable->Interact(FInteraction({"Circle", this}));
}