// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyPortal.generated.h"

UCLASS()
class CAPSTONE_TEST_API AMyPortal : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyPortal();

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = Niagara, Meta = (AllowPrivateAccess = true))
		class UNiagaraComponent* PortalCloseNiagara;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = Niagara, Meta = (AllowPrivateAccess = true))
		class UNiagaraComponent* PortalOpenNiagara;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = Niagara, Meta = (AllowPrivateAccess = true))
		class UCapsuleComponent* CapsuleComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = Clear, Meta = (AllowPrivateAccess = true))
		bool bClear;

	class UMyGameInstance* myGameInstance;

	UPROPERTY()
		class UGameplayStatics* GameStatic;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = Sound, Meta = (AllowPrivateAccess = true))
		class USoundWave* PortalSound;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
		void PlayerClear();

	UFUNCTION(BlueprintCallable)
		void NextMap();

	UFUNCTION(BlueprintCallable)
		void PlaySound();
};
