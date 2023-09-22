// Fill out your copyright notice in the Description page of Project Settings.


#include "StartAIController.h"
#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "MyAICharacter.h"

const FName AStartAIController::HomePosKey(TEXT("HomePos"));
const FName AStartAIController::PatrolPosKey(TEXT("PatrolPos"));
const FName AStartAIController::TargetKey(TEXT("SelfActor"));


AStartAIController::AStartAIController(FObjectInitializer const& object_initializer)
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT("BehaviorTree'/Game/AI/BT_StartAI.BT_StartAI'"));
	if (BTObject.Succeeded())
	{
		BTAsset = BTObject.Object;
	}

	BTAsset_Component = object_initializer.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("BehaviorComp"));
	BBAsset = object_initializer.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("BlackboardComp"));
}

void AStartAIController::BeginPlay()
{
	Super::BeginPlay();

	RunBehaviorTree(BTAsset);
	BTAsset_Component->StartTree(*BTAsset);
}

void AStartAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	myCharacter = Cast<AMyAICharacter>(InPawn);
}

UBlackboardComponent* AStartAIController::get_blackboard() const
{
	return BBAsset;
}

void AStartAIController::RunAI()
{
	if (BBAsset)
	{
		BBAsset->InitializeBlackboard(*BTAsset->BlackboardAsset);
	}
}

void AStartAIController::StopAI()
{
	if (this == nullptr) // 서버, 클라이언트 할때는 이거 해줘야하나?
	{
		return;
	}

	BTAsset_Component->StopTree(EBTStopMode::Safe);
}
