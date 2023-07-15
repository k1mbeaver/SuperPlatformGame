// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAICharacter.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MyAIAnimInstance.h"
#include "MyGameInstance.h"
#include "Animation/AnimInstance.h"
#include "MyAIController.h"

// Sets default values
AMyAICharacter::AMyAICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Configure character movement
	//GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	//GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 100.0f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	bAlive = true;
}

// Called when the game starts or when spawned
void AMyAICharacter::BeginPlay()
{
	Super::BeginPlay();
	
	MonsterAnim = Cast<UMyAIAnimInstance>(GetMesh()->GetAnimInstance());
	myGameInstance = Cast<UMyGameInstance>(GetGameInstance());
	GetMesh()->SetSkeletalMesh(myGameInstance->GetAISkeletalMesh(strMonsterType));
	GetMesh()->SetAnimInstanceClass(myGameInstance->GetAIAnimInstance(strMonsterType));
	GetCharacterMovement()->MaxWalkSpeed = myGameInstance->GetAISpeed(strMonsterType);
	AttackMontage = myGameInstance->GetAIAttackMontage(strMonsterType);

	CharacterDefaultHP = myGameInstance->GetAIHP(strMonsterType);
	CharacterHP = CharacterDefaultHP;
}

// Called every frame
void AMyAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyAICharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMyAICharacter::Attack()
{
	MonsterAnim->PlayAttackMontage(AttackMontage);
}

void AMyAICharacter::Death()
{
	bAlive = false;
	MonsterAnim->SetDeadAnim();
	AMyAIController* myAIController = Cast<AMyAIController>(GetController());
	myAIController->StopAI();
}