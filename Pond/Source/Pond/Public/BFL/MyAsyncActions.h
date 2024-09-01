// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "LatentActions.h"
#include "MyAsyncActions.generated.h"

UENUM()
enum class ELatentActionInputPins : uint8
{
	Start,
	Interrupt
};
UENUM()
enum class ELatentActionOutputPins : uint8
{
	OnStarted,
	OnUpdated,
	OnInterrupted,
	OnCompleted
};
UCLASS()
class POND_API UMyAsyncActions : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(
		BlueprintCallable,
		meta = (WorldContext = "WorldContext", Latent, LatentInfo = "LatentInfo", ExpandEnumAsExecs="InputPins,OutputPins"),
		Category = "MyAsync"
	)
	static void LatentActorMovement(
		UObject* WorldContext,
		FLatentActionInfo LatentInfo,
		ELatentActionInputPins InputPins,
		ELatentActionOutputPins& OutputPins,
		UPARAM(ref) TArray<FVector>& PathPoints,
		AActor* ActorToMove,
		UPARAM(ref) bool& Grounded,
		float& Velocity
	);
};
USTRUCT()
struct FBoundarySphere
{
	GENERATED_BODY()
	FVector Center;
	float Radius;
	FVector EntranceLocation;
	FVector EntranceNormal;
	FVector ExitLocation;
	FVector ExitNormal;
};

class FLatentActorMovement : public FPendingLatentAction
{
public:
	//FLOW CTRL BOOLEANS
	bool bInit = true;
	bool bInterrupt = false;
	//LATENT ACTION REQUIRED
	UWorld* World;
	FLatentActionInfo LatentActionInfo;
	ELatentActionOutputPins& Output;
	
	TArray<FVector>& PathPoints;
	AActor* ActorToMove;
	bool& Grounded;

	int TargetPointIndex = 0;
	float& Velocity;

	bool bWithinBoundary = false;
	TArray<FBoundarySphere> BoundarySpheres;

	bool bStartTargetInit = true;
	
	bool Landing = false;

	FLatentActorMovement(
		UWorld* _World,
		FLatentActionInfo& LatentInfo, ELatentActionOutputPins& OutputPins,
		TArray<FVector>& _PathPoints, AActor* _ActorToMove, bool& _Grounded,
		float& _Velocity
	)
		: World(_World)
		, LatentActionInfo(LatentInfo)
		, Output(OutputPins)
		, PathPoints(_PathPoints)
		, ActorToMove(_ActorToMove)
		, Grounded(_Grounded)
		, Velocity(_Velocity)
	{
		Output = ELatentActionOutputPins::OnStarted;
		Velocity = 150.0f;
	}
	virtual void UpdateOperation(FLatentResponse& Response) override;
};