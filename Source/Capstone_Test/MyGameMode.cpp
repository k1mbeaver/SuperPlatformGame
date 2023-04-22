// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameMode.h"
#include "MyPlayerController.h"

AMyGameMode::AMyGameMode()
//: Super()
{
	// set default pawn class to our Blueprinted character
	//DefaultPawnClass = AMyCharacter::StaticClass();
	//DefaultPawnClass = APlayerCharacter::StaticClass();

	//static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("Blueprint'/Game/Blueprints/PlayerCharacter.PlayerCharacter_C'"));
	//DefaultPawnClass = PlayerPawnClassFinder.Class;

	// PlayerController
	PlayerControllerClass = AMyPlayerController::StaticClass();
}

void AMyGameMode::PostLogin(APlayerController* NewPlayer)
{
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("PostLogin Begin"));
	Super::PostLogin(NewPlayer);
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("PostLogin End"));
}
