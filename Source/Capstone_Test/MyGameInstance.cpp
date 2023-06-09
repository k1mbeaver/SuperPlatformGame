// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "AIDataTableClass.h"
#include "CharacterDataTableClass.h"
#include "ObjectDataTableClass.h"

UMyGameInstance::UMyGameInstance()
{
	FString AIFileDataTable = TEXT("DataTable'/Game/DataTable/AIDataTable.AIDataTable'");

	static ConstructorHelpers::FObjectFinder<UDataTable> DT_AIFILE(*AIFileDataTable);

	if (DT_AIFILE.Succeeded())
	{
		FAITable = DT_AIFILE.Object;
	}

	FString CharacterFileDataTable = TEXT("DataTable'/Game/DataTable/CharacterDataTable.CharacterDataTable'");

	static ConstructorHelpers::FObjectFinder<UDataTable> DT_CHARACTERFILE(*CharacterFileDataTable);

	if (DT_CHARACTERFILE.Succeeded())
	{
		FCharacterTable = DT_CHARACTERFILE.Object;
	}
}

USkeletalMesh* UMyGameInstance::GetAISkeletalMesh(FString MonsterType)
{
	FAIDataTable* SkeletalData = FAITable->FindRow<FAIDataTable>(*MonsterType, TEXT(""));
	USkeletalMesh* mySkeletalMesh = SkeletalData->CharacterMesh;
	return mySkeletalMesh;
}

TSubclassOf<class UAnimInstance> UMyGameInstance::GetAIAnimInstance(FString MonsterType)
{
	FAIDataTable* AnimData = FAITable->FindRow<FAIDataTable>(*MonsterType, TEXT(""));
	TSubclassOf<class UAnimInstance> myAnimInstance = AnimData->MyAnimation;
	return myAnimInstance;
}

float UMyGameInstance::GetAISpeed(FString MonsterType)
{
	FAIDataTable* SpeedData = FAITable->FindRow<FAIDataTable>(*MonsterType, TEXT(""));
	float mySpeed = SpeedData->CharacterSpeed;
	return mySpeed;
}

UAnimMontage* UMyGameInstance::GetAIAttackMontage(FString MonsterType)
{
	FAIDataTable* MontageData = FAITable->FindRow<FAIDataTable>(*MonsterType, TEXT(""));
	UAnimMontage* myMontage = MontageData->AttackMontage;
	return myMontage;
}

UAnimMontage* UMyGameInstance::GetPlayerDiveMontage()
{
	FCharacterDataTable* MontageData = FCharacterTable->FindRow<FCharacterDataTable>("Player", TEXT(""));
	UAnimMontage* myMontage = MontageData->DiveMontage;
	return myMontage;
}