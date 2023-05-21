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
	// ĳ���� ü��?
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float CharacterHP;

	// ĳ���� ���ݷ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float CharacterDamage;

	// ĳ���� �ӵ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float CharacterSpeed;

	// ĳ���� �޽�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USkeletalMesh* CharacterMesh;
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
