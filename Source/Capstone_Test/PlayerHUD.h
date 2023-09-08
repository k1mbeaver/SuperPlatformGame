// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "PlayerHUD.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONE_TEST_API APlayerHUD : public AHUD
{
	GENERATED_BODY()

public:
	APlayerHUD();
	virtual void BeginPlay() override;

public:
	// 함수 정리
	void SetCharacterCount(int nCount);
	void SetCoinCount(int nCount);
	void SetGemCount(int nCount);
	void SetStarCount(int nCount);
	void SetPlayMode(bool bActive);
	void SetStageMode(bool bActive);
	void SetStage(int nStage);
	void GameRestart();
	void GameExit();
	void GameStage();
	void SettingPauseVisible(bool Istrue);
	void VisibleLoading(bool bIstrue);
	void SetLoadingImage(int nMap);
	void SetLoadingText(int nMap);
	void InitProgressBar();
private:
	TSubclassOf<class UPlayerMainUI> MainUIClass;
	class UPlayerMainUI* MainUIObject;

private:
	bool CheckUIObject();
	bool CreateUIObject();
	
};
