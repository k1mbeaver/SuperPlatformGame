// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerStartUI.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "MyGameInstance.h"
#include "Kismet/GamePlayStatics.h"

void UPlayerStartUI::NativeOnInitialized()
{
	BtStart = Cast<UButton>(GetWidgetFromName(TEXT("BtStart")));
	BtExit = Cast<UButton>(GetWidgetFromName(TEXT("BtExit")));
}

void UPlayerStartUI::GameStart()
{
	UMyGameInstance* MyGI = Cast<UMyGameInstance>(GetGameInstance());
	FString MapStage = MyGI->GetMapName(7);
	FName fnNextStage = FName(*MapStage);

	UGameplayStatics::OpenLevel(GetWorld(), fnNextStage);
}

void UPlayerStartUI::GameExit()
{

}