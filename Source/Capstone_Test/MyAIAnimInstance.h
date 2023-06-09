// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MyAIAnimInstance.generated.h"

DECLARE_MULTICAST_DELEGATE(FAttackStart_AttackDelegate);
DECLARE_MULTICAST_DELEGATE(FAttackEnd_AttackDelegate);
/**
 * 
 */
UCLASS()
class CAPSTONE_TEST_API UMyAIAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UMyAIAnimInstance();
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	void PlayAttackMontage(UAnimMontage* GetAttackMontage);
	void SetDeadAnim();

private:
	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
		float CurrentPawnSpeed; // AnimInstance�� ����ؼ� C++ ��ũ���� �� ���� �������Ʈ���� ����� �����ϴ�.

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
		bool IsInAir;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
		bool IsDead;

	UFUNCTION()
		void AnimNotify_AttackStart();

	UFUNCTION()
		void AnimNotify_AttackEnd();

public:
	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
		bool IsAttacking;

	FAttackStart_AttackDelegate AttackStart_Attack;
	FAttackEnd_AttackDelegate AttackEnd_Attack;
};
