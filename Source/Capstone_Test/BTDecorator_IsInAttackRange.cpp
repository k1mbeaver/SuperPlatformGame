// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_IsInAttackRange.h"
#include "MyAIController.h"
#include "MyAICharacter.h"
#include "Capstone_TestCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTDecorator_IsInAttackRange::UBTDecorator_IsInAttackRange()
{
    NodeName = TEXT("CanAttack");
}

bool UBTDecorator_IsInAttackRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
    bool bResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

    auto ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
    if (ControllingPawn == nullptr)
        return false;

    auto Target = Cast<ACapstone_TestCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AMyAIController::TargetKey));
    if (Target == nullptr)
        return false;

    bResult = (Target->GetDistanceTo(ControllingPawn) <= 500.0f);
    return bResult;
}
