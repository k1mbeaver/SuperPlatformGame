// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPlayUI.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "MyGameInstance.h"


void UPlayerPlayUI::NativeOnInitialized()
{
	TextCharacterCount = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextCharacterCount")));
	TextCoinCount = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextCoinCount")));
	TextGemCount = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextGemCount")));
	TextStarCount = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextStarCount")));
}

void UPlayerPlayUI::SetCharacterCount(int nCount)
{
	FString nToString = FString::FromInt(nCount);
	FText strToft = FText::FromString(nToString);
	TextCharacterCount->SetText(strToft);
}

void UPlayerPlayUI::SetCoinCount(int nCount)
{
	FString nToString = FString::FromInt(nCount);
	FText strToft = FText::FromString(nToString);
	TextCoinCount->SetText(strToft);
}

void UPlayerPlayUI::SetGemCount(int nCount)
{
	FString nToString = FString::FromInt(nCount);
	FText strToft = FText::FromString(nToString);
	TextGemCount->SetText(strToft);
}

void UPlayerPlayUI::SetStarCount(int nCount)
{
	FString nToString = FString::FromInt(nCount);
	FText strToft = FText::FromString(nToString);
	TextStarCount->SetText(strToft);
}