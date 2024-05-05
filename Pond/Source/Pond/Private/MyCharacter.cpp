// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/CapsuleComponent.h"
#include "InputActionValue.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "MyPlayerController.h"
#include "CrosshairWidget.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Look
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMyCharacter::Look);
		//Interact
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &AMyCharacter::Interact);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AMyCharacter::Look(const FInputActionValue& Value)
{
    FVector2D InputVector = Value.Get<FVector2D>();
	InputVector.Normalize();

	FRotator CurrentCameraRotation = FirstPersonCameraComponent->GetRelativeRotation();
	CurrentCameraRotation.Pitch = FMath::Lerp(CurrentCameraRotation.Pitch, FMath::Sign(InputVector.Y) * 10.0f, FMath::Abs(InputVector.Y) * 0.05f);
	CurrentCameraRotation.Yaw 	= FMath::Lerp(CurrentCameraRotation.Yaw, FMath::Sign(InputVector.X) * 10.0f, FMath::Abs(InputVector.X) * 0.05f);
	FirstPersonCameraComponent->SetRelativeRotation(CurrentCameraRotation);
}

void AMyCharacter::Interact(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Warning, TEXT("Character::Interact"));
}