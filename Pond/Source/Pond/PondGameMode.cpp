// Copyright Epic Games, Inc. All Rights Reserved.

#include "PondGameMode.h"
#include "UnusedBoilerplate/PondCharacter.h"
#include "UObject/ConstructorHelpers.h"

APondGameMode::APondGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Script/Engine.Blueprint'/Game/MyContent/Blueprints/BP_MyPawn.BP_MyPawn_C'"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerClassFinder(TEXT("/Script/Engine.Blueprint'/Game/MyContent/Blueprints/BP_MyPlayerController.BP_MyPlayerController_C'"));
	PlayerControllerClass = PlayerControllerClassFinder.Class;
}
