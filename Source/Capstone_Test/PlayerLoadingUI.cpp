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
	// ���� �ν��Ͻ��� �ؽ�Ʈ�� ������ �Լ��� ��������
	UMyGameInstance* MyGI = Cast<UMyGameInstance>(GetGameInstance());
	FString strText = MyGI->GetMapText(nMap);
	FText strToft = FText::FromString(strText);
	LoadingText->SetText(strToft);
}

void UPlayerLoadingUI::InitProgressBar()
{
	// ���α׷����� �ʱ�ȭ ��Ű��
	LoadingBar->SetPercent(0.0f);
	//UW_PlayerPause->GameStage();
}

bool UPlayerLoadingUI::EngageProgressBar(float LoadingPercent)
{
	LoadingBar->SetPercent(LoadingPercent);

	if (LoadingPercent < 1)
	{
		//InitProgressBar();
		//SetVisibility(ESlateVisibility::Hidden);
		//bOnLoading = false;
		return true;
	}

	else
	{
		InitProgressBar();
		return false;
	}
	//UW_PlayerPause->GameStage();
}