// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingObject.generated.h"

UCLASS()
class CAPSTONE_TEST_API AMovingObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMovingObject();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Type)
		FString strObjectType;

	UPROPERTY()
		class UGameplayStatics* GameStatic;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Type)
		int nMaxHeight;

	class UMyGameInstance* myGameInstance;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
		void InitMaxHeight();

	UFUNCTION(BlueprintCallable)
		void IncreaseMaxHeight();
};
