// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAIController.h"
#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "MyAICharacter.h"

const FName AMyAIController::HomePosKey(TEXT("HomePos"));
const FName AMyAIController::PatrolPosKey(TEXT("PatrolPos"));
const FName AMyAIController::TargetKey(TEXT("Target"));
const FName AMyAIController::SkillTime(TEXT("SkillTime"));
const FName AMyAIController::bUIPrint(TEXT("bUIPrint"));


AMyAIController::AMyAIController(FObjectInitializer const& object_initializer)
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT("BehaviorTree'/Game/AI/BT_AIMonster.BT_AIMonster'"));
	if (BTObject.Succeeded())
	{
		BTAsset = BTObject.Object;
	}

	BTAsset_Component = object_initializer.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("BehaviorComp"));
	BBAsset = object_initializer.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("BlackboardComp"));
}

void AMyAIController::BeginPlay()
{
	Super::BeginPlay();

	RunBehaviorTree(BTAsset);
	BTAsset_Component->StartTree(*BTAsset);
}

void AMyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	myCharacter = Cast<AMyAICharacter>(InPawn);
}

UBlackboardComponent* AMyAIController::get_blackboard() const
{
	return BBAsset;
}

void AMyAIController::RunAI()
{
	if (BBAsset)
	{
		BBAsset->InitializeBlackboard(*BTAsset->BlackboardAsset);
	}
}

void AMyAIController::StopAI()
{
	if (this == nullptr) // 서버, 클라이언트 할때는 이거 해줘야하나?
	{
		return;
	}

	BTAsset_Component->StopTree(EBTStopMode::Safe);
}

/*
void AMyAIController::EndIntro() // 여기서 BT를 실행시킨다.
{
	RunBehaviorTree(BTAsset);
	BTAsset_Component->StartTree(*BTAsset);
}
*/

