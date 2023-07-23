// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyBossMonster.generated.h"

UCLASS()
class CAPSTONE_TEST_API AMyBossMonster : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyBossMonster();

	//UPROPERTY(VisibleInstanceOnly, Category = Animation)
		//class UAIAnimInstance* AIAnim;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		float AttackPower;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		float AttackRange;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		float AttackRadius;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		float SkillPower;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		float SkillRange;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		float SkillRadius;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Speed, Meta = (AllowPrivateAccess = true))
		float MonsterSpeed;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		bool bCanAttack;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = HP, Meta = (AllowPrivateAccess = true))
		float fAIHp;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = HP, Meta = (AllowPrivateAccess = true))
		float fMaxHp;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Alive, Meta = (AllowPrivateAccess = true))
		bool bAlive;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Type)
		FString strMonsterType;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		UAnimMontage* AttackMontage;

	//UPROPERTY(VisibDleDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		//UAnimMontage* SkillMontage;

	UPROPERTY(VisibleInstanceOnly, Category = Animation)
		class UMyAIAnimInstance* MonsterAnim;

	//UPROPERTY()
		//class UParticleSystem* AttackParticle;

	//UPROPERTY()
		//class UParticleSystem* IntroParticle;

	//UPROPERTY()
		//class UParticleSystem* SkillParticle;

	// damage particle
	UPROPERTY()
		class UParticleSystem* DamageParticle;

	UPROPERTY()
		class UGameplayStatics* GameStatic;

	class UMyGameInstance* myGameInstance;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	float CharacterHP = 0.0f;
	float CharacterDefaultHP = 0.0f;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//virtual void PostInitializeComponents() override;

	//float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamasgeCauser) override;

	void Attack();
	void StartAttackAnimation();
	void StopAttackAnimation();
	UFUNCTION(BlueprintCallable)
		void Death();
	void Skill();
	void SkillEnd();
	//void AttackEnd();
	//void SkillEnd();
	//void AttackCheck();
	//void SkillCheck();
	//void AttackCheck();
	//void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);
	//void AttackByPlayer(float DamageAmount);
	//void MoveMonster();
	//void FindPlayer();
	//void StopMonster();
	//void StopAIController();
	//void InitializeAI(FString MonsterType);
	//void AttackParticleStart(FVector StartParticle);
	//void IntroParticleStart();
	//void SkillParticleStart();
	//void SkillParticleEnd();
	//void DropItem();
	//void MonsterDestory();
};
