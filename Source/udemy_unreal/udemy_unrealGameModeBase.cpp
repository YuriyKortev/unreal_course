// Copyright Epic Games, Inc. All Rights Reserved.


#include "udemy_unrealGameModeBase.h"

#include "SandboxPlayerController.h"
#include "SandboxPawn.h"

Audemy_unrealGameModeBase::Audemy_unrealGameModeBase()
{
	DefaultPawnClass = ASandboxPawn::StaticClass();
	PlayerControllerClass = ASandboxPlayerController::StaticClass();
}
