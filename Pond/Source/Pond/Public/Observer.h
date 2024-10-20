// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Observer.generated.h"

class UCameraComponent;
class UCapsuleComponent;
class UInputAction;
struct FInputActionValue;

UCLASS()
class TUTORIAL_API AObserver : public APawn
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Root, meta = (AllowPrivateAccess = "true"))
	class UCapsuleComponent* CapsuleComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* CameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* IA_PanTilt;

public:
	AObserver();
	virtual void BeginPlay() override;
	virtual void EndPlay(EEndPlayReason::Type EndPlayReason) override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void ChangeSettings(FVector Location, FRotator Rotation, FRotator _PanTiltLimit = FRotator(60.0f, 60.0f, 0.0f));
private:
	void OnPanTilt(const FInputActionValue& InputActionValue);
	FVector2D PanTiltMinThreshold;
	FVector2D PanTiltMaxThreshold;
	FRotator PanTiltLimit;
	FRotator TargetRotation;
	FDelegateHandle OnViewportResizedHandle;
};
