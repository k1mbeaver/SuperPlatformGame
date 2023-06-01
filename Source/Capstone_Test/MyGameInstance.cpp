// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "AIDataTableClass.h"
#include "CharacterDataTableClass.h"
#include "ObjectDataTableClass.h"

UMyGameInstance::UMyGameInstance()
{
	FString AIFileDataTable = TEXT("DataTable'/Game/DataTable/AIDataTable.AIDataTable'");

	static ConstructorHelpers::FObjectFinder<UDataTable> DT_AIFILE(*AIFileDataTable);

	if (DT_AIFILE.Succeeded())
	{
		FAITable = DT_AIFILE.Object;
	}
}
USkeletalMesh* UMyGameInstance::GetAISkeletalMesh(FString MonsterType)
{
	FAIDataTable* SkeletalData = FAITable->FindRow<FAIDataTable>(*MonsterType, TEXT(""));
	USkeletalMesh* mySkeletalMesh = SkeletalData->CharacterMesh;
	return mySkeletalMesh;
}