// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "CharacterDataTableClass.generated.h"

USTRUCT(BlueprintType)
struct FCharacterDataTable : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	// 캐릭터 체력?
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float CharacterHP;

	// 캐릭터 공격력
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float CharacterDamage;

	// 캐릭터 속도
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float CharacterSpeed;

	// 캐릭터 메쉬
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USkeletalMesh* CharacterMesh;

	// 캐릭터 애님 인스턴스
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class UAnimInstance> MyAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UAnimMontage* DiveMontage;

	// 캐릭터 코인
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int CharacterCoin;

	// 캐릭터 젬
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int CharacterGem;

	// 캐릭터 스타
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int CharacterStar;

	// 캐릭터 목숨
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int CharacterLife;

	// 캐릭터 파티클
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
		//UNiagaraSystem* CharacterBashParticle;
};

UCLASS()
class CAPSTONE_TEST_API ACharacterDataTableClass : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACharacterDataTableClass();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
