// Fill out your copyright notice in the Description page of Project Settings.


#include "MapBGM.h"
#include "Components/AudioComponent.h"
#include "MyGameInstance.h"

AMapBGM::AMapBGM()
{

}

void AMapBGM::BeginPlay()
{
	Super::BeginPlay();

	UMyGameInstance* MyGI = Cast<UMyGameInstance>(GetGameInstance());

	GetAudioComponent()->SetSound(MyGI->GetSound(strMap));
	GetAudioComponent()->SetVolumeMultiplier(MyGI->GetSoundVolume("BGSound"));
	GetAudioComponent()->Play();
}