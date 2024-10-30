// Copyright Epic Games, Inc. All Rights Reserved.

#include "VRFINALTESTINGGameMode.h"
#include "VRFINALTESTINGCharacter.h"
#include "UObject/ConstructorHelpers.h"

AVRFINALTESTINGGameMode::AVRFINALTESTINGGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
