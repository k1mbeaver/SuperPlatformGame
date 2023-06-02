// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBossMonster.h"

// Sets default values
AMyBossMonster::AMyBossMonster()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyBossMonster::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyBossMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyBossMonster::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

