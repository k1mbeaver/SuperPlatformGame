// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

struct FAIDataTable;
struct FObjectDataTable;
struct FCharacterDataTable;
class UDataTable;

/**
 * 
 */
UCLASS()
class CAPSTONE_TEST_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UMyGameInstance();

	// �÷��̾� ������ �� ������
	UAnimMontage* GetPlayerDiveMontage();

	// AI ���� ������ ������
	USkeletalMesh* GetAISkeletalMesh(FString MonsterType);
	TSubclassOf<class UAnimInstance> GetAIAnimInstance(FString MonsterType);
	float GetAISpeed(FString MonsterType);

private:
	UPROPERTY()
		UDataTable* FAITable;

	UPROPERTY()
		UDataTable* FObjectTable;

	UPROPERTY()
		UDataTable* FCharacterTable;
};
