// Fill out your copyright notice in the Description page of Project Settings.


#include "BashObject.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInterface.h"
#include "MyGameInstance.h"

// Sets default values
ABashObject::ABashObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BashCollision = CreateDefaultSubobject<USphereComponent>(TEXT("BashCollision"));
	BashCollision->SetupAttachment(RootComponent);

	BashSphere = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BashSphere"));
	BashSphere->SetupAttachment(BashCollision);
}

// Called when the game starts or when spawned
void ABashObject::BeginPlay()
{
	Super::BeginPlay();
	UMyGameInstance* MyGI = Cast<UMyGameInstance>(GetGameInstance());

	DeActivatedMaterial = MyGI->GetMaterial("BashDeActivated");
	ActivatedMaterial = MyGI->GetMaterial("BashActivated");
}

// Called every frame
void ABashObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	nCount++;

	if (nCount == 1000)
	{
		if (bLight)
		{
			OnDeActivated();
			bLight = false;
			nCount = 0;
		}

		else
		{
			OnActivated();
			bLight = true;
			nCount = 0;
		}
	}
}

void ABashObject::OnActivated()
{	
	BashSphere->SetMaterial(0, ActivatedMaterial);
}

void ABashObject::OnDeActivated()
{
	BashSphere->SetMaterial(0, DeActivatedMaterial);
}
