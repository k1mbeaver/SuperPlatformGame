// Fill out your copyright notice in the Description page of Project Settings.


#include "MyHitObject.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "MyGameInstance.h"

// Sets default values
AMyHitObject::AMyHitObject()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a camera boom (pulls in towards the player if there is a collision)
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(RootComponent);

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
void AMyHitObject::BeginPlay()
{
	Super::BeginPlay();

	myGameInstance = Cast<UMyGameInstance>(GetGameInstance());

	InitObject(myGameInstance->GetObjectName(strObjectType));
	//GetMesh()->SetSkeletalMesh(myGameInstance->GetAISkeletalMesh(strObjectType));
	//GetCharacterMovement()->MaxWalkSpeed = myGameInstance->GetAISpeed(strObjectType);

	//CharacterDefaultHP = myGameInstance->GetAIHP(strMonsterType);
	//CharacterHP = CharacterDefaultHP;
}

// Called every frame
void AMyHitObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyHitObject::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMyHitObject::InitObject(FString ObjectName)
{
	ObjectSpeed = myGameInstance->GetObjectSpeed(ObjectName);
	GetCharacterMovement()->MaxWalkSpeed = ObjectSpeed;

	StaticMesh->SetStaticMesh(myGameInstance->GetObjStaticMesh(ObjectName));

	// Damage까지 추가한 후에 적용시켜서 사용해보자(충돌처리)
}
