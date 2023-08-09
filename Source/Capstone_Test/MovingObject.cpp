// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingObject.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"
#include "MyGameInstance.h"

// Sets default values
AMovingObject::AMovingObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a camera boom (pulls in towards the player if there is a collision)
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(RootComponent);

	bUpDown = true;
	CurrentActorLocationZ = 0.0f;
}

// Called when the game starts or when spawned
void AMovingObject::BeginPlay()
{
	Super::BeginPlay();
	
	FVector NewLocation = GetActorLocation();

	CurrentActorLocationZ = NewLocation.Z;
}

// Called every frame
void AMovingObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	nMaxUpDown++;

	if (bUpDown == false)
	{
		DownObject();
	}

	else
	{
		UpObject();
	}
}

// Called when the game starts or when spawned
void AMovingObject::UpObject()
{
	if (nMaxUpDown > 100)
	{
		nMaxUpDown = 0;
		bUpDown = false;
		return;
	}

	FVector NewLocation = GetActorLocation();
	NewLocation.Z += 1.0f; // 예시로 10.0f 만큼 위로 이동하도록 설정합니다.

	// 액터를 새로운 위치로 이동시킵니다.
	SetActorLocation(NewLocation);
}

// Called when the game starts or when spawned
void AMovingObject::DownObject()
{
	if (nMaxUpDown > 100)
	{
		nMaxUpDown = 0;
		bUpDown = true;
		return;
	}

	//nMaxHeight++;
	FVector NewLocation = GetActorLocation();
	NewLocation.Z -= 1.0f; // 예시로 10.0f 만큼 위로 이동하도록 설정합니다.

	// 액터를 새로운 위치로 이동시킵니다.
	SetActorLocation(NewLocation);
}