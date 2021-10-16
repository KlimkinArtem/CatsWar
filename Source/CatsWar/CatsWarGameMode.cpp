// Copyright Epic Games, Inc. All Rights Reserved.

#include "CatsWarGameMode.h"
#include "CatsWarCharacter.h"
#include "UObject/ConstructorHelpers.h"

ACatsWarGameMode::ACatsWarGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
