// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_GeneralDetect.generated.h"

/**
 * 
 */

UENUM()
enum class ECustomCollisionChannel_GeneralDetect : uint8
{
	ECC_AIDetect UMETA(DisplayName = "AIDetect"),
	// Add more custom collision channels if needed
};

UCLASS()
class CAPSTONE_TEST_API UBTService_GeneralDetect : public UBTService
{
	GENERATED_BODY()

public:
	UBTService_GeneralDetect();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
