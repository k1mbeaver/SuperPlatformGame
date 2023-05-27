// Copyright Epic Games, Inc. All Rights Reserved.

#include "Capstone_TestGameMode.h"
#include "Capstone_TestCharacter.h"
#include "UObject/ConstructorHelpers.h"

ACapstone_TestGameMode::ACapstone_TestGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/BluePrint/BP_ThirdPersonCharacter"));
	//
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
