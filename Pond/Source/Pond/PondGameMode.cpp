// Copyright Epic Games, Inc. All Rights Reserved.

#include "PondGameMode.h"
#include "PondCharacter.h"
#include "UObject/ConstructorHelpers.h"

APondGameMode::APondGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Script/Engine.Blueprint'/Game/UserContent/BP_MyCharacter.BP_MyCharacter_C'"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerClassFinder(TEXT("/Script/Engine.Blueprint'/Game/UserContent/BP_MyPlayerController.BP_MyPlayerController_C'"));
	PlayerControllerClass = PlayerControllerClassFinder.Class;
}
