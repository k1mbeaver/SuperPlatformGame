// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StageScreen.generated.h"

UCLASS()
class CAPSTONE_TEST_API AStageScreen : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStageScreen();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	AActor* GetPlayer;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Bash, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* ImageSquare;

	int CurrentPlayerStage;
	int CurrentSelectStage;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
		void SetImage(int nMap);

	UFUNCTION(BlueprintCallable)
		void ImageOnOff(bool bOnOff);
};
