// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MyAIController.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONE_TEST_API AMyAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	AMyAIController(FObjectInitializer const& object_initializer);
	virtual void OnPossess(APawn* InPawn) override;
	void BeginPlay() override;

	class UBlackboardComponent* get_blackboard() const;

	static const FName HomePosKey;
	static const FName PatrolPosKey;
	static const FName TargetKey;
	static const FName NewTargetKey;

	void RunAI();
	void StopAI();

private:
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
		class UBehaviorTree* BTAsset;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
		class UBehaviorTreeComponent* BTAsset_Component;

	UPROPERTY()
		class UBlackboardComponent* BBAsset;

	UPROPERTY()
		class AMyAICharacter* myCharacter;
};
