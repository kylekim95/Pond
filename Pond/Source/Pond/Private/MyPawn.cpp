// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/CapsuleComponent.h"

// Sets default values
AMyPawn::AMyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	CapsuleComponent->SetupAttachment(GetRootComponent());

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(CapsuleComponent);
	CameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 100.0f));
}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();

	if(UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMyPawn::OnLookAction);
	}

	FRotator CurrentCameraRotation = CameraComponent->GetRelativeRotation();
	TargetCameraRotation = CurrentCameraRotation;
}

// Called every frame
void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FRotator CurrentCameraRotation = CameraComponent->GetRelativeRotation();
	CameraComponent->SetRelativeRotation(FRotator(
			FMath::Lerp(CurrentCameraRotation.Pitch, TargetCameraRotation.Pitch, 0.05f),
			FMath::Lerp(CurrentCameraRotation.Yaw, TargetCameraRotation.Yaw, 0.05f),
			CurrentCameraRotation.Roll
	));
}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AMyPawn::OnLookAction(const FInputActionValue& Value)
{
	FVector2D _Value = Value.Get<FVector2D>();

    FVector2D CurrentMousePosition = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld()) * UWidgetLayoutLibrary::GetViewportScale(GetWorld());
	FVector2D CurrentViewportSize = UWidgetLayoutLibrary::GetViewportSize(GetWorld());

	FVector2D MinThresholdInPixels, MaxThresholdInPixels;
	MinThresholdInPixels.X = CurrentViewportSize.X * MoveCameraThreshold;
	MaxThresholdInPixels.X = CurrentViewportSize.X - MinThresholdInPixels.X;
	MinThresholdInPixels.Y = CurrentViewportSize.Y * MoveCameraThreshold;
	MaxThresholdInPixels.Y = CurrentViewportSize.Y - MinThresholdInPixels.Y;

	FVector2D Direction;
	if(CurrentMousePosition.X < MinThresholdInPixels.X)
		Direction.X = -1;
	else if(CurrentMousePosition.X > MaxThresholdInPixels.X)
		Direction.X = 1;
	else
		Direction.X = 0;

	if(CurrentMousePosition.Y < MinThresholdInPixels.Y)
		Direction.Y = 1;
	else if(CurrentMousePosition.Y > MaxThresholdInPixels.Y)
		Direction.Y = -1;
	else
		Direction.Y = 0;

	TargetCameraRotation.Pitch = Direction.Y * 20.0f;
	TargetCameraRotation.Yaw = Direction.X * 20.0f;
	FRotator CurrentCameraRotation = CameraComponent->GetRelativeRotation();
	if(Direction.Y == 0) TargetCameraRotation.Pitch = CurrentCameraRotation.Pitch;
	if(Direction.X == 0) TargetCameraRotation.Yaw = CurrentCameraRotation.Yaw;
}