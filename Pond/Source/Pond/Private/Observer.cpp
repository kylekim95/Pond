// Fill out your copyright notice in the Description page of Project Settings.
#include "Observer.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "Blueprint/WidgetLayoutLibrary.h"

// Sets default values
AObserver::AObserver()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	SetRootComponent(CapsuleComponent);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(GetRootComponent());

	static ConstructorHelpers::FObjectFinder<UInputAction> IA_PanTilt_Finder(TEXT("/Script/EnhancedInput.InputAction'/Game/MyContent/EnhancedInput/InputAction/IA_PanTilt.IA_PanTilt'"));
	IA_PanTilt = IA_PanTilt_Finder.Object;
}
// Called when the game starts or when spawned
void AObserver::BeginPlay()
{
	Super::BeginPlay();

	OnViewportResizedHandle = FViewport::ViewportResizedEvent.AddLambda([=, this](FViewport* Viewport, uint32 Unknown){
		PanTiltMinThreshold.X = Viewport->GetSizeXY().X * 0.05f;
		PanTiltMinThreshold.Y = Viewport->GetSizeXY().Y * 0.05f;
		PanTiltMaxThreshold.X = Viewport->GetSizeXY().X * 0.95f;
		PanTiltMaxThreshold.Y = Viewport->GetSizeXY().Y * 0.95f;
	});
	PanTiltLimit = FRotator(60.0f, 60.0f, 0.0f);
	TargetRotation = FRotator(0.0f, 0.0f, 0.0f);
}

void AObserver::EndPlay(EEndPlayReason::Type EndPlayReason)
{
	FViewport::ViewportResizedEvent.Remove(OnViewportResizedHandle);
}
// Called every frame
void AObserver::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FRotator CurrentRotation = CameraComponent->GetRelativeRotation();
	FRotator NextRotation = FRotator(
		FMath::Lerp(CurrentRotation.Pitch, TargetRotation.Pitch, DeltaTime),
		FMath::Lerp(CurrentRotation.Yaw, TargetRotation.Yaw, DeltaTime),
		0.0f
	);
	CameraComponent->SetRelativeRotation(NextRotation);
}
// Called to bind functionality to input
void AObserver::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if(UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)){
		EnhancedInputComponent->BindAction(IA_PanTilt, ETriggerEvent::Triggered, this, &AObserver::OnPanTilt);
	}
}

void AObserver::ChangeSettings(FVector Location, FRotator Rotation, FRotator _PanTiltLimit)
{
	SetActorLocation(Location);
	SetActorRotation(Rotation);
	CameraComponent->SetRelativeRotation(FRotator::ZeroRotator);
	PanTiltLimit = _PanTiltLimit;
}

void AObserver::OnPanTilt(const FInputActionValue& InputActionValue)
{
	FVector2D Value = InputActionValue.Get<FVector2D>();

	FVector2D MousePositionOnViewport = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld());
	FVector2D Direction(0, 0);
	if(MousePositionOnViewport.X <= PanTiltMinThreshold.X)
		Direction.X = -1;
	else if(MousePositionOnViewport.X >= PanTiltMaxThreshold.X)
		Direction.X = 1;
	if(MousePositionOnViewport.Y <= PanTiltMinThreshold.Y)
		Direction.Y = 1;
	else if(MousePositionOnViewport.Y >= PanTiltMaxThreshold.Y)
		Direction.Y = -1;

	TargetRotation.Pitch = Direction.Y * PanTiltLimit.Pitch;
	TargetRotation.Yaw = Direction.X * PanTiltLimit.Yaw;

	FRotator CurrentRotation = CameraComponent->GetRelativeRotation();
	if(Direction.X == 0){
		TargetRotation.Yaw = CurrentRotation.Yaw;
	}
	if(Direction.Y == 0){
		TargetRotation.Pitch = CurrentRotation.Pitch;
	}
}
