// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Capstone_TestCharacter.generated.h"

UENUM(BlueprintType)
enum class ECharacterState : uint8
{
	CROUCH, // 웅크린상태
	DOWN, // 엎드린 상태
	STAND, // 서있는 상태
	RUN, // 달리는 상태
	BASH, // 가속 상태
	DEATH,	// 죽은 상태
	//이후에 추가하자
};

UCLASS(config=Game)
class ACapstone_TestCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		UAnimMontage* myDiveMontage;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		USceneComponent* BashMuzzleLocation;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = Niagara, Meta = (AllowPrivateAccess = true))
		class UNiagaraComponent* NiagaraComponent;

	class UMyGameInstance* myGameInstance;

	UPROPERTY()
		class UGameplayStatics* GameStatic;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		class AMyPortal* PlayerPortal;
public:
	ACapstone_TestCharacter();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Input)
	float TurnRateGamepad;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = State)
		ECharacterState CurrentState = ECharacterState::STAND;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = State)
		bool bGameClear = false;
protected:

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	//void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	//void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Tick(float DeltaTime) override;
	// End of APawn interface
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	bool bCameraMove = false;
	bool bCanMove = true;
	bool bAlive = true;
	bool bCameraForward = false;

	float CharacterHP = 0.0f;
	float CharacterDefaultHP = 0.0f;

	int CurrentLife = 0;
	int CurrentCoin = 0;
	int CurrentStar = 0;
	int CurrentGem = 0;

	float AttackRange = 100.0f;
	float AttackRadius = 50.0f;

private:
	class UMyAnimInstance* myAnimInstance;
public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	float LerpFun(float beginValue, float endValue, float t) {
		return beginValue * (1 - t) + (endValue * t);
	};

	void TransCameraPos(float t, float targetRatio);
	void ReturnTransCameraPos(float t, float targetRatio);

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	void BulletTime();

	void StopBulletTime();

	void TransCamera();

	void StopTransCamera();

	void CameraChange();

	void Run();

	void StopRun();

	void Crouching();

	void StopCrouch();

	void CharacterDown();

	void StopDown();

	void Bash();

	void StopBash();

	void StartBashAnimation();

	void CurrentBash();

	void StopBashAnimation();

	void Death();

	void AttackCheck();

	UFUNCTION(BlueprintCallable)
		void CoinGet();

	UFUNCTION(BlueprintCallable)
		void StarGet();

	UFUNCTION(BlueprintCallable)
		void GemGet();

	UFUNCTION(BlueprintCallable)
		void PlayerDead();
};

