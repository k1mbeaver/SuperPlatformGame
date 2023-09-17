// Fill out your copyright notice in the Description page of Project Settings.


#include "StageScreen.h"
#include "Capstone_TestCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "MyGameInstance.h"

// Sets default values
AStageScreen::AStageScreen()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ImageSquare = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ImageSquare"));
	ImageSquare->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AStageScreen::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> FoundActors;
	FString PlayerTag = "Player";
	UWorld* World = GetWorld();
	UGameplayStatics::GetAllActorsWithTag(World, FName(*PlayerTag), FoundActors);

	AActor* PlayerActor = FoundActors[0];
	GetPlayer = PlayerActor;
}

// Called every frame
void AStageScreen::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector NewLocation = GetPlayer->GetActorLocation();
	FVector ActorNewLocation = FVector(NewLocation.X - 1000.0f, NewLocation.Y, NewLocation.Z + 550.0f);

	SetActorLocation(ActorNewLocation);
	//SetRelativeLocation(CameraNewLocation);
	//SetRelativeRotation(FRotator(180.0f, 0.0f, 180.0f));
}

void AStageScreen::SetImage(int nMap)
{
	// 여기다가 평면에 그림을 그리도록 설정하기
	UMyGameInstance* MyGI = Cast<UMyGameInstance>(GetGameInstance());

	ImageSquare->SetMaterial(0, MyGI->GetMapMaterial(nMap));
}

void AStageScreen::ImageOnOff(bool bOnOff)
{
	if (bOnOff)
	{
		ImageSquare->SetVisibility(true);
	}

	else
	{
		ImageSquare->SetVisibility(false);
	}
}