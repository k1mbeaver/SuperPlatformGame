// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerStageUI.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "MyGameInstance.h"


void UPlayerStageUI::NativeOnInitialized()
{
	TextDefault = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextDefault")));
	TextPressBar = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextPressBar")));
	TextStage = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextStage")));
}

void UPlayerStageUI::SetStage(int nCount)
{
	FString nToString = FString::FromInt(nCount);
	FText strToft = FText::FromString(nToString);
	TextStage->SetText(strToft);
}