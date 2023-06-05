// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "AIDataTableClass.generated.h"

USTRUCT(BlueprintType)
struct FAIDataTable : public FTableRowBase
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
};

UCLASS()
class CAPSTONE_TEST_API AAIDataTableClass : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAIDataTableClass();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
