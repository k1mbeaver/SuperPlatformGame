// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BashObject.generated.h"

UCLASS()
class CAPSTONE_TEST_API ABashObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABashObject();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = State)
		bool bLight = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = State)
		bool bMission = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = State)
		int nCustomCount = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = State)
		int nMissionCount = 1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Bash, meta = (AllowPrivateAccess = "true"))
		class USphereComponent* BashCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Bash, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* BashSphere;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Material, Meta = (AllowPrivateAccess = true))
		class UMaterialInterface* ActivatedMaterial;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Material, Meta = (AllowPrivateAccess = true))
		class UMaterialInterface* DeActivatedMaterial;

private:
	int nCount = 0;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
		void OnActivated();

	UFUNCTION(BlueprintCallable)
		void OnDeActivated();

	UFUNCTION(BlueprintCallable)
		void PlayMission(int myMissionCount);
};
