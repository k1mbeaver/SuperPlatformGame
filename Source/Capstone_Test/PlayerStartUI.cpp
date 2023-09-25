// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerStartUI.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/Slider.h"
#include "Components/CanvasPanel.h"
#include "MyGameInstance.h"
#include "Kismet/GamePlayStatics.h"

void UPlayerStartUI::NativeOnInitialized()
{
	BtStart = Cast<UButton>(GetWidgetFromName(TEXT("BtStart")));
	BtExit = Cast<UButton>(GetWidgetFromName(TEXT("BtExit")));
	BtSetting = Cast<UButton>(GetWidgetFromName(TEXT("BtSetting")));
	BtSettingExit = Cast<UButton>(GetWidgetFromName(TEXT("BtSettingExit")));
	BGSlider = Cast<USlider>(GetWidgetFromName(TEXT("BGSlider")));
	EffectSlider = Cast<USlider>(GetWidgetFromName(TEXT("EffectSlider")));
	CharacterSlider = Cast<USlider>(GetWidgetFromName(TEXT("CharacterSlider")));
	SettingCanvas = Cast<UCanvasPanel>(GetWidgetFromName(TEXT("SettingCanvas")));
}

void UPlayerStartUI::GameStart()
{
	UMyGameInstance* MyGI = Cast<UMyGameInstance>(GetGameInstance());
	FString MapStage = MyGI->GetMapName(7);
	FName fnNextStage = FName(*MapStage);

	MyGI->SetCurrentStage(7);
	UGameplayStatics::OpenLevel(GetWorld(), fnNextStage);
}

void UPlayerStartUI::GameExit()
{

}

void UPlayerStartUI::GameSetting()
{
	
}

void UPlayerStartUI::VisibleSetting(bool bVisible)
{
	if (bVisible)
	{
		SettingCanvas->SetVisibility(ESlateVisibility::Visible);
		UMyGameInstance* MyGI = Cast<UMyGameInstance>(GetGameInstance());

		EffectSlider->SetValue(MyGI->GetSoundVolume("EffectSound"));
		CharacterSlider->SetValue(MyGI->GetSoundVolume("CharacterSound"));
		BGSlider->SetValue(MyGI->GetSoundVolume("BGSound"));
	}

	else
	{
		SettingCanvas->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UPlayerStartUI::SetBGVolume(float myVolume)
{
	UMyGameInstance* MyGI = Cast<UMyGameInstance>(GetGameInstance());
	MyGI->SetSoundVolume("BGSound", myVolume);
}

void UPlayerStartUI::SetEffectVolume(float myVolume)
{
	UMyGameInstance* MyGI = Cast<UMyGameInstance>(GetGameInstance());
	MyGI->SetSoundVolume("EffectSound", myVolume);
}

void UPlayerStartUI::SetCharacterVolume(float myVolume)
{
	UMyGameInstance* MyGI = Cast<UMyGameInstance>(GetGameInstance());
	MyGI->SetSoundVolume("CharacterSound", myVolume);
}