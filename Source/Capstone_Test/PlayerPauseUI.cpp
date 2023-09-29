// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPauseUI.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "MyGameInstance.h"
#include "Kismet/GamePlayStatics.h"
#include "Capstone_TestCharacter.h"

void UPlayerPauseUI::NativeOnInitialized()
{
	BtRestart = Cast<UButton>(GetWidgetFromName(TEXT("BtRestart")));
	BtStage = Cast<UButton>(GetWidgetFromName(TEXT("BtStage")));
	BtExit = Cast<UButton>(GetWidgetFromName(TEXT("BtExit")));
}

void UPlayerPauseUI::NativeConstruct()
{
	Super::NativeConstruct();

	UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(GetGameInstance());
	myCharacter = Cast<ACapstone_TestCharacter>(UGameplayStatics::GetPlayerController(this, 0)->GetPawn());

	myCharacter->OnPlayerMenuUpDelegate.AddUObject(this, &UPlayerPauseUI::MenuUp);
	myCharacter->OnPlayerMenuDownDelegate.AddUObject(this, &UPlayerPauseUI::MenuDown);

	BtArray.Insert(BtRestart, 0);
	BtArray.Insert(BtStage, 1);
	BtArray.Insert(BtExit, 2);

	BtSequence = 0;
}

void UPlayerPauseUI::GameRestart()
{
	UMyGameInstance* MyGI = Cast<UMyGameInstance>(GetGameInstance());
	FString MapStage = MyGI->GetMapName(MyGI->GetCurrentStage());
	FName fnNextStage = FName(*MapStage);

	UGameplayStatics::OpenLevel(GetWorld(), fnNextStage);
}

void UPlayerPauseUI::GameExit()
{

}

void UPlayerPauseUI::GameStage()
{
	UMyGameInstance* MyGI = Cast<UMyGameInstance>(GetGameInstance());
	FString MapStage = MyGI->GetMapName(7);
	FName fnNextStage = FName(*MapStage);

	MyGI->SetCurrentStage(7);
	UGameplayStatics::OpenLevel(GetWorld(), fnNextStage);
}

void UPlayerPauseUI::MenuUp()
{
	if (BtSequence == 0)
	{
		BtArray[BtSequence]->SetFocus();
		return;
	}

	else
	{
		BtSequence = BtSequence - 1;
		BtArray[BtSequence]->SetFocus();
	}
}

void UPlayerPauseUI::MenuDown()
{
	if (BtSequence == 2)
	{
		BtArray[BtSequence]->SetFocus();
		return;
	}

	else
	{
		BtSequence = BtSequence + 1;
		BtArray[BtSequence]->SetFocus();
	}
}
