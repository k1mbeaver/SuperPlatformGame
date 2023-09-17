// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "MapDataTableClass.generated.h"

USTRUCT(BlueprintType)
struct FMapDataTable : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector MapPortalLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int NextMap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString strNextMap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString strMapName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int IsSide; // 1이 사이드 0은 기본

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTexture2D* MapImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString MapText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UMaterial* MapMaterial;
};

UCLASS()
class CAPSTONE_TEST_API AMapDataTableClass : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMapDataTableClass();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
