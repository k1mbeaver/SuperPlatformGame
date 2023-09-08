// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerLoadingUI.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONE_TEST_API UPlayerLoadingUI : public UUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY(Meta = (BindWidget))
		class UProgressBar* LoadingBar;

	UPROPERTY(Meta = (BindWidget))
		class UImage* LoadingImage;

	UPROPERTY(Meta = (BindWidget))
		class UTextBlock* LoadingText;

	int CurrentPercent = 0;
	bool bOnLoading = true;
protected:
	virtual void NativeOnInitialized() override;

public:
	void SetLoadingImage(int nMap);
	void SetLoadingText(int nMap);
	void InitProgressBar();
	void EngageProgressBar();
};
