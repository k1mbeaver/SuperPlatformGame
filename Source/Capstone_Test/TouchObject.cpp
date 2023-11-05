// Fill out your copyright notice in the Description page of Project Settings.


#include "TouchObject.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "MyGameInstance.h"

// Sets default values
ATouchObject::ATouchObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TouchCollision = CreateDefaultSubobject<USphereComponent>(TEXT("TouchCollision"));
	TouchCollision->SetupAttachment(RootComponent);

	TouchStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TouchStaticMesh"));
	TouchStaticMesh->SetupAttachment(TouchCollision);
}

// Called when the game starts or when spawned
void ATouchObject::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATouchObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called every frame
int ATouchObject::GetTouchNumber()
{
	return nTouchNumber;
}