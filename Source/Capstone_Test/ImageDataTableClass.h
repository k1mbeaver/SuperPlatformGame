// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "ImageDataTableClass.generated.h"

USTRUCT(BlueprintType)
struct FImageDataTable : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	// »ç¿îµå
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTexture2D* myImage;
};

UCLASS()
class CAPSTONE_TEST_API AImageDataTableClass : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AImageDataTableClass();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
