// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "AProjectGameMode.h"
#include "AAPlayerPawn.h"
#include "AAPlayerController.h"

AAProjectGameMode::AAProjectGameMode()
{
	// set default pawn class to our character class
	DefaultPawnClass = AAAPlayerPawn::StaticClass();
	PlayerControllerClass = AAAPlayerController::StaticClass();
}

