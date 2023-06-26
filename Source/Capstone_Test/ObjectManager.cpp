// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectManager.h"
#include "MyGameInstance.h"
#include "Components/StaticMeshComponent.h"

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

