// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBossMonster.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MyGameInstance.h"
#include "MyAIAnimInstance.h"
#include "Animation/AnimInstance.h"
#include "MyBossAIController.h"

// Sets default values
AMyBossMonster::AMyBossMonster()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Configure character movement
	//GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	//GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	BashCollision = CreateDefaultSubobject<USphereComponent>(TEXT("BashCollision"));
	BashCollision->SetupAttachment(RootComponent);

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 200.0f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	bCanAttack = false;
	bAlive = true;
}

// Called when the game starts or when spawned
void AMyBossMonster::BeginPlay()
{
	Super::BeginPlay();

	InitBossMonster();

	//CharacterDefaultHP = myGameInstance->GetAIHP(strMonsterType);
	//CharacterHP = CharacterDefaultHP;
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

void AMyBossMonster::Attack()
{
	if (!bCanAttack)
	{
		bCanAttack = true;
		MonsterAnim->PlayAttackMontage(AttackMontage);
	}
}

void AMyBossMonster::StartAttackAnimation()
{
	bCanAttack = true;
}

void AMyBossMonster::StopAttackAnimation()
{
	bCanAttack = false;
}

void AMyBossMonster::Death()
{
	bAlive = false;
	MonsterAnim->SetDeadAnim();
	AMyBossAIController* myAIController = Cast<AMyBossAIController>(GetController());
	myAIController->StopAI();
}

void AMyBossMonster::Skill()
{
	GetCharacterMovement()->MaxWalkSpeed = 600.0f;

	/*
	float Duration = 10.0f; // Duration in seconds
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, [&]()
		{
			GetCharacterMovement()->MaxWalkSpeed = 500.0f;
		}, Duration, false);
	*/
}

void AMyBossMonster::SkillEnd()
{
	GetCharacterMovement()->MaxWalkSpeed = 300.0f;

	/*
	float Duration = 10.0f; // Duration in seconds
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, [&]()
		{
			GetCharacterMovement()->MaxWalkSpeed = 500.0f;
		}, Duration, false);
	*/
}

void AMyBossMonster::InitBossMonster()
{
	myGameInstance = Cast<UMyGameInstance>(GetGameInstance());
	GetMesh()->SetSkeletalMesh(myGameInstance->GetAISkeletalMesh(strMonsterType));
	GetMesh()->SetAnimInstanceClass(myGameInstance->GetAIAnimInstance(strMonsterType));
	GetCharacterMovement()->MaxWalkSpeed = myGameInstance->GetAISpeed(strMonsterType);
	MonsterAnim = Cast<UMyAIAnimInstance>(GetMesh()->GetAnimInstance());
	AttackMontage = myGameInstance->GetAIAttackMontage(strMonsterType);

	MonsterAnim->AttackStart_Attack.AddUObject(this, &AMyBossMonster::StartAttackAnimation);
	MonsterAnim->AttackEnd_Attack.AddUObject(this, &AMyBossMonster::StopAttackAnimation);
}