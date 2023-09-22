// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerPlayUI.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONE_TEST_API UPlayerPlayUI : public UUserWidget
{
	GENERATED_BODY()

		
private:
	UPROPERTY(Meta = (BindWidget))
		class UTextBlock* TextCharacterCount;

	UPROPERTY(Meta = (BindWidget))
		class UTextBlock* TextCoinCount;

	UPROPERTY(Meta = (BindWidget))
		class UTextBlock* TextGemCount;

	UPROPERTY(Meta = (BindWidget))
		class UTextBlock* TextStarCount;

protected:
	virtual void NativeOnInitialized() override;

public:
	// ����� �Լ����� ����
	void SetCharacterCount(int nCount);
	void SetCoinCount(int nCount);
	void SetGemCount(int nCount);
	void SetStarCount(int nCount);
};
