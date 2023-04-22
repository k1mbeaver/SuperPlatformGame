// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Capstone_TestCharacter.h"
#include "Kismet/KismetMathLibrary.h"

AMyPlayerController::AMyPlayerController()
{

}

void AMyPlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

	myCharacter = Cast<ACapstone_TestCharacter>(aPawn);
}

void AMyPlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();

}

void AMyPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
}

void AMyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// 캐릭터 이동 함수
	InputComponent->BindAxis(TEXT("Move Forward / Backward"), this, &AMyPlayerController::MoveForward);
	InputComponent->BindAxis(TEXT("Move Right / Left"), this, &AMyPlayerController::MoveRight);
}

void AMyPlayerController::MoveForward(float NewAxisValue)
{
	if (myCharacter)
	{
		myCharacter->MoveForward(NewAxisValue);
	}
}

void AMyPlayerController::MoveRight(float NewAxisValue)
{
	if (myCharacter)
	{
		myCharacter->MoveRight(NewAxisValue);
	}
}