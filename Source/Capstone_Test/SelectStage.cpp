// Fill out your copyright notice in the Description page of Project Settings.


#include "SelectStage.h"
#include "MyGameInstance.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ASelectStage::ASelectStage()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	OnStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	OnStaticMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ASelectStage::BeginPlay()
{
	Super::BeginPlay();
	
	nStageNumber = FCString::Atoi(*strStageNumber);

	UMyGameInstance* MyGI = Cast<UMyGameInstance>(GetGameInstance());
	OnSound = MyGI->GetSound("MapChoose");
}

// Called every frame
void ASelectStage::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASelectStage::OnStage()
{
	// ĳ���Ͱ� �ش� ���� ���� �ö��� �� Ȱ��ȭ

	if (OnSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, OnSound, GetActorLocation());
	}
}

void ASelectStage::OffStage()
{
	// ĳ���Ͱ� �ش� ���Ϳ��� �������� �� ��Ȱ��ȭ
}