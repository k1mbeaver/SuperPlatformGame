// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ObjectController.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONE_TEST_API AObjectController : public AAIController
{
	GENERATED_BODY()

public:
	AObjectController(FObjectInitializer const& object_initializer);
	virtual void OnPossess(APawn* InPawn) override;
	void BeginPlay() override;

	class UBlackboardComponent* get_blackboard() const;

	static const FName HomePosKey;
	static const FName PatrolPosKey;
	static const FName TargetKey;

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
		class AMyHitObject* myCharacter;
};
