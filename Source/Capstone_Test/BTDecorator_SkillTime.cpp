// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_SkillTime.h"
#include "MyBossAIController.h"
#include "MyBossMonster.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTDecorator_SkillTime::UBTDecorator_SkillTime()
{
    NodeName = TEXT("CanSkill");
}

bool UBTDecorator_SkillTime::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
    bool bResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

    // 나중에 이부분 구현 되면 조치하기
    
    int SkillTime = OwnerComp.GetBlackboardComponent()->GetValueAsInt(AMyBossAIController::SkillTime);
    bResult = (SkillTime == 20);
    
    return bResult;
}

