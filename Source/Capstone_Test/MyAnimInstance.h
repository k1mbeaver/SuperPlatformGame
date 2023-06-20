// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MyAnimInstance.generated.h"

DECLARE_MULTICAST_DELEGATE(FDiveStart_DiveDelegate);
DECLARE_MULTICAST_DELEGATE(FDiveBash_DiveDelegate);
DECLARE_MULTICAST_DELEGATE(FDiveEnd_DiveDelegate);

/**
 * 
 */
UCLASS()
class CAPSTONE_TEST_API UMyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UMyAnimInstance();
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	void PlayAttackMontage(UAnimMontage* GetAttackMontage);
	void PlayDiveMontage(UAnimMontage* GetDiveMontage);
	void SetDeadAnim();

private:
	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
		float CurrentPawnSpeed; // AnimInstance�� ����ؼ� C++ ��ũ���� �� ���� �������Ʈ���� ����� �����ϴ�.

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
		bool IsInAir;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
		bool IsDead;

	//UFUNCTION()
		//void AnimNotify_SaveAttack();

	UFUNCTION()
		void AnimNotify_DiveStart();
	UFUNCTION()
		void AnimNotify_DiveEnd();
	UFUNCTION()
		void AnimNotify_DiveBash();

public:
	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
		bool IsAttacking;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
		bool IsCrouch;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
		bool IsBash;

	FDiveStart_DiveDelegate DiveStart_Dive;
	FDiveEnd_DiveDelegate DiveEnd_Dive;
	FDiveBash_DiveDelegate DiveBash_Dive;
};
