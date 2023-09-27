// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerStartUI.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/Slider.h"
#include "Components/CanvasPanel.h"
#include "MyGameInstance.h"
#include "Kismet/GamePlayStatics.h"
#include "Capstone_TestCharacter.h"

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

void UPlayerStartUI::NativeConstruct()
{
	Super::NativeConstruct();

	UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(GetGameInstance());
	myCharacter = Cast<ACapstone_TestCharacter>(UGameplayStatics::GetPlayerController(this, 0)->GetPawn());

	myCharacter->OnPlayerMenuRightDelegate.AddUObject(this, &UPlayerStartUI::MenuRight);
	myCharacter->OnPlayerMenuLeftDelegate.AddUObject(this, &UPlayerStartUI::MenuLeft);
	myCharacter->OnPlayerMenuUpDelegate.AddUObject(this, &UPlayerStartUI::MenuUp);
	myCharacter->OnPlayerMenuDownDelegate.AddUObject(this, &UPlayerStartUI::MenuDown);
	myCharacter->OnPlayerMenuClickDelegate.AddUObject(this, &UPlayerStartUI::MenuClick);
	myCharacter->OnPlayerMenuOutDelegate.AddUObject(this, &UPlayerStartUI::MenuOut);

	BtArray.Insert(BtStart, 0);
	BtArray.Insert(BtSetting, 1);
	BtArray.Insert(BtExit, 2);

	BtSequence = 0;
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
	UKismetSystemLibrary::QuitGame(this, 0, EQuitPreference::Quit, false);
}

void UPlayerStartUI::GameSetting()
{
	VisibleSetting(true);
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

void UPlayerStartUI::MenuUp()
{
	if (BtSequence == 0)
	{
		BtArray[BtSequence]->SetFocus();
		return;
	}

	else
	{
		BtSequence--;
	}

	BtArray[BtSequence]->SetFocus();
}

void UPlayerStartUI::MenuDown()
{
	if (BtSequence == 2)
	{
		BtArray[BtSequence]->SetFocus();
		return;
	}

	else
	{
		BtSequence++;
	}

	BtArray[BtSequence]->SetFocus();
}

void UPlayerStartUI::MenuRight()
{

}

void UPlayerStartUI::MenuLeft()
{

}

void UPlayerStartUI::MenuClick()
{
	if (BtSequence == 1)
	{
		GameStart();
	}

	else if (BtSequence == 2)
	{
		GameSetting();
	}

	else if(BtSequence == 3)
	{
		GameExit();
	}
}

void UPlayerStartUI::MenuOut()
{

}