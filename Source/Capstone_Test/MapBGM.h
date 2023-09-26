// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Sound/AmbientSound.h"
#include "MapBGM.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONE_TEST_API AMapBGM : public AAmbientSound
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Type)
		FString strMap;
	
	AMapBGM();
protected:

	virtual void Tick(float DeltaTime) override;
	// End of APawn interface

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
