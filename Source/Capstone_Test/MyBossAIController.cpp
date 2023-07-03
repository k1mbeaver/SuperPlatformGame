// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBossAIController.h"
#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "MyBossMonster.h"

const FName AMyBossAIController::HomePosKey(TEXT("HomePos"));
const FName AMyBossAIController::PatrolPosKey(TEXT("PatrolPos"));
const FName AMyBossAIController::TargetKey(TEXT("Target"));


AMyBossAIController::AMyBossAIController(FObjectInitializer const& object_initializer)
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT("BehaviorTree'/Game/AI/BT_AIBossMonster.BT_AIBossMonster'"));
	if (BTObject.Succeeded())
	{
		BTAsset = BTObject.Object;
	}

	BTAsset_Component = object_initializer.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("BehaviorComp"));
	BBAsset = object_initializer.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("BlackboardComp"));
}

void AMyBossAIController::BeginPlay()
{
	Super::BeginPlay();

	RunBehaviorTree(BTAsset);
	BTAsset_Component->StartTree(*BTAsset);
}

void AMyBossAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	myCharacter = Cast<AMyBossMonster>(InPawn);
}

UBlackboardComponent* AMyBossAIController::get_blackboard() const
{
	return BBAsset;
}

void AMyBossAIController::RunAI()
{
	if (BBAsset)
	{
		BBAsset->InitializeBlackboard(*BTAsset->BlackboardAsset);
	}
}

void AMyBossAIController::StopAI()
{
	if (this == nullptr) // 서버, 클라이언트 할때는 이거 해줘야하나?
	{
		return;
	}

	BTAsset_Component->StopTree(EBTStopMode::Safe);
}


