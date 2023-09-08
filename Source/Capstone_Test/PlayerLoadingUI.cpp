// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerLoadingUI.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "Components/Image.h"
#include "MyGameInstance.h"
#include "Kismet/GamePlayStatics.h"

void UPlayerLoadingUI::NativeOnInitialized()
{
	LoadingBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("LoadingBar")));
	LoadingImage = Cast<UImage>(GetWidgetFromName(TEXT("LoadingImage")));
	LoadingText = Cast<UTextBlock>(GetWidgetFromName(TEXT("LoadingText")));
}

void UPlayerLoadingUI::SetLoadingImage(int nMap)
{
	UMyGameInstance* MyGI = Cast<UMyGameInstance>(GetGameInstance());
	LoadingImage->SetBrushFromTexture(MyGI->GetMapImage(nMap));
	bOnLoading = true;
	//UW_PlayerPause->GameStage();
}

void UPlayerLoadingUI::SetLoadingText(int nMap)
{
	// 게임 인스턴스에 텍스트를 얻어오는 함수도 가져오자
	//UW_PlayerPause->GameStage();
}

void UPlayerLoadingUI::InitProgressBar()
{
	// 프로그래스바 초기화 시키기
	LoadingBar->SetPercent(0.0f);
	CurrentPercent = 0.0f;
	//UW_PlayerPause->GameStage();
}

void UPlayerLoadingUI::EngageProgressBar()
{
	// 프로그래스바 초기화 시키기
	CurrentPercent++;
	LoadingBar->SetPercent(CurrentPercent);

	if (CurrentPercent == 100)
	{
		InitProgressBar();
		//SetVisibility(ESlateVisibility::Hidden);
		bOnLoading = false;
	}
	//UW_PlayerPause->GameStage();
}