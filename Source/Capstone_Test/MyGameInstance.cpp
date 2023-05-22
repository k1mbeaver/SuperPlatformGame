// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "AIDataTableClass.h"
#include "CharacterDataTableClass.h"
#include "ObjectDataTableClass.h"

/*
int UMyGameInstance::GetInventoryItemCount(int nSlot)
{
	FString strSlot = FString::FromInt(nSlot);
	FInventoryDataTable* InventoryData = FInventoryTable->FindRow<FInventoryDataTable>(*strSlot, TEXT(""));
	int ItemCount = InventoryData->ItemCount;
	return ItemCount;
}

void UMyGameInstance::SetInventoryItemCount(int nSlot, int nCount)
{
	FString strSlot = FString::FromInt(nSlot);
	FInventoryDataTable* InventoryData = FInventoryTable->FindRow<FInventoryDataTable>(*strSlot, TEXT(""));
	InventoryData->ItemCount = nCount;
}
*/