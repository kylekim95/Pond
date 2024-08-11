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
	Cancel
};
UENUM()
enum class ELatentActionOutputPins : uint8
{
	OnStarted,
	OnCancelled,
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
		const TArray<FVector>& Path,
		UPARAM(ref) AActor* Actor,
		TArray<FVector>& BoundaryNormals,
		TArray<FVector>& PointsOnBoundary,
		float& CurrentVelocity
	);
};

class FLatentActorMovement : public FPendingLatentAction
{
public:
	//FLOW CTRL BOOLEANS
	bool bInit = true;
	bool bCancel = false;

	//REQUIRED
	FLatentActionInfo LatentActionInfo;
	ELatentActionOutputPins& Output;

	//WORLD
	UWorld* World;

	//INPUT
	const TArray<FVector>& Path;
	AActor* Actor;

	//VARS
	TArray<FVector>& BoundaryNormals;
	TArray<FVector>& PointsOnBoundary;
	float TurnDistance;
	int TargetPointIndex;
	float& CurrentVelocity;
	float MaxVelocity;
	float AngularVelocity;

	FLatentActorMovement(
		FLatentActionInfo& LatentInfo, ELatentActionOutputPins& OutputPins, 
		UWorld* _World,
		const TArray<FVector>& _Path, AActor* _Actor,
		TArray<FVector>& _BoundaryNormals, TArray<FVector>& _PointsOnBoundary, float& _CurrentVelocity
	)
		: LatentActionInfo(LatentInfo)
		, Output(OutputPins)
		, World(_World)
		, Path(_Path)
		, Actor(_Actor)
		, BoundaryNormals(_BoundaryNormals)
		, PointsOnBoundary(_PointsOnBoundary)
		, CurrentVelocity(_CurrentVelocity)
	{
		Output = ELatentActionOutputPins::OnStarted;
		TurnDistance = 100.0f;
		TargetPointIndex = 1;
		AngularVelocity = 20.0f;
		CurrentVelocity = 0.0f;
		MaxVelocity = 100.0f;
	}
	virtual void UpdateOperation(FLatentResponse& Response) override;
};