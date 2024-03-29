// Copyright Epic Games, Inc. All Rights Reserved.

#include "Capstone_TestCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
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
#include "PortalCamera.h"
#include "Components/ArrowComponent.h"
#include "Sound/SoundWave.h"
#include "Sound/SoundCue.h"
#include "Components/AudioComponent.h"
#include "MyPlayerController.h"

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
	FollowCamera->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	PlayerDirection = CreateDefaultSubobject<UArrowComponent>(TEXT("PlayerDirection"));
	PlayerDirection->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	PlayerDirection->SetVisibility(false);
	PlayerDirection->Deactivate();

	SideCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("SideCamera"));
	SideCamera->Deactivate();

	NiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComponent"));
	NiagaraComponent->SetupAttachment(RootComponent);

	BashCollision = CreateDefaultSubobject<USphereComponent>(TEXT("BashCollision"));
	BashCollision->SetupAttachment(RootComponent);

	WalkSound = CreateDefaultSubobject<UAudioComponent>(TEXT("WalkSound"));
	WalkSound->SetupAttachment(RootComponent);

	// 나중에 수정
	CurrentState = ECharacterState::STAGE;
	//bStageMode = true;

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
}

void ACapstone_TestCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (bSideMode == true)
	{
		FVector NewLocation = GetActorLocation();
		FVector CameraNewLocation = FVector(NewLocation.X + 800.0f, NewLocation.Y, NewLocation.Z);
		SideCamera->SetRelativeLocation(CameraNewLocation);
		SideCamera->SetRelativeRotation(FRotator(180.0f, 0.0f, 180.0f));
	}

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
	
	if (bBash)
	{
		PlayerBashDirection = PlayerDirection->GetForwardVector();
	}
}

void ACapstone_TestCharacter::BeginPlay()
{
	Super::BeginPlay();

	UMyGameInstance* MyGI = Cast<UMyGameInstance>(GetGameInstance());
	APlayerHUD* myHUD = Cast<APlayerHUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());

	if (MyGI->GetCurrentStage() == 8)
	{
		UWorld* World = GetWorld();

		if (World)
		{
			TArray<AActor*> CameraFoundActors;

			FString CameraTag = "Start";

			UGameplayStatics::GetAllActorsWithTag(World, FName(*CameraTag), CameraFoundActors);

			if (CameraFoundActors.Num() > 0)
			{
				AActor* CameraActor = CameraFoundActors[0];

				AMyPlayerController* PlayerController = Cast<AMyPlayerController>(GetWorld()->GetFirstPlayerController());
				PlayerController->SetViewTargetWithBlend(CameraActor, 0.1f);

				bUIControl = true;
			}
		}

		myHUD->SetPlayMode(false);
		myHUD->SetStageMode(false);
		myHUD->VisibleLoading(false);
		myHUD->SetLoading(false);
		myHUD->VisibleStart(true);

		return;
	}

	myHUD->SetLoading(true);
	myHUD->VisibleLoading(true);
	myHUD->SetLoadingImage(MyGI->GetCurrentStage());
	myHUD->SetLoadingText(MyGI->GetCurrentStage());

	myAnimInstance = Cast<UMyAnimInstance>(GetMesh()->GetAnimInstance());
	myDiveMontage = MyGI->GetPlayerDiveMontage();

	myAnimInstance->DiveStart_Dive.AddUObject(this, &ACapstone_TestCharacter::StartBashAnimation);
	myAnimInstance->DiveEnd_Dive.AddUObject(this, &ACapstone_TestCharacter::StopBashAnimation);
	myAnimInstance->DiveBash_Dive.AddUObject(this, &ACapstone_TestCharacter::CurrentBash);

	CurrentCoin = MyGI->GetPlayerCoin();
	CurrentStar = MyGI->GetPlayerStar();
	CurrentGem = MyGI->GetPlayerGem();
	CurrentLife = MyGI->GetPlayerLife();

	myHUD->SetCharacterCount(CurrentLife);
	myHUD->SetStarCount(CurrentStar);
	myHUD->SetGemCount(CurrentGem);
	myHUD->SetCoinCount(CurrentCoin);

	CharacterSoundVolume = MyGI->GetSoundVolume("CharacterSound");
	PlayerBashSound = MyGI->GetSound("BashStart");
	PlayerJumpSound = MyGI->GetPlayerJumpSound();
	PlayerWalkSound = MyGI->GetSound("Walking");
	LifeUpSound = MyGI->GetSound("HeartUp");
	JumpEndSound = MyGI->GetSound("JumpEnd");
	BashEndSound = MyGI->GetSound("BashEnd");
	DamagedSound = MyGI->GetSound("PlayerDamaged");
	MapSound = MyGI->GetSound("MapClear");
	PlayerRunSound = MyGI->GetSound("Walking");
	PlayerRunSound->Pitch = 3.0f;

	WalkSound->SetSound(PlayerWalkSound);
	WalkSound->SetVolumeMultiplier(CharacterSoundVolume);

	bUIControl = false;
	
	FInputModeGameOnly GameMode;
	UGameplayStatics::GetPlayerController(this, 0)->SetInputMode(GameMode);

	if (bSideMode == true)
	{
		FollowCamera->Deactivate();
		SideCamera->Activate();
	}

	if (bStageMode)
	{
		myHUD->SetPlayMode(false);
		myHUD->SetStageMode(false);
	}

	else
	{
		myHUD->SetPlayMode(true);
		myHUD->SetStageMode(false);
	}
}

//////////////////////////////////////////////////////////////////////////
// Input

void ACapstone_TestCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);

	UMyGameInstance* MyGI = Cast<UMyGameInstance>(GetGameInstance());

	if (MyGI->GetMapIsSide(MyGI->GetCurrentStage()) == 0)
	{
		bSideMode = false;
	}

	else
	{
		bSideMode = true;
	}


	if (MyGI->GetCurrentStage() == 7)
	{
		bStageMode = true;
	}

	else
	{
		bStageMode = false;
	}

	if (MyGI->GetCurrentStage() == 8)
	{
		bUIControl = true;
	}

	else
	{
		bUIControl = false;
	}

	if (bSideMode)
	{
		PlayerInputComponent->BindAxis("Side MoveForward / Backward", this, &ACapstone_TestCharacter::SideMoveForward);
	}

	else
	{
		PlayerInputComponent->BindAxis("Move Forward / Backward", this, &ACapstone_TestCharacter::MoveForward);
		PlayerInputComponent->BindAxis("Move Right / Left", this, &ACapstone_TestCharacter::MoveRight);

		PlayerInputComponent->BindAction("CameraChange", IE_Pressed, this, &ACapstone_TestCharacter::CameraChange);
	}

	if (bStageMode)
	{
		PlayerInputComponent->BindAction("StageSelect", IE_Pressed, this, &ACapstone_TestCharacter::StageSelect);
	}

	else
	{
		PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACapstone_TestCharacter::Jump);
		PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACapstone_TestCharacter::StopJumping);

		PlayerInputComponent->BindAction("BulletTime", IE_Pressed, this, &ACapstone_TestCharacter::BulletTime);
		PlayerInputComponent->BindAction("BulletTime", IE_Released, this, &ACapstone_TestCharacter::StopBulletTime);
	}

	if (bUIControl)
	{
		PlayerInputComponent->BindAction("MenuOut", IE_Pressed, this, &ACapstone_TestCharacter::MenuOut);
	}

	else
	{
		PlayerInputComponent->BindAction("Run", IE_Pressed, this, &ACapstone_TestCharacter::Run);
		PlayerInputComponent->BindAction("Run", IE_Released, this, &ACapstone_TestCharacter::StopRun);
	}

	PlayerInputComponent->BindAxis("BashDirectionForward", this, &ACapstone_TestCharacter::BashDirectionForward);
	PlayerInputComponent->BindAxis("BashDirectionRight", this, &ACapstone_TestCharacter::BashDirectionRight);

	PlayerInputComponent->BindAction("TransCamera", IE_Pressed, this, &ACapstone_TestCharacter::TransCamera);
	PlayerInputComponent->BindAction("TransCamera", IE_Released, this, &ACapstone_TestCharacter::StopTransCamera);

	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &ACapstone_TestCharacter::Crouching);
	PlayerInputComponent->BindAction("Crouch", IE_Released, this, &ACapstone_TestCharacter::StopCrouch);

	PlayerInputComponent->BindAction("CharacterDown", IE_Pressed, this, &ACapstone_TestCharacter::CharacterDown);
	PlayerInputComponent->BindAction("CharacterDown", IE_Released, this, &ACapstone_TestCharacter::StopDown);

	PlayerInputComponent->BindAction("Bash", IE_Pressed, this, &ACapstone_TestCharacter::Bash);
	PlayerInputComponent->BindAction("Bash", IE_Released, this, &ACapstone_TestCharacter::StopBash);

	PlayerInputComponent->BindAction("Pause", IE_Pressed, this, &ACapstone_TestCharacter::VisiblePause);

	PlayerInputComponent->BindAction("MenuUp", IE_Pressed, this, &ACapstone_TestCharacter::MenuUp);
	PlayerInputComponent->BindAction("MenuDown", IE_Pressed, this, &ACapstone_TestCharacter::MenuDown);
	PlayerInputComponent->BindAction("MenuRight", IE_Pressed, this, &ACapstone_TestCharacter::MenuRight);
	PlayerInputComponent->BindAction("MenuLeft", IE_Pressed, this, &ACapstone_TestCharacter::MenuLeft);
	PlayerInputComponent->BindAction("MenuClick", IE_Pressed, this, &ACapstone_TestCharacter::MenuClick);
	PlayerInputComponent->BindAction("MenuOut", IE_Pressed, this, &ACapstone_TestCharacter::MenuOut);
}

void ACapstone_TestCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
	Jump();
}

void ACapstone_TestCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
	StopJumping();
}

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

		if (WalkSound->IsPlaying())
		{
			return;
		}

		else
		{
			WalkSound->Play();
		}
	}
}

void ACapstone_TestCharacter::StageUpDown(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		FVector Direction = FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::X);

		Direction.Z = 0.0f;
		Direction.Normalize();

		AddMovementInput(Direction, Value);

		if (WalkSound->IsPlaying())
		{
			return;
		}

		else
		{
			WalkSound->Play();
		}
	}
}

void ACapstone_TestCharacter::StageLeftRight(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		FVector Direction = FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::X);

		Direction.Z = 0.0f;
		Direction.Normalize();

		AddMovementInput(Direction, Value);

		if (WalkSound->IsPlaying())
		{
			return;
		}

		else
		{
			WalkSound->Play();
		}
	}
}

void ACapstone_TestCharacter::StageSelect()
{
	UMyGameInstance* MyGI = Cast<UMyGameInstance>(GetGameInstance());
	if (CurrentSelectStage > MyGI->GetClearStage())
	{
		return;
	}

	if (bCurrentStageOn)
	{
		FString MapStage = MyGI->GetMapName(CurrentSelectStage);
		FName fnNextStage = FName(*MapStage);

		MyGI->SetCurrentStage(CurrentSelectStage);
		UGameplayStatics::OpenLevel(GetWorld(), fnNextStage);
	}
}

void ACapstone_TestCharacter::PlayerOnStage(int nStage)
{
	UMyGameInstance* MyGI = Cast<UMyGameInstance>(GetGameInstance());

	CurrentSelectStage = nStage;
	if (CurrentSelectStage > MyGI->GetClearStage())
	{
		return;
	}

	APlayerHUD* myHUD = Cast<APlayerHUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());
	myHUD->SetStageMode(true);
	myHUD->SetStage(nStage);
	bCurrentStageOn = true;
}

void ACapstone_TestCharacter::PlayerOffStage()
{
	APlayerHUD* myHUD = Cast<APlayerHUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());
	myHUD->SetStageMode(false);
	bCurrentStageOn = false;
}

void ACapstone_TestCharacter::SideMoveForward(float Value)
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

		if (WalkSound->IsPlaying())
		{
			return;
		}

		else
		{
			WalkSound->Play();
		}
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

		if (WalkSound->IsPlaying())
		{
			return;
		}

		else
		{
			WalkSound->Play();
		}
	}
}

void ACapstone_TestCharacter::Jump()
{
	Super::Jump();

	if (PlayerJumpSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, PlayerJumpSound, GetActorLocation(), CharacterSoundVolume);
	}
}

void ACapstone_TestCharacter::StopJumping()
{
	Super::StopJumping();

}


void ACapstone_TestCharacter::BulletTime()
{
	GetWorldSettings()->SetTimeDilation(0.5f);
}

void ACapstone_TestCharacter::StopBulletTime()
{
	GetWorldSettings()->SetTimeDilation(1.0f);
}

void ACapstone_TestCharacter::TransCamera()
{
	bCameraMove = true;
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

	WalkSound->SetSound(PlayerRunSound);
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

	WalkSound->SetSound(PlayerWalkSound);
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
	if (bCanBash)
	{
		CurrentState = ECharacterState::BASH;

		if (PlayerBashSound != nullptr)
		{
			UGameplayStatics::PlaySoundAtLocation(this, PlayerBashSound, GetActorLocation(), CharacterSoundVolume);
		}

		GetWorldSettings()->SetTimeDilation(0.0f);
		bCameraMove = true;
		bBash = true;
		myAnimInstance->IsBash = true;
		myAnimInstance->PlayDiveMontage(myDiveMontage);

		PlayerDirection->Activate();
		PlayerDirection->SetVisibility(true);

		NiagaraComponent->Activate();

		float Duration = 0.1f; // Duration in seconds
		FTimerHandle TimerHandle;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, [&]()
			{
				NiagaraComponent->Deactivate();
			}, Duration, false);

		AttackCheck();
	}
}

void ACapstone_TestCharacter::VisibleBash()
{
	bCanBash = true;
}

void ACapstone_TestCharacter::HiddenBash()
{
	bCanBash = false;
}

void ACapstone_TestCharacter::StopBash()
{
	if (bCanBash)
	{
		CurrentState = ECharacterState::STAND;
		GetWorldSettings()->SetTimeDilation(1.0f);
		bCameraMove = false;
		myAnimInstance->IsBash = false;


		PlayerDirection->Deactivate();
		PlayerDirection->SetVisibility(false);
	}
}

void ACapstone_TestCharacter::LaunchBash()
{
	PlayerBashDirection = PlayerDirection->GetForwardVector();
	PlayerBashDirection.Normalize();
	PlayerBashDirection = PlayerBashDirection * BashPower;

	if (BashEndSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, BashEndSound, GetActorLocation(), CharacterSoundVolume);
	}

	LaunchCharacter(PlayerBashDirection, 1, 1);
}

void ACapstone_TestCharacter::StartBashAnimation()
{
	
}

void ACapstone_TestCharacter::CurrentBash()
{
	
}

void ACapstone_TestCharacter::StopBashAnimation()
{
	bCanMove = true;
	bBash = false;
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

		if (LifeUpSound != nullptr)
		{
			UGameplayStatics::PlaySoundAtLocation(this, LifeUpSound, GetActorLocation(), CharacterSoundVolume);
		}

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
			TArray<AActor*> PortalFoundActors;
			TArray<AActor*> CameraFoundActors;

			FString PortalTag = "PlayerPortal";
			FString CameraTag = "PlayerPortalCamera";

			UGameplayStatics::GetAllActorsWithTag(World, FName(*PortalTag), PortalFoundActors);
			UGameplayStatics::GetAllActorsWithTag(World, FName(*CameraTag), CameraFoundActors);

			if (PortalFoundActors.Num() > 0)
			{
				AActor* PortalActor = PortalFoundActors[0];

				if (AMyPortal* CastedPortal = Cast<AMyPortal>(PortalActor))
				{
					PlayerPortal = CastedPortal;
					PlayerPortal->PlayerClear();
				}
			}

			if (CameraFoundActors.Num() > 0)
			{
				AActor* CameraActor = CameraFoundActors[0];

				if (APortalCamera* CastedCamera = Cast<APortalCamera>(CameraActor))
				{
					CastedCamera->PlayerGameClear();
				}
			}

			if (MapSound != nullptr)
			{
				UGameplayStatics::PlaySoundAtLocation(this, MapSound, GetActorLocation(), CharacterSoundVolume);
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
			TArray<AActor*> PortalFoundActors;
			TArray<AActor*> CameraFoundActors;

			FString PortalTag = "PlayerPortal";
			FString CameraTag = "PlayerPortalCamera";

			UGameplayStatics::GetAllActorsWithTag(World, FName(*PortalTag), PortalFoundActors);
			UGameplayStatics::GetAllActorsWithTag(World, FName(*CameraTag), CameraFoundActors);

			if (PortalFoundActors.Num() > 0)
			{
				AActor* PortalActor = PortalFoundActors[0];

				if (AMyPortal* CastedPortal = Cast<AMyPortal>(PortalActor))
				{
					PlayerPortal = CastedPortal;
					PlayerPortal->PlayerClear();
				}
			}

			if (CameraFoundActors.Num() > 0)
			{
				AActor* CameraActor = CameraFoundActors[0];

				if (APortalCamera* CastedCamera = Cast<APortalCamera>(CameraActor))
				{
					CastedCamera->PlayerGameClear();
				}
			}

			if (MapSound != nullptr)
			{
				UGameplayStatics::PlaySoundAtLocation(this, MapSound, GetActorLocation(), CharacterSoundVolume);
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

	TArray<ACapstone_TestCharacter*> ActorsToPause;
	// 나중에 여기 수정하기 죽었을 때 플레이어를 제외한 모든 사물이 멈추도록
	// 
	APlayerHUD* myHUD = Cast<APlayerHUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());
	UMyGameInstance* MyGI = Cast<UMyGameInstance>(GetGameInstance());

	CurrentLife--;
	CurrentGem = 0;
	CurrentStar = 0;

	MyGI->SetPlayerLife(CurrentLife);
	MyGI->SetPlayerStar(CurrentStar);
	MyGI->SetPlayerGem(CurrentGem);
	myHUD->SetCharacterCount(CurrentLife);

	bPause = true;
	bUIControl = true;
	myHUD->SettingPauseVisible(true);
	myHUD->GameDead(true);

	for (ACapstone_TestCharacter* Actor : ActorsToPause)
	{
		if (Actor != this) // Skip the player character
		{
			Actor->SetActorTickEnabled(false);
		}
	}
}

void ACapstone_TestCharacter::VisiblePause()
{
	if (!bPause)
	{
		APlayerHUD* myHUD = Cast<APlayerHUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());

		myHUD->SettingPauseVisible(true);
		bPause = true;
		bUIControl = true;
	}

	else
	{
		APlayerHUD* myHUD = Cast<APlayerHUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());

		myHUD->SettingPauseVisible(false);
		bPause = false;
		bUIControl = false;
	}
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

	if (bResult)
	{
		{
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

void ACapstone_TestCharacter::BashDirectionForward(float Value)
{
	if (!bBash)
	{
		return;
	}

	if (!bSideMode)
	{
		if ((Controller != nullptr) && (Value != 0.0f))
		{
			FRotator PlayerRotator = PlayerDirection->GetComponentRotation();
			
			PlayerRotator.Pitch = PlayerRotator.Pitch + Value;

			FRotator CurrentRotator = PlayerRotator;
			PlayerDirection->SetWorldRotation(CurrentRotator);
		}
	}
}

void ACapstone_TestCharacter::BashDirectionRight(float Value)
{
	if (!bBash)
	{
		return;
	}

	if (bSideMode)
	{
		if ((Controller != nullptr) && (Value != 0.0f))
		{
			FRotator PlayerRotator = PlayerDirection->GetComponentRotation();

			PlayerRotator.Yaw = -90.0f;
			PlayerRotator.Pitch = PlayerRotator.Pitch - Value;

			FRotator CurrentRotator = PlayerRotator;
			PlayerDirection->SetWorldRotation(CurrentRotator);
		}
	}

	else
	{
		if ((Controller != nullptr) && (Value != 0.0f))
		{
			FRotator PlayerRotator = PlayerDirection->GetComponentRotation();
			PlayerRotator.Yaw = PlayerRotator.Yaw + Value;

			FRotator CurrentRotator = PlayerRotator;
			PlayerDirection->SetWorldRotation(CurrentRotator);
		}
	}
}

void ACapstone_TestCharacter::MenuUp()
{
	if (bUIControl)
	{
		OnPlayerMenuUpDelegate.Broadcast();
	}
}

void ACapstone_TestCharacter::MenuDown()
{
	if (bUIControl)
	{
		OnPlayerMenuDownDelegate.Broadcast();
	}
}

void ACapstone_TestCharacter::MenuRight()
{
	if (bUIControl)
	{
		OnPlayerMenuRightDelegate.Broadcast();
	}
}

void ACapstone_TestCharacter::MenuLeft()
{
	if (bUIControl)
	{
		OnPlayerMenuLeftDelegate.Broadcast();
	}
}

void ACapstone_TestCharacter::MenuClick()
{
	if (bUIControl)
	{
		OnPlayerMenuClickDelegate.Broadcast();
	}
}

void ACapstone_TestCharacter::MenuOut()
{
	if (bUIControl)
	{
		OnPlayerMenuOutDelegate.Broadcast();
	}
}