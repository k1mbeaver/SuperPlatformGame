// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "AIDataTableClass.h"
#include "CharacterDataTableClass.h"
#include "ObjectDataTableClass.h"
#include "MapDataTableClass.h"
#include "SoundDataTableClass.h"
#include "ImageDataTableClass.h"
#include "MaterialDataTableClass.h"

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

	FString MapDataTable = TEXT("DataTable'/Game/DataTable/MapDataTable.MapDataTable'");

	static ConstructorHelpers::FObjectFinder<UDataTable> DT_MAPFILE(*MapDataTable);

	if (DT_MAPFILE.Succeeded())
	{
		FMapTable = DT_MAPFILE.Object;
	}

	FString ImageDataTable = TEXT("DataTable'/Game/DataTable/ImageDataTable.ImageDataTable'");

	static ConstructorHelpers::FObjectFinder<UDataTable> DT_IMAGEFILE(*ImageDataTable);

	if (DT_IMAGEFILE.Succeeded())
	{
		FImageTable = DT_IMAGEFILE.Object;
	}

	FString SoundDataTable = TEXT("DataTable'/Game/DataTable/SoundDataTable.SoundDataTable'");

	static ConstructorHelpers::FObjectFinder<UDataTable> DT_SOUNDFILE(*SoundDataTable);

	if (DT_SOUNDFILE.Succeeded())
	{
		FSoundTable = DT_SOUNDFILE.Object;
	}

	FString MaterialDataTable = TEXT("DataTable'/Game/DataTable/MaterialDatatTable.MaterialDatatTable'");

	static ConstructorHelpers::FObjectFinder<UDataTable> DT_MATERIALFILE(*MaterialDataTable);

	if (DT_MATERIALFILE.Succeeded())
	{
		FMaterialTable = DT_MATERIALFILE.Object;
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

FString UMyGameInstance::GetAIName(FString MonsterType)
{
	FAIDataTable* NameData = FAITable->FindRow<FAIDataTable>(*MonsterType, TEXT(""));
	FString myName = NameData->CharacterName;
	return myName;
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

int UMyGameInstance::GetCurrentStage()
{
	FCharacterDataTable* StageData = FCharacterTable->FindRow<FCharacterDataTable>("Player", TEXT(""));
	int myStage = StageData->CharacterStage;
	return myStage;
}

int UMyGameInstance::GetClearStage()
{
	FCharacterDataTable* StageData = FCharacterTable->FindRow<FCharacterDataTable>("Player", TEXT(""));
	int myStage = StageData->ClearStage;
	return myStage;
}

void UMyGameInstance::SetClearStage(int nStage)
{
	FCharacterDataTable* PlayerData = FCharacterTable->FindRow<FCharacterDataTable>("Player", TEXT(""));
	PlayerData->ClearStage = nStage;
}

void UMyGameInstance::SetCurrentStage(int nStage)
{
	FCharacterDataTable* PlayerData = FCharacterTable->FindRow<FCharacterDataTable>("Player", TEXT(""));
	PlayerData->CharacterStage = nStage;
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

USoundWave* UMyGameInstance::GetPlayerJumpSound()
{
	FCharacterDataTable* SoundWaveData = FCharacterTable->FindRow<FCharacterDataTable>("Player", TEXT(""));
	USoundWave* mySound = SoundWaveData->PlayerJumpSound;
	return mySound;
}

USoundWave* UMyGameInstance::GetPlayerBashSound()
{
	FCharacterDataTable* SoundWaveData = FCharacterTable->FindRow<FCharacterDataTable>("Player", TEXT(""));
	USoundWave* mySound = SoundWaveData->PlayerBashSound;
	return mySound;
}

USoundWave* UMyGameInstance::GetPlayerWalkSound()
{
	FCharacterDataTable* SoundWaveData = FCharacterTable->FindRow<FCharacterDataTable>("Player", TEXT(""));
	USoundWave* mySound = SoundWaveData->PlayerWalkSound;
	return mySound;
}

UStaticMesh* UMyGameInstance::GetObjStaticMesh(FString ObjType)
{
	FObjectDataTable* StaticMeshData = FObjectTable->FindRow<FObjectDataTable>(*ObjType, TEXT(""));
	UStaticMesh* myStatic = StaticMeshData->ObjectStaticMesh;
	return myStatic;
}

FString UMyGameInstance::GetObjectName(FString ObjType)
{
	FObjectDataTable* NameData = FObjectTable->FindRow<FObjectDataTable>(*ObjType, TEXT(""));
	FString myName = NameData->ObjectName;
	return myName;
}

float UMyGameInstance::GetObjectSpeed(FString ObjType)
{
	FObjectDataTable* SpeedData = FObjectTable->FindRow<FObjectDataTable>(*ObjType, TEXT(""));
	float mySpeed = SpeedData->ObjectSpeed;
	return mySpeed;
}

float UMyGameInstance::GetObjectDamage(FString ObjType)
{
	FObjectDataTable* DamageData = FObjectTable->FindRow<FObjectDataTable>(*ObjType, TEXT(""));
	float myDamage = DamageData->ObjectDamage;
	return myDamage;
}

FVector UMyGameInstance::GetMapPortal(int nMap)
{
	FString strMap = FString::FromInt(nMap);
	FMapDataTable* PortalData = FMapTable->FindRow<FMapDataTable>(*strMap, TEXT(""));
	FVector myMap = PortalData->MapPortalLocation;
	return myMap;
}

int UMyGameInstance::GetMapNext(int nMap)
{
	FString strMap = FString::FromInt(nMap);
	FMapDataTable* NextData = FMapTable->FindRow<FMapDataTable>(*strMap, TEXT(""));
	int myMap = NextData->NextMap;
	return myMap;
}

int UMyGameInstance::GetMapIsSide(int nMap)
{
	FString strMap = FString::FromInt(nMap);
	FMapDataTable* NextData = FMapTable->FindRow<FMapDataTable>(*strMap, TEXT(""));
	int myMap = NextData->IsSide;
	return myMap;
}

FString UMyGameInstance::GetMapStrNext(int nMap)
{
	FString strMap = FString::FromInt(nMap);
	FMapDataTable* NextData = FMapTable->FindRow<FMapDataTable>(*strMap, TEXT(""));
	FString myMap = NextData->strNextMap;
	return myMap;
}

FString UMyGameInstance::GetMapName(int nMap)
{
	FString strMap = FString::FromInt(nMap);
	FMapDataTable* NameData = FMapTable->FindRow<FMapDataTable>(*strMap, TEXT(""));
	FString myMap = NameData->strMapName;
	return myMap;
}

UTexture2D* UMyGameInstance::GetMapImage(int nMap)
{
	FString strMap = FString::FromInt(nMap);
	FMapDataTable* ImageData = FMapTable->FindRow<FMapDataTable>(*strMap, TEXT(""));
	UTexture2D* myMap = ImageData->MapImage;
	return myMap;
}

UMaterial* UMyGameInstance::GetMapMaterial(int nMap)
{
	FString strMap = FString::FromInt(nMap);
	FMapDataTable* MaterialData = FMapTable->FindRow<FMapDataTable>(*strMap, TEXT(""));
	UMaterial* myMap = MaterialData->MapMaterial;
	return myMap;
}

FString UMyGameInstance::GetMapText(int nMap)
{
	FString strMap = FString::FromInt(nMap);
	FMapDataTable* TextData = FMapTable->FindRow<FMapDataTable>(*strMap, TEXT(""));
	FString myText = TextData->MapText;
	return myText;
}

UTexture2D* UMyGameInstance::GetImage(FString ImageName)
{
	FImageDataTable* ImageData = FImageTable->FindRow<FImageDataTable>(*ImageName, TEXT(""));
	UTexture2D* myImage = ImageData->myImage;
	return myImage;
}

USoundWave* UMyGameInstance::GetSound(FString SoundName)
{
	FSoundDataTable* SoundData = FSoundTable->FindRow<FSoundDataTable>(*SoundName, TEXT(""));
	USoundWave* mySound = SoundData->mySound;
	return mySound;
}

float UMyGameInstance::GetSoundVolume(FString SoundName)
{
	FSoundDataTable* SoundData = FSoundTable->FindRow<FSoundDataTable>(*SoundName, TEXT(""));
	float mySound = SoundData->mySoundVolume;
	return mySound;
}

void UMyGameInstance::SetSoundVolume(FString SoundName, float mySound)
{
	FSoundDataTable* PlayerData = FSoundTable->FindRow<FSoundDataTable>(*SoundName, TEXT(""));
	PlayerData->mySoundVolume = mySound;
}

UMaterialInterface* UMyGameInstance::GetMaterial(FString MaterialName)
{
	FMaterialDataTable* MaterialData = FMaterialTable->FindRow<FMaterialDataTable>(*MaterialName, TEXT(""));
	UMaterialInterface* myMaterial = MaterialData->ObjectMaterial;
	return myMaterial;
}