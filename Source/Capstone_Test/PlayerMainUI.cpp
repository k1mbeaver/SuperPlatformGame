// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerMainUI.h"
#include "PlayerPlayUI.h"
#include "PlayerStageUI.h"
#include "PlayerPauseUI.h"

void UPlayerMainUI::SetCharacterCount(int nCount)
{
	UW_PlayerPlay->SetCharacterCount(nCount);
}

void UPlayerMainUI::SetCoinCount(int nCount)
{
	UW_PlayerPlay->SetCoinCount(nCount);
}

void UPlayerMainUI::SetGemCount(int nCount)
{
	UW_PlayerPlay->SetGemCount(nCount);
}

void UPlayerMainUI::SetStarCount(int nCount)
{
	UW_PlayerPlay->SetStarCount(nCount);
}

void UPlayerMainUI::SetPlayMode(bool bActive)
{
	if (bActive)
	{
		UW_PlayerPlay->SetVisibility(ESlateVisibility::Visible);
	}

	else
	{
		UW_PlayerPlay->SetVisibility(ESlateVisibility::Hidden);
	}
}


void UPlayerMainUI::SetStageMode(bool bActive)
{
	if (bActive)
	{
		UW_PlayerStage->SetVisibility(ESlateVisibility::Visible);
	}

	else
	{
		UW_PlayerStage->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UPlayerMainUI::SetStage(int nStage)
{
	UW_PlayerStage->SetStage(nStage);
}

void UPlayerMainUI::GameRestart()
{
	UW_PlayerPause->GameRestart();
}

void UPlayerMainUI::GameExit()
{
	UW_PlayerPause->GameExit();
}

void UPlayerMainUI::GameStage()
{
	UW_PlayerPause->GameStage();
}

void UPlayerMainUI::SettingPauseVisible(bool Istrue)
{
	if (Istrue)
	{
		UW_PlayerPause->SetVisibility(ESlateVisibility::Visible);
	}

	else
	{
		UW_PlayerPause->SetVisibility(ESlateVisibility::Hidden);
	}
}