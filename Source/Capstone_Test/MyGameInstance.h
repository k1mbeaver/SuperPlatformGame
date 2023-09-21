// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

struct FAIDataTable;
struct FObjectDataTable;
struct FCharacterDataTable;
struct FMapDataTable;
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

	// 플레이어 데이터 값 얻어오기
	UAnimMontage* GetPlayerDiveMontage();
	float GetPlayerHP();
	float GetPlayerSpeed();
	float GetPlayerDamage();
	USkeletalMesh* GetPlayerSkeletalMesh();
	TSubclassOf<class UAnimInstance> GetPlayerAnimInstance();
	int GetPlayerLife();
	int GetPlayerStar();
	int GetPlayerCoin();
	int GetPlayerGem();
	int GetCurrentStage();
	int GetClearStage();
	//UParticleSystem* GetPlayerBashParticle();
	void SetPlayerLife(int nLife);
	void SetPlayerStar(int nStar);
	void SetPlayerCoin(int nCoin);
	void SetPlayerGem(int nGem);
	void SetCurrentStage(int nStage);
	void SetClearStage(int nStage);
	USoundWave* GetPlayerJumpSound();
	USoundWave* GetPlayerBashSound();
	USoundWave* GetPlayerWalkSound();


	// AI 몬스터 데이터 얻어오기
	USkeletalMesh* GetAISkeletalMesh(FString MonsterType);
	TSubclassOf<class UAnimInstance> GetAIAnimInstance(FString MonsterType);
	float GetAISpeed(FString MonsterType);
	float GetAIHP(FString MonsterType);
	UAnimMontage* GetAIAttackMontage(FString MonsterType);
	FString GetAIName(FString MonsterType);

	// Object 데이터 값 얻어오기
	UStaticMesh* GetObjStaticMesh(FString ObjType);
	float GetObjectSpeed(FString ObjType);
	FString GetObjectName(FString ObjType);
	float GetObjectDamage(FString ObjType);

	// Map 데이터 값 얻어오기
	FVector GetMapPortal(int nMap);
	int GetMapNext(int nMap);
	FString GetMapStrNext(int nMap);
	FString GetMapName(int nMap);
	int GetMapIsSide(int nMap);
	UTexture2D* GetMapImage(int nMap);
	FString GetMapText(int nMap);
	UMaterial* GetMapMaterial(int nMap);

	// Image 데이터 값 얻어오기
	UTexture2D* GetImage(FString ImageName);

	// Sound 데이터 값 얻어오기
	USoundWave* GetSound(FString SoundName);

private:
	UPROPERTY()
		UDataTable* FAITable;

	UPROPERTY()
		UDataTable* FObjectTable;

	UPROPERTY()
		UDataTable* FCharacterTable;

	UPROPERTY()
		UDataTable* FMapTable;

	UPROPERTY()
		UDataTable* FImageTable;

	UPROPERTY()
		UDataTable* FSoundTable;
};
