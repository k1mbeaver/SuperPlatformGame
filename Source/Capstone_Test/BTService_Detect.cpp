// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_Detect.h"
#include "MyAIController.h"
#include "MyAICharacter.h"
#include "Capstone_TestCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "MyBossMonster.h"
#include "MyBossAIController.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "MyBossAIController.h"

UBTService_Detect::UBTService_Detect()
{
    NodeName = TEXT("Detect");
    Interval = 0.3f;
}

void UBTService_Detect::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
    if (nullptr == ControllingPawn)
        return;

    UWorld* World = ControllingPawn->GetWorld();
    FVector Center = ControllingPawn->GetActorLocation();
    float DetectRadius = 500.0f;

    if (nullptr == World)
        return;

    TArray<FOverlapResult> OverlapResults;
    FCollisionQueryParams CollisionQueryParam(NAME_None, false, ControllingPawn);
    bool bResult = World->OverlapMultiByChannel(OverlapResults, Center, FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel6, FCollisionShape::MakeSphere(DetectRadius), CollisionQueryParam);

    AMyBossMonster* myMonster = Cast<AMyBossMonster>(ControllingPawn);

    if (bResult)
    {
        for (auto const& OverlapResult : OverlapResults)
        {
            ACapstone_TestCharacter* MyCharacter = Cast<ACapstone_TestCharacter>(OverlapResult.GetActor());

            if (MyCharacter)
            {
                int SkillTime = OwnerComp.GetBlackboardComponent()->GetValueAsInt(AMyBossAIController::SkillTime);
                SkillTime++;

                if (SkillTime == 20 && bSkill == true)
                {
                    myMonster->SkillEnd();
                    bSkill = false;
                }

                if (SkillTime > 40) // 스킬 쿨이 50이 넘어가면 사용후
                {
                    SkillTime = 0; // 초기화
                    bSkill = true;
                }

                OwnerComp.GetBlackboardComponent()->SetValueAsObject(AMyBossAIController::TargetKey, MyCharacter);
                OwnerComp.GetBlackboardComponent()->SetValueAsInt(AMyBossAIController::SkillTime, SkillTime);
                DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Green, false, 0.2f);

                DrawDebugPoint(World, MyCharacter->GetActorLocation(), 10.0f, FColor::Blue, false, 0.2f);
                DrawDebugLine(World, ControllingPawn->GetActorLocation(), MyCharacter->GetActorLocation(), FColor::Blue, false, 0.2f);
                return;
            }

            else
            {
                OwnerComp.GetBlackboardComponent()->SetValueAsObject(AMyBossAIController::TargetKey, nullptr);
            }
        }
    }

    DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Red, false, 0.2f);
}
