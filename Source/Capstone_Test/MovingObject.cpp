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

	bUpDown = false;
}

// Called when the game starts or when spawned
void AMovingObject::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMovingObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bUpDown)
	{
		UpObject();
	}

	else
	{
		DownObject();
	}
}

// Called when the game starts or when spawned
void AMovingObject::UpObject()
{
	bUpDown = true;
}

// Called when the game starts or when spawned
void AMovingObject::DownObject()
{
	//nMaxHeight++;
	FVector NewLocation = GetActorLocation();
	NewLocation.Z += 1.0f; // ���÷� 10.0f ��ŭ ���� �̵��ϵ��� �����մϴ�.

	// ���͸� ���ο� ��ġ�� �̵���ŵ�ϴ�.
	SetActorLocation(NewLocation);
}