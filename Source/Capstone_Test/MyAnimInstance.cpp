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

	// ��Ÿ�ִ� ���� �ν��Ͻ����� ���� �������°ɷ�?
}

void UMyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto Pawn = TryGetPawnOwner(); // ���� �����ؼ� ���� �ӷ� ���� ���´�.
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