// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "MaterialDataTableClass.generated.h"

USTRUCT(BlueprintType)
struct FMaterialDataTable : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	// Material
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UMaterialInterface* ObjectMaterial;
};

UCLASS()
class CAPSTONE_TEST_API AMaterialDataTableClass : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMaterialDataTableClass();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
