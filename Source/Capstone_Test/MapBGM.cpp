// Fill out your copyright notice in the Description page of Project Settings.


#include "MapBGM.h"
#include "Components/AudioComponent.h"
#include "MyGameInstance.h"

AMapBGM::AMapBGM()
{

}

void AMapBGM::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMapBGM::BeginPlay()
{
	Super::BeginPlay();

	UMyGameInstance* MyGI = Cast<UMyGameInstance>(GetGameInstance());

	GetAudioComponent()->SetSound(MyGI->GetSound(strMap));
	GetAudioComponent()->Play();
}