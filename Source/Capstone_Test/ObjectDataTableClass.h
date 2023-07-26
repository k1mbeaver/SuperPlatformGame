// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "ObjectDataTableClass.generated.h"

USTRUCT(BlueprintType)
struct FObjectDataTable : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	// ������Ʈ ü��?
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float ObjectHP;

	// ������Ʈ ���ݷ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float ObjectDamage;

	// ������Ʈ �̵��ӵ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float ObjectSpeed;

	// ������Ʈ �̸�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString ObjectName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMesh* ObjectStaticMesh;
};

UCLASS()
class CAPSTONE_TEST_API AObjectDataTableClass : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AObjectDataTableClass();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
