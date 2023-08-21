// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SelectStage.generated.h"

UCLASS()
class CAPSTONE_TEST_API ASelectStage : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* OnStaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Type)
		FString strStageNumber;

	UPROPERTY()
		class UGameplayStatics* GameStatic;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Type)
		bool bOnPlayer; // Up = true, Down = false;

	class UMyGameInstance* myGameInstance;

public:	
	// Sets default values for this actor's properties
	ASelectStage();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
		void OnStage();

	UFUNCTION(BlueprintCallable)
		void OffStage();

};