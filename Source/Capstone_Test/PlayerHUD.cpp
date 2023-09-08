// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHUD.h"
#include "PlayerMainUI.h"


APlayerHUD::APlayerHUD()
{
	static ConstructorHelpers::FClassFinder<UPlayerMainUI> WB_Main(TEXT("WidgetBlueprint'/Game/UI/UW_PlayerMain'"));
	if (WB_Main.Succeeded())
	{
		MainUIClass = WB_Main.Class;
	}
}

void APlayerHUD::BeginPlay()
{
	Super::BeginPlay();

	CheckUIObject(); // 시작하면 UI를 생성한다.
}

bool APlayerHUD::CheckUIObject()
{
	if (MainUIObject == nullptr) // UI가 없다면 생성.
	{
		return CreateUIObject();
	}
	return true; // 있다면 True.
}

bool APlayerHUD::CreateUIObject()
{
	if (MainUIClass)
	{
		MainUIObject = CreateWidget<UPlayerMainUI>(GetOwningPlayerController(), MainUIClass);
		if (MainUIObject)
		{
			MainUIObject->AddToViewport();
			return true; // 만들었다면 true.
		}
	}
	return false; // 못 만들었다면 false.
}

void APlayerHUD::SetCharacterCount(int nCount)
{
	MainUIObject->SetCharacterCount(nCount);
}

void APlayerHUD::SetCoinCount(int nCount)
{
	MainUIObject->SetCoinCount(nCount);
}

void APlayerHUD::SetGemCount(int nCount)
{
	MainUIObject->SetGemCount(nCount);
}

void APlayerHUD::SetStarCount(int nCount)
{
	MainUIObject->SetStarCount(nCount);
}

void APlayerHUD::SetPlayMode(bool bActive)
{
	MainUIObject->SetPlayMode(bActive);
}

void APlayerHUD::SetStageMode(bool bActive)
{
	MainUIObject->SetStageMode(bActive);
}

void APlayerHUD::SetStage(int nStage)
{
	MainUIObject->SetStage(nStage);
}

void APlayerHUD::GameRestart()
{
	MainUIObject->GameRestart();
}

void APlayerHUD::GameExit()
{
	MainUIObject->GameExit();
}

void APlayerHUD::GameStage()
{
	MainUIObject->GameStage();
}

void APlayerHUD::SettingPauseVisible(bool Istrue)
{
	MainUIObject->SettingPauseVisible(Istrue);
}

void APlayerHUD::VisibleLoading(bool Istrue)
{
	MainUIObject->VisibleLoading(Istrue);
}

void APlayerHUD::SetLoadingImage(int nMap)
{
	MainUIObject->SetLoadingImage(nMap);
}

void APlayerHUD::SetLoadingText(int nMap)
{
	MainUIObject->SetLoadingText(nMap);
}

void APlayerHUD::InitProgressBar()
{
	MainUIObject->InitProgressBar();
}