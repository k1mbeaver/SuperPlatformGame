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

	FString ObjFileDataTable = TEXT("DataTable'/Game/DataTable/ObjectDataTable.ObjectDataTable'");

	static ConstructorHelpers::FObjectFinder<UDataTable> DT_OBJFILE(*ObjFileDataTable);

	if (DT_OBJFILE.Succeeded())
	{
		FObjectTable = DT_OBJFILE.Object;
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

float UMyGameInstance::GetAIHP(FString MonsterType)
{
	FAIDataTable* HPData = FAITable->FindRow<FAIDataTable>(*MonsterType, TEXT(""));
	float myHP = HPData->CharacterHP;
	return myHP;
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

float UMyGameInstance::GetPlayerHP()
{
	FCharacterDataTable* HPData = FCharacterTable->FindRow<FCharacterDataTable>("Player", TEXT(""));
	float myHP = HPData->CharacterHP;
	return myHP;
}

float UMyGameInstance::GetPlayerSpeed()
{
	FCharacterDataTable* SpeedData = FCharacterTable->FindRow<FCharacterDataTable>("Player", TEXT(""));
	float mySpeed = SpeedData->CharacterSpeed;
	return mySpeed;
}

float UMyGameInstance::GetPlayerDamage()
{
	FCharacterDataTable* DamageData = FCharacterTable->FindRow<FCharacterDataTable>("Player", TEXT(""));
	float myDamage = DamageData->CharacterDamage;
	return myDamage;
}

int UMyGameInstance::GetPlayerLife()
{
	FCharacterDataTable* LifeData = FCharacterTable->FindRow<FCharacterDataTable>("Player", TEXT(""));
	int myLife = LifeData->CharacterLife;
	return myLife;
}

int UMyGameInstance::GetPlayerStar()
{
	FCharacterDataTable* StarData = FCharacterTable->FindRow<FCharacterDataTable>("Player", TEXT(""));
	int myStar = StarData->CharacterStar;
	return myStar;
}

int UMyGameInstance::GetPlayerCoin()
{
	FCharacterDataTable* CoinData = FCharacterTable->FindRow<FCharacterDataTable>("Player", TEXT(""));
	int myCoin = CoinData->CharacterCoin;
	return myCoin;
}

//UParticleSystem* UMyGameInstance::GetPlayerBashParticle()
//{
	//FCharacterDataTable* ParticleData = FCharacterTable->FindRow<FCharacterDataTable>("Player", TEXT(""));
	//UParticleSystem* myParticle = ParticleData->CharacterBashParticle;
	//return myParticle;
//}

int UMyGameInstance::GetPlayerGem()
{
	FCharacterDataTable* GemData = FCharacterTable->FindRow<FCharacterDataTable>("Player", TEXT(""));
	int myGem = GemData->CharacterGem;
	return myGem;
}

void UMyGameInstance::SetPlayerLife(int nLife)
{
	FCharacterDataTable* PlayerData = FCharacterTable->FindRow<FCharacterDataTable>("Player", TEXT(""));
	PlayerData->CharacterLife = nLife;
}

void UMyGameInstance::SetPlayerGem(int nGem)
{
	FCharacterDataTable* PlayerData = FCharacterTable->FindRow<FCharacterDataTable>("Player", TEXT(""));
	PlayerData->CharacterGem = nGem;
}

void UMyGameInstance::SetPlayerStar(int nStar)
{
	FCharacterDataTable* PlayerData = FCharacterTable->FindRow<FCharacterDataTable>("Player", TEXT(""));
	PlayerData->CharacterStar = nStar;
}

void UMyGameInstance::SetPlayerCoin(int nCoin)
{
	FCharacterDataTable* PlayerData = FCharacterTable->FindRow<FCharacterDataTable>("Player", TEXT(""));
	PlayerData->CharacterCoin = nCoin;
}


USkeletalMesh* UMyGameInstance::GetPlayerSkeletalMesh()
{
	FCharacterDataTable* SkeletalMeshData = FCharacterTable->FindRow<FCharacterDataTable>("Player", TEXT(""));
	USkeletalMesh* mySkeletal = SkeletalMeshData->CharacterMesh;
	return mySkeletal;
}

TSubclassOf<class UAnimInstance> UMyGameInstance::GetPlayerAnimInstance()
{
	FCharacterDataTable* AnimationData = FCharacterTable->FindRow<FCharacterDataTable>("Player", TEXT(""));
	TSubclassOf<class UAnimInstance> myAnimation = AnimationData->MyAnimation;
	return myAnimation;
}

UStaticMesh* UMyGameInstance::GetObjStaticMesh(FString ObjType)
{
	FObjectDataTable* StaticMeshData = FObjectTable->FindRow<FObjectDataTable>(*ObjType, TEXT(""));
	UStaticMesh* myStatic = StaticMeshData->ObjectStaticMesh;
	return myStatic;
}