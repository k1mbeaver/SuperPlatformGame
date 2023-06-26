// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerMainUI.h"
#include "PlayerPlayUI.h"

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