// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_Detect.h"
#include "MyAIController.h"
#include "MyAICharacter.h"
#include "Capstone_TestCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
//#include "PlayerUI_HUD.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"

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
    float DetectRadius = 1000.0f;

    if (nullptr == World)
        return;

    TArray<FOverlapResult> OverlapResults;
    FCollisionQueryParams CollisionQueryParam(NAME_None, false, ControllingPawn);
    bool bResult = World->OverlapMultiByChannel(OverlapResults, Center, FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel1, FCollisionShape::MakeSphere(DetectRadius), CollisionQueryParam);

    //APlayerUI_HUD* HUD = Cast<APlayerUI_HUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());

    AMyAICharacter* myMonster = Cast<AMyAICharacter>(ControllingPawn);

    if (bResult)
    {
        for (auto const& OverlapResult : OverlapResults)
        {
            ACapstone_TestCharacter* MyCharacter = Cast<ACapstone_TestCharacter>(OverlapResult.GetActor());
            //AMyAICharacter* MyAICharacter = Cast<AMyAICharacter>(OverlapResult.GetActor());

             //  && MyCharacter->GetController()->IsPlayerController()
            if (MyCharacter)
            {
                OwnerComp.GetBlackboardComponent()->SetValueAsObject(AMyAIController::TargetKey, MyCharacter);
                // DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Green, false, 0.2f);

                 //DrawDebugPoint(World, MyCharacter->GetActorLocation(), 10.0f, FColor::Blue, false, 0.2f);
                 //DrawDebugLine(World, ControllingPawn->GetActorLocation(), MyCharacter->GetActorLocation(), FColor::Blue, false, 0.2f);
                return;
            }

            else
            {
                OwnerComp.GetBlackboardComponent()->SetValueAsObject(AMyAIController::TargetKey, nullptr);
            }
        }
    }

    //DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Red, false, 0.2f);
}
