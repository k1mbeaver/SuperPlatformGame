// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPortal.h"
#include "Particles/ParticleSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "MyGameInstance.h"

// Sets default values
AMyPortal::AMyPortal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	CapsuleComponent->SetupAttachment(RootComponent);

	PortalCloseNiagara = CreateDefaultSubobject<UNiagaraComponent>(TEXT("PortalCloseNiagara"));
	PortalCloseNiagara->SetupAttachment(CapsuleComponent);

	PortalOpenNiagara = CreateDefaultSubobject<UNiagaraComponent>(TEXT("PortalOpenNiagara"));
	PortalOpenNiagara->SetupAttachment(CapsuleComponent);

	bClear = false;
}

// Called when the game starts or when spawned
void AMyPortal::BeginPlay()
{
	Super::BeginPlay();
	
	PortalCloseNiagara->Activate();
	PortalOpenNiagara->Deactivate();
}

// Called every frame
void AMyPortal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyPortal::PlayerClear()
{
	PortalCloseNiagara->Deactivate();
	PortalOpenNiagara->Activate();
	bClear = true;
}

void AMyPortal::NextMap()
{
	UMyGameInstance* MyGI = Cast<UMyGameInstance>(GetGameInstance());
	int CurrentStage = MyGI->GetCurrentStage();
	FString NextStage = MyGI->GetMapStrNext(CurrentStage);
	FName fnNextStage = FName(*NextStage);
	UGameplayStatics::OpenLevel(GetWorld(), fnNextStage);
}