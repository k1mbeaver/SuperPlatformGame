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
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("PossessPlayer"));
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

	// 캐릭터 달리기
	InputComponent->BindAction(TEXT("Run"), IE_Pressed, this, &AMyPlayerController::Run);
	InputComponent->BindAction(TEXT("Run"), IE_Released, this, &AMyPlayerController::StopRun);

	// 캐릭터 웅크리기
	InputComponent->BindAction(TEXT("Crouch"), IE_Pressed, this, &AMyPlayerController::Crouch);
	InputComponent->BindAction(TEXT("Crouch"), IE_Released, this, &AMyPlayerController::StopCrouch);

	// 캐릭터 엎드리기
	InputComponent->BindAction(TEXT("CharacterDown"), IE_Pressed, this, &AMyPlayerController::CharacterDown);
	InputComponent->BindAction(TEXT("CharacterDown"), IE_Released, this, &AMyPlayerController::StopDown);

	InputComponent->BindAction(TEXT("Bash"), IE_Pressed, this, &AMyPlayerController::Bash);
	InputComponent->BindAction(TEXT("Bash"), IE_Released, this, &AMyPlayerController::StopBash);
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

void AMyPlayerController::Run()
{
	if (myCharacter)
	{
		myCharacter->Run();
	}
}

void AMyPlayerController::StopRun()
{
	if (myCharacter)
	{
		myCharacter->StopRun();
	}
}

void AMyPlayerController::Crouch()
{
	if (myCharacter)
	{
		myCharacter->Crouch();
	}
}

void AMyPlayerController::StopCrouch()
{
	if (myCharacter)
	{
		myCharacter->StopCrouch();
	}
}

void AMyPlayerController::CharacterDown()
{
	if (myCharacter)
	{
		myCharacter->CharacterDown();
	}
}

void AMyPlayerController::StopDown()
{
	if (myCharacter)
	{
		myCharacter->StopDown();
	}
}

void AMyPlayerController::Bash()
{
	if (myCharacter)
	{
		myCharacter->Bash();
	}
}

void AMyPlayerController::StopBash()
{
	if (myCharacter)
	{
		myCharacter->StopBash();
	}
}
