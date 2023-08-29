// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerPauseUI.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONE_TEST_API UPlayerPauseUI : public UUserWidget
{
	GENERATED_BODY()
	
private:
	UPROPERTY(Meta = (BindWidget))
		class UButton* BtExit;

	UPROPERTY(Meta = (BindWidget))
		class UButton* BtRestart;

	UPROPERTY(Meta = (BindWidget))
		class UButton* BtStage;

protected:
	virtual void NativeOnInitialized() override;

public:
	// 사용할 함수들을 정리
	UFUNCTION(BlueprintCallable)
		void GameRestart();

	UFUNCTION(BlueprintCallable)
		void GameExit();

	UFUNCTION(BlueprintCallable)
		void GameStage();
};
