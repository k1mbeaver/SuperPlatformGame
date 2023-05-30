// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/PawnMovementComponent.h"

UMyAnimInstance::UMyAnimInstance()
{
	CurrentPawnSpeed = 0.0f;
	IsInAir = false;
	IsDead = false;
	IsCrouch = false;
	IsBash = false;

	// 몽타주는 게임 인스턴스에서 직접 가져오는걸로?
}

void UMyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto Pawn = TryGetPawnOwner(); // 폰에 접근해서 폰의 속력 값을 얻어온다.
	if (!::IsValid(Pawn)) return;

	if (!IsDead)
	{
		CurrentPawnSpeed = Pawn->GetVelocity().Size();
		auto Character = Cast<ACharacter>(Pawn);
		if (Character)
		{
			IsInAir = Character->GetMovementComponent()->IsFalling();
		}
	}
}

void UMyAnimInstance::PlayAttackMontage(UAnimMontage* GetAttackMontage)
{
	if (IsAttacking == true)
	{
		Montage_Play(GetAttackMontage, 1.0f);
	}
}

void UMyAnimInstance::SetDeadAnim()
{
	IsDead = true;
}