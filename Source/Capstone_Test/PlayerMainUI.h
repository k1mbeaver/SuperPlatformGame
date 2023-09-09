// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerMainUI.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONE_TEST_API UPlayerMainUI : public UUserWidget
{
	GENERATED_BODY()

		
	UPROPERTY(Meta = (BindWidget))
		class UPlayerPlayUI* UW_PlayerPlay;

	UPROPERTY(Meta = (BindWidget))
		class UPlayerStageUI* UW_PlayerStage;

	UPROPERTY(Meta = (BindWidget))
		class UPlayerPauseUI* UW_PlayerPause;

	UPROPERTY(Meta = (BindWidget))
		class UPlayerLoadingUI* UW_PlayerLoading;

	float CurrentLoading = 0.0f;
public:
	// PlayUI
	void SetCharacterCount(int nCount);
	void SetCoinCount(int nCount);
	void SetGemCount(int nCount);
	void SetStarCount(int nCount);
	void SetPlayMode(bool bActive);

	// StageUI
	void SetStageMode(bool bActive);
	void SetStage(int nStage);

	// PauseUI
	void GameRestart();
	void GameExit();
	void GameStage();
	void SettingPauseVisible(bool Istrue);

	// LoadingUI
	void VisibleLoading(bool bVisible);
	void SetLoadingImage(int nMap);
	void SetLoadingText(int nMap);
	void InitProgressBar();
	UFUNCTION(BlueprintCallable)
		void EngagePercent();
};
