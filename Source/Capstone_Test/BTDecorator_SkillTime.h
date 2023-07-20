// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_SkillTime.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONE_TEST_API UBTDecorator_SkillTime : public UBTDecorator
{
	GENERATED_BODY()

public:
	UBTDecorator_SkillTime();

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
