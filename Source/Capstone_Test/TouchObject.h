// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TouchObject.generated.h"

UCLASS()
class CAPSTONE_TEST_API ATouchObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATouchObject();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = State)
		bool bTouch = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = State)
		int nTouchNumber = 1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Bash, meta = (AllowPrivateAccess = "true"))
		class USphereComponent* TouchCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Bash, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* TouchStaticMesh;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = Sound, Meta = (AllowPrivateAccess = true))
		class USoundWave* ActiveSound;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	float SoundVolume = 0;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
		int GetTouchNumber();

	UFUNCTION(BlueprintCallable)
		void PlayActivatedSound();

};
