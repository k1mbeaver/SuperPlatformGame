// Copyright Epic Games, Inc. All Rights Reserved.

#include "Capstone_TestCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "MyGameInstance.h"
#include "MyAnimInstance.h"
#include "Animation/AnimInstance.h"
#include "PlayerHUD.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "MyBossMonster.h"
#include "MyAICharacter.h"
#include "Particles/ParticleSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "MyPortal.h"

//////////////////////////////////////////////////////////////////////////
// ACapstone_TestCharacter

ACapstone_TestCharacter::ACapstone_TestCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rate for input
	TurnRateGamepad = 50.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 250.0f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom);
	//FollowCamera->SetupAttachment(GetCapsuleComponent());
	FollowCamera->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	NiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComponent"));
	NiagaraComponent->SetupAttachment(RootComponent);
	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
}

void ACapstone_TestCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (bCameraMove)
	{
		if (CurrentState == ECharacterState::STAND)
		{
			TransCameraPos(0.05, 1.0);
			//ReturnTransCameraPos(0.05, 1);
		}

		else if (CurrentState == ECharacterState::CROUCH)
		{
			TransCameraPos(0.05, 0.5);
			// 나중에 편집하기
		}

		else if (CurrentState == ECharacterState::DOWN)
		{
			TransCameraPos(0.05, 0.3);
			// 나중에 편집하기
		}

		else if (CurrentState == ECharacterState::RUN)
		{
			TransCameraPos(0.05, 0.6);
			// 나중에 편집하기
		}

		else if (CurrentState == ECharacterState::BASH)
		{
			// 나중에 편집하기
		}

		else if (CurrentState == ECharacterState::DEATH)
		{
			// 나중에 편집하기
			TransCameraPos(0.05, 0.2);
		}
	}

	else
	{
		if (CurrentState == ECharacterState::STAND)
		{
			ReturnTransCameraPos(0.05, 1.0);
			//ReturnTransCameraPos(0.05, 1);
		}

		else if (CurrentState == ECharacterState::CROUCH)
		{
			ReturnTransCameraPos(0.05, 0.5);
			// 나중에 편집하기
		}

		else if (CurrentState == ECharacterState::DOWN)
		{
			ReturnTransCameraPos(0.05, 0.3);
			// 나중에 편집하기
		}

		else if (CurrentState == ECharacterState::RUN)
		{
			ReturnTransCameraPos(0.05, 0.6);
			// 나중에 편집하기
		}

		else if (CurrentState == ECharacterState::BASH)
		{
			// 나중에 편집하기
		}
	}
	
}

void ACapstone_TestCharacter::BeginPlay()
{
	Super::BeginPlay();

	//GetMesh()->SetSkeletalMesh(GetGameInstance()->);
	UMyGameInstance* MyGI = Cast<UMyGameInstance>(GetGameInstance());
	myAnimInstance = Cast<UMyAnimInstance>(GetMesh()->GetAnimInstance());
	myDiveMontage = MyGI->GetPlayerDiveMontage();

	myAnimInstance->DiveStart_Dive.AddUObject(this, &ACapstone_TestCharacter::StartBashAnimation);
	myAnimInstance->DiveEnd_Dive.AddUObject(this, &ACapstone_TestCharacter::StopBashAnimation);
	myAnimInstance->DiveBash_Dive.AddUObject(this, &ACapstone_TestCharacter::CurrentBash);

	CurrentCoin = MyGI->GetPlayerCoin();
	CurrentStar = MyGI->GetPlayerStar();
	CurrentGem = MyGI->GetPlayerGem();
	CurrentLife = MyGI->GetPlayerLife();

	APlayerHUD* myHUD = Cast<APlayerHUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());
	myHUD->SetGemCount(CurrentGem);
	myHUD->SetStarCount(CurrentStar);
	myHUD->SetCoinCount(CurrentCoin);
	myHUD->SetCharacterCount(CurrentLife);

	//BashParticle = MyGI->GetPlayerBashParticle();
	//CharacterDefaultHP = MyGI->GetPlayerHP();
	//CharacterHP = CharacterDefaultHP;
}

//////////////////////////////////////////////////////////////////////////
// Input

void ACapstone_TestCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction("BulletTime", IE_Pressed, this, &ACapstone_TestCharacter::BulletTime);
	PlayerInputComponent->BindAction("BulletTime", IE_Released, this, &ACapstone_TestCharacter::StopBulletTime);

	PlayerInputComponent->BindAction("TransCamera", IE_Pressed, this, &ACapstone_TestCharacter::TransCamera);
	PlayerInputComponent->BindAction("TransCamera", IE_Released, this, &ACapstone_TestCharacter::StopTransCamera);

	PlayerInputComponent->BindAxis("Move Forward / Backward", this, &ACapstone_TestCharacter::MoveForward);
	PlayerInputComponent->BindAxis("Move Right / Left", this, &ACapstone_TestCharacter::MoveRight);

	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &ACapstone_TestCharacter::Run);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &ACapstone_TestCharacter::StopRun);

	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &ACapstone_TestCharacter::Crouching);
	PlayerInputComponent->BindAction("Crouch", IE_Released, this, &ACapstone_TestCharacter::StopCrouch);

	PlayerInputComponent->BindAction("CharacterDown", IE_Pressed, this, &ACapstone_TestCharacter::CharacterDown);
	PlayerInputComponent->BindAction("CharacterDown", IE_Released, this, &ACapstone_TestCharacter::StopDown);

	PlayerInputComponent->BindAction("Bash", IE_Pressed, this, &ACapstone_TestCharacter::Bash);
	PlayerInputComponent->BindAction("Bash", IE_Released, this, &ACapstone_TestCharacter::StopBash);

	PlayerInputComponent->BindAction("CameraChange", IE_Pressed, this, &ACapstone_TestCharacter::CameraChange);
}

void ACapstone_TestCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
	Jump();
}

void ACapstone_TestCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
	StopJumping();
}

/*
void ACapstone_TestCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}

void ACapstone_TestCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}
*/
void ACapstone_TestCharacter::MoveForward(float Value)
{
	if (bCanMove == false)
	{
		return;
	}

	if (bCameraForward)
	{
		Value = Value * -1;
	}

	if ((Controller != nullptr) && (Value != 0.0f))
	{
		FVector Direction = FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::X);

		Direction.Z = 0.0f;
		Direction.Normalize();

		AddMovementInput(Direction, Value);
	}
}

void ACapstone_TestCharacter::MoveRight(float Value)
{
	if (bCanMove == false)
	{
		return;
	}

	if (bCameraForward)
	{
		Value = Value * -1;
	}

	if ( (Controller != nullptr) && (Value != 0.0f) )
	{
		FVector Direction = FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::Y);

		Direction.Z = 0.0f;
		Direction.Normalize();

		AddMovementInput(Direction, Value);
	}
}

void ACapstone_TestCharacter::BulletTime()
{
	GetWorldSettings()->SetTimeDilation(0.5f);
	//CameraBoom->TargetArmLength = 1000.0f;
}

void ACapstone_TestCharacter::StopBulletTime()
{
	GetWorldSettings()->SetTimeDilation(1.0f);
	//CameraBoom->TargetArmLength = 500.0f;
}

void ACapstone_TestCharacter::TransCamera()
{
	bCameraMove = true;
	//TransCameraPos(0.05, 0.5);
}

void ACapstone_TestCharacter::StopTransCamera()
{
	bCameraMove = false;
}

void ACapstone_TestCharacter::CameraChange()
{
	if (bCameraForward)
	{
		bCameraForward = false;
		CameraBoom->SocketOffset = FVector(0.0f, 0.0f, 200.0f);
		FQuat DesiredRotation = FRotator(-30.0f, 0.0f, 0.0f).Quaternion();
		FollowCamera->SetRelativeRotation(DesiredRotation);
	}

	else
	{
		bCameraForward = true;
		CameraBoom->SocketOffset = FVector(1000.0f, 0.0f, 200.0f);
		FQuat DesiredRotation = FRotator(-30.0f, 180.0f, 0.0f).Quaternion();
		FollowCamera->SetRelativeRotation(DesiredRotation);
	}
}

void ACapstone_TestCharacter::TransCameraPos(float t, float targetRatio) {
	//float EndArmValue = LerpFun(CameraBoom->TargetArmLength, 0, targetRatio);
	//float EndSocketValue = LerpFun(CameraBoom->SocketOffset.Z, 0, targetRatio);
	float EndArmValue = LerpFun(500.0f, 0, targetRatio);
	float EndSocketValue = LerpFun(200.0f, 0, targetRatio);
	CameraBoom->TargetArmLength = LerpFun(CameraBoom->TargetArmLength, EndArmValue, t);

	if (bCameraForward)
	{
		float EndSocketValueX = LerpFun(1000.0f, 0, targetRatio);
		CameraBoom->SocketOffset.X = LerpFun(CameraBoom->SocketOffset.X, EndSocketValueX, t);
		CameraBoom->SocketOffset.Z = LerpFun(CameraBoom->SocketOffset.Z, EndSocketValue, t);
	}

	else
	{
		CameraBoom->SocketOffset.Z = LerpFun(CameraBoom->SocketOffset.Z, EndSocketValue, t);
	}
}

void ACapstone_TestCharacter::ReturnTransCameraPos(float t, float targetRatio) {
	//float EndArmValue = LerpFun(CameraBoom->TargetArmLength, 0, targetRatio);
	//float EndSocketValue = LerpFun(CameraBoom->SocketOffset.Z, 0, targetRatio);
	float EndArmValue = LerpFun(CameraBoom->TargetArmLength, 500.0f, targetRatio);
	float EndSocketValue = LerpFun(CameraBoom->SocketOffset.Z, 200.0f, targetRatio);
	CameraBoom->TargetArmLength = LerpFun(CameraBoom->TargetArmLength, EndArmValue, t);

	if (bCameraForward)
	{
		float EndSocketValueX = LerpFun(CameraBoom->SocketOffset.X, 1000.0f, targetRatio);
		CameraBoom->SocketOffset.X = LerpFun(CameraBoom->SocketOffset.X, EndSocketValueX, t);
		CameraBoom->SocketOffset.Z = LerpFun(CameraBoom->SocketOffset.Z, EndSocketValue, t);
	}

	else
	{
		CameraBoom->SocketOffset.Z = LerpFun(CameraBoom->SocketOffset.Z, EndSocketValue, t);
	}
}

void ACapstone_TestCharacter::Run()
{
	if (bCanMove == false)
	{
		return;
	}

	CurrentState = ECharacterState::RUN;
	GetCharacterMovement()->MaxWalkSpeed = 500.0f;
	bCameraMove = true;
}

void ACapstone_TestCharacter::StopRun()
{
	if (bCanMove == false)
	{
		return;
	}

	CurrentState = ECharacterState::STAND;
	GetCharacterMovement()->MaxWalkSpeed = 250.0f;
	bCameraMove = false;
}

void ACapstone_TestCharacter::Crouching()
{
	if (bCanMove == false)
	{
		return;
	}

	CurrentState = ECharacterState::CROUCH;
	GetCharacterMovement()->MaxWalkSpeed = 150.0f;
	bCameraMove = true;
	myAnimInstance->IsCrouch = true;
}

void ACapstone_TestCharacter::StopCrouch()
{
	if (bCanMove == false)
	{
		return;
	}

	CurrentState = ECharacterState::STAND;
	GetCharacterMovement()->MaxWalkSpeed = 300.0f;
	bCameraMove = false;
	myAnimInstance->IsCrouch = false;
}

void ACapstone_TestCharacter::CharacterDown()
{
	CurrentState = ECharacterState::DOWN;
	bCameraMove = true;
}

void ACapstone_TestCharacter::StopDown()
{
	CurrentState = ECharacterState::STAND;
	bCameraMove = false;
}

void ACapstone_TestCharacter::Bash()
{
	CurrentState = ECharacterState::BASH;
	GetWorldSettings()->SetTimeDilation(0.1f);
	bCameraMove = true;
	//bCanMove = false;
	myAnimInstance->IsBash = true;
	myAnimInstance->PlayDiveMontage(myDiveMontage);

	//GameStatic->SpawnEmitterAttached(BashParticle, BashMuzzleLocation, FName("MuzzleLocation"));
	NiagaraComponent->Activate();

	float Duration = 0.1f; // Duration in seconds
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, [&]()
		{
			NiagaraComponent->Deactivate();
		}, Duration, false);

	AttackCheck();
}

void ACapstone_TestCharacter::StopBash()
{
	CurrentState = ECharacterState::STAND;
	GetWorldSettings()->SetTimeDilation(1.0f);
	bCameraMove = false;
	myAnimInstance->IsBash = false;
}

void ACapstone_TestCharacter::StartBashAnimation()
{
	//bCanMove = false;
	LaunchCharacter(FVector(0.0f, 0.0f, 1000.f), 0, 1);
}

void ACapstone_TestCharacter::CurrentBash()
{
	//
}

void ACapstone_TestCharacter::StopBashAnimation()
{
	bCanMove = true;
}

void ACapstone_TestCharacter::Death()
{
	bAlive = false;
	myAnimInstance->SetDeadAnim();
}

void ACapstone_TestCharacter::CoinGet()
{
	CurrentCoin++;

	if (CurrentCoin == 10)
	{
		CurrentLife++;
		UMyGameInstance* MyGI = Cast<UMyGameInstance>(GetGameInstance());
		APlayerHUD* myHUD = Cast<APlayerHUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());
		MyGI->SetPlayerLife(CurrentLife);
		myHUD->SetCharacterCount(MyGI->GetPlayerLife());
		CurrentCoin = 0;
	}

	UMyGameInstance* MyGI = Cast<UMyGameInstance>(GetGameInstance());
	APlayerHUD* myHUD = Cast<APlayerHUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());
	MyGI->SetPlayerCoin(CurrentCoin);
	myHUD->SetCoinCount(MyGI->GetPlayerCoin());
}

void ACapstone_TestCharacter::StarGet()
{
	CurrentStar++;
	UMyGameInstance* MyGI = Cast<UMyGameInstance>(GetGameInstance());
	APlayerHUD* myHUD = Cast<APlayerHUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());
	MyGI->SetPlayerStar(CurrentStar);
	myHUD->SetStarCount(MyGI->GetPlayerStar());

	if (CurrentStar == 1 && CurrentGem == 1)
	{
		bGameClear = true;

		UWorld* World = GetWorld();

		if (World)
		{
			TArray<AActor*> FoundActors;
			FString PortalTag = "PlayerPortal";

			UGameplayStatics::GetAllActorsWithTag(World, FName(*PortalTag), FoundActors);

			if (FoundActors.Num() > 0)
			{
				AActor* PortalActor = FoundActors[0];

				if (AMyPortal* CastedPortal = Cast<AMyPortal>(PortalActor))
				{
					PlayerPortal = CastedPortal;
					PlayerPortal->PlayerClear();
				}
			}
		}
	}
}

void ACapstone_TestCharacter::GemGet()
{
	CurrentGem++;
	UMyGameInstance* MyGI = Cast<UMyGameInstance>(GetGameInstance());
	APlayerHUD* myHUD = Cast<APlayerHUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());
	MyGI->SetPlayerGem(CurrentGem);
	myHUD->SetGemCount(MyGI->GetPlayerGem());

	if (CurrentStar == 1 && CurrentGem == 1)
	{
		bGameClear = true;

		UWorld* World = GetWorld();

		if (World)
		{
			TArray<AActor*> FoundActors;
			FString PortalTag = "PlayerPortal";

			UGameplayStatics::GetAllActorsWithTag(World, FName(*PortalTag), FoundActors);

			if (FoundActors.Num() > 0)
			{
				AActor* PortalActor = FoundActors[0];

				if (AMyPortal* CastedPortal = Cast<AMyPortal>(PortalActor))
				{
					PlayerPortal = CastedPortal;
					PlayerPortal->PlayerClear();
				}
			}
		}
	}
}

void ACapstone_TestCharacter::PlayerDead()
{
	bAlive = false;
	bCameraMove = true;
	bCanMove = false;
	CurrentState = ECharacterState::DEATH;
	myAnimInstance->SetDeadAnim();
	LaunchCharacter(FVector(100.0f, 100.0f, 500.f), 0, 1);
}

void ACapstone_TestCharacter::AttackCheck()
{
	FHitResult HitResult;
	FCollisionQueryParams Params(NAME_None, false, this);
	bool bResult = GetWorld()->SweepSingleByChannel(
		HitResult,
		GetActorLocation(),
		GetActorLocation() + (GetActorUpVector() * -1) * AttackRange,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel3, // Attack 채널 player의 경우에만 충돌 한다
		FCollisionShape::MakeSphere(AttackRadius),
		Params);
	
	/*
	#if ENABLE_DRAW_DEBUG
			FVector TraceVec = (GetActorUpVector() * -1) * AttackRange;
			FVector Center = GetActorLocation() + TraceVec * 0.5f;
			float HalfHeight = AttackRange * 0.5f + AttackRadius;
			FQuat CapsuleRot = FRotationMatrix::MakeFromZ(TraceVec).ToQuat();
			FColor DrawColor = bResult ? FColor::Green : FColor::Red;
			float DebugLifeTime = 5.0f;

			// 이거는 에디터에서만 사용하는거
			DrawDebugCapsule(GetWorld(),
				Center,
				HalfHeight,
				AttackRadius,
				CapsuleRot,
				DrawColor,
				false,
				DebugLifeTime);

			//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("PlayerPunch!")); // 플레이어가 펀치하는지 확인용

	#endif
	*/

	if (bResult)
	{
		{
			GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("Hit!"));
			//FDamageEvent DamageEvent;
			//AttackParticleStart(HitResult.ImpactPoint); // 몬스터 공격 파티클 출력하기

			AMyBossMonster* HitCharacter = Cast<AMyBossMonster>(HitResult.GetActor());

			if (!HitCharacter)
			{
				AMyAICharacter* AIHitCharacter = Cast<AMyAICharacter>(HitResult.GetActor());

				if (!AIHitCharacter)
				{
					return;
				}

				else
				{
					AIHitCharacter->Death();
					return;
				}
			}
			HitCharacter->Death();
		}
	}
}