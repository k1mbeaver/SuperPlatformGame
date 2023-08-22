// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerStageUI.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONE_TEST_API UPlayerStageUI : public UUserWidget
{
	GENERATED_BODY()
	
private:
	UPROPERTY(Meta = (BindWidget))
		class UTextBlock* TextStage;

	UPROPERTY(Meta = (BindWidget))
		class UTextBlock* TextDefault;

	UPROPERTY(Meta = (BindWidget))
		class UTextBlock* TextPressBar;

protected:
	virtual void NativeOnInitialized() override;

public:
	// 사용할 함수들을 정리
	void SetStage(int nCount);
};
