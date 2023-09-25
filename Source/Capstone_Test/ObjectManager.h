// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ObjectManager.generated.h"

UCLASS()
class CAPSTONE_TEST_API AObjectManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AObjectManager();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Type)
		FString strObjectType;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = Sound, Meta = (AllowPrivateAccess = true))
		class USoundWave* ObjectSound;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
		void InitObj(UStaticMeshComponent* myStaticMesh);

	UFUNCTION(BlueprintCallable)
		void PlaySound();

private:
	float SoundVolume;
};
