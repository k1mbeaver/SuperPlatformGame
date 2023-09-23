// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerStartUI.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONE_TEST_API UPlayerStartUI : public UUserWidget
{
	GENERATED_BODY()
	
private:
	UPROPERTY(Meta = (BindWidget))
		class UButton* BtExit;


	UPROPERTY(Meta = (BindWidget))
		class UButton* BtStart;

protected:
	virtual void NativeOnInitialized() override;

public:
	UFUNCTION(BlueprintCallable)
		void GameExit();

	UFUNCTION(BlueprintCallable)
		void GameStart();
};
