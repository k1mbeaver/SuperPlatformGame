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

	UPROPERTY(Meta = (BindWidget))
		class UTextBlock* TextDead;

	ACapstone_TestCharacter* myCharacter;

	TArray<UButton*> BtArray;
	int BtSequence;
protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
public:
	// 사용할 함수들을 정리
	UFUNCTION(BlueprintCallable)
		void GameRestart();

	UFUNCTION(BlueprintCallable)
		void GameExit();

	UFUNCTION(BlueprintCallable)
		void GameStage();

	UFUNCTION(BlueprintCallable)
		void MenuUp();

	UFUNCTION(BlueprintCallable)
		void MenuDown();

	UFUNCTION(BlueprintCallable)
		void GameDead(bool bVisible);
};
