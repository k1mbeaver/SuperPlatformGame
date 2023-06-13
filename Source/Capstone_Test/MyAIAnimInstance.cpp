// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAIAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/PawnMovementComponent.h"

UMyAIAnimInstance::UMyAIAnimInstance()
{
	CurrentPawnSpeed = 0.0f;
	IsInAir = false;
	IsDead = false;
	IsAttacking = false;

	// ��Ÿ�ִ� ���� �ν��Ͻ����� ���� �������°ɷ�?
}

void UMyAIAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
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

void UMyAIAnimInstance::PlayAttackMontage(UAnimMontage* GetAttackMontage)
{
	//if (IsAttacking == true)
	//{
		//Montage_Play(GetAttackMontage, 1.0f);
	//}
	Montage_Play(GetAttackMontage, 1.0f);
}

void UMyAIAnimInstance::SetDeadAnim()
{
	IsDead = true;
}

void UMyAIAnimInstance::AnimNotify_AttackStart()
{
	AttackStart_Attack.Broadcast();
	IsAttacking = true;
}

void UMyAIAnimInstance::AnimNotify_AttackEnd()
{
	AttackEnd_Attack.Broadcast();
	IsAttacking = false;
}