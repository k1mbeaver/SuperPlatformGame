// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectController.h"
#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "MyHitObject.h"

const FName AObjectController::HomePosKey(TEXT("HomePos"));
const FName AObjectController::PatrolPosKey(TEXT("PatrolPos"));
const FName AObjectController::TargetKey(TEXT("SelfActor"));


AObjectController::AObjectController(FObjectInitializer const& object_initializer)
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT("BehaviorTree'/Game/AI/BT_HitObject.BT_HitObject'"));
	if (BTObject.Succeeded())
	{
		BTAsset = BTObject.Object;
	}

	BTAsset_Component = object_initializer.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("BehaviorComp"));
	BBAsset = object_initializer.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("BlackboardComp"));
}

void AObjectController::BeginPlay()
{
	Super::BeginPlay();

	RunBehaviorTree(BTAsset);
	BTAsset_Component->StartTree(*BTAsset);
}

void AObjectController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	myCharacter = Cast<AMyHitObject>(InPawn);
}

UBlackboardComponent* AObjectController::get_blackboard() const
{
	return BBAsset;
}

void AObjectController::RunAI()
{
	if (BBAsset)
	{
		BBAsset->InitializeBlackboard(*BTAsset->BlackboardAsset);
	}
}

void AObjectController::StopAI()
{
	if (this == nullptr) // 서버, 클라이언트 할때는 이거 해줘야하나?
	{
		return;
	}

	BTAsset_Component->StopTree(EBTStopMode::Safe);
}
