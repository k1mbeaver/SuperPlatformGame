// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPauseUI.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "MyGameInstance.h"
#include "Kismet/GamePlayStatics.h"

void UPlayerPauseUI::NativeOnInitialized()
{
	BtRestart = Cast<UButton>(GetWidgetFromName(TEXT("BtRestart")));
	BtStage = Cast<UButton>(GetWidgetFromName(TEXT("BtStage")));
	BtExit = Cast<UButton>(GetWidgetFromName(TEXT("BtExit")));
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