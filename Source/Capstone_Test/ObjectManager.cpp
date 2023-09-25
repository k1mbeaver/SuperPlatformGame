// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectManager.h"
#include "MyGameInstance.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AObjectManager::AObjectManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AObjectManager::BeginPlay()
{
	Super::BeginPlay();
	
	// 게임 인스턴스에서 값을 가져와서 ObjectSound에 사용할 데이터를 적용할 수 있게 구현하기
	UMyGameInstance* MyGI = Cast<UMyGameInstance>(GetGameInstance());
	FString GetType = strObjectType;
	ObjectSound = MyGI->GetSound(strObjectType);
	SoundVolume = MyGI->GetSoundVolume("EffectSound");
}

// Called every frame
void AObjectManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AObjectManager::InitObj(UStaticMeshComponent* myStaticMesh)
{
	UMyGameInstance* MyGI = Cast<UMyGameInstance>(GetGameInstance());

	myStaticMesh->SetStaticMesh(MyGI->GetObjStaticMesh(strObjectType));
}

void AObjectManager::PlaySound()
{
	if (ObjectSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, ObjectSound, GetActorLocation(), SoundVolume);
	}
}
