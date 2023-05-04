// Copyright Epic Games, Inc. All Rights Reserved.

#include "Capstone_TestCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"

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
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
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

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
}

void ACapstone_TestCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	/*
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
		TransCameraPos(0.05, 1.2);
		// 나중에 편집하기
	}
	*/
	
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
			TransCameraPos(0.05, 1.2);
			// 나중에 편집하기
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
			ReturnTransCameraPos(0.05, 1.2);
			// 나중에 편집하기
		}
	}
	
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

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	//PlayerInputComponent->BindAxis("Turn Right / Left Mouse", this, &APawn::AddControllerYawInput);
	//PlayerInputComponent->BindAxis("Turn Right / Left Gamepad", this, &ACapstone_TestCharacter::TurnAtRate);
	//PlayerInputComponent->BindAxis("Look Up / Down Mouse", this, &APawn::AddControllerPitchInput);
	//PlayerInputComponent->BindAxis("Look Up / Down Gamepad", this, &ACapstone_TestCharacter::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &ACapstone_TestCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &ACapstone_TestCharacter::TouchStopped);
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

void ACapstone_TestCharacter::TransCameraPos(float t, float targetRatio) {
	//float EndArmValue = LerpFun(CameraBoom->TargetArmLength, 0, targetRatio);
	//float EndSocketValue = LerpFun(CameraBoom->SocketOffset.Z, 0, targetRatio);
	float EndArmValue = LerpFun(500.0f, 0, targetRatio);
	float EndSocketValue = LerpFun(200.0f, 0, targetRatio);
	CameraBoom->TargetArmLength = LerpFun(CameraBoom->TargetArmLength, EndArmValue, t);
	CameraBoom->SocketOffset.Z = LerpFun(CameraBoom->SocketOffset.Z, EndSocketValue, t);
}

void ACapstone_TestCharacter::ReturnTransCameraPos(float t, float targetRatio) {
	//float EndArmValue = LerpFun(CameraBoom->TargetArmLength, 0, targetRatio);
	//float EndSocketValue = LerpFun(CameraBoom->SocketOffset.Z, 0, targetRatio);
	float EndArmValue = LerpFun(CameraBoom->TargetArmLength, 500.0f, targetRatio);
	float EndSocketValue = LerpFun(CameraBoom->SocketOffset.Z, 200.0f, targetRatio);
	CameraBoom->TargetArmLength = LerpFun(CameraBoom->TargetArmLength, EndArmValue, t);
	CameraBoom->SocketOffset.Z = LerpFun(CameraBoom->SocketOffset.Z, EndSocketValue, t);
}

void ACapstone_TestCharacter::Run()
{
	CurrentState = ECharacterState::RUN;
	bCameraMove = true;
}

void ACapstone_TestCharacter::StopRun()
{
	CurrentState = ECharacterState::STAND;
	bCameraMove = false;
}

void ACapstone_TestCharacter::Crouch()
{
	CurrentState = ECharacterState::CROUCH;
	bCameraMove = true;
}

void ACapstone_TestCharacter::StopCrouch()
{
	CurrentState = ECharacterState::STAND;
	bCameraMove = false;
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

}

void ACapstone_TestCharacter::StopBash()
{

}

