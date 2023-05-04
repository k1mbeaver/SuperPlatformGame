// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONE_TEST_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()

		AMyPlayerController();

private:
	class ACapstone_TestCharacter* myCharacter;
public:
	virtual void OnPossess(APawn* aPawn) override;
	virtual void PostInitializeComponents() override; // 여기서 빙의되는지 알 수 있음
	virtual void SetupInputComponent() override;
	virtual void Tick(float DeltaTime) override;

private:
	void MoveForward(float NewAxisValue);
	void MoveRight(float NewAxisValue);
	void Run();
	void StopRun();
	void Crouch();
	void StopCrouch();
	void CharacterDown();
	void StopDown();
	void Bash();
	void StopBash();
};
