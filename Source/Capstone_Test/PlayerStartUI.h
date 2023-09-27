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

	UPROPERTY(Meta = (BindWidget))
		class UButton* BtSetting;

	UPROPERTY(Meta = (BindWidget))
		class UButton* BtSettingExit;

	UPROPERTY(Meta = (BindWidget))
		class USlider* BGSlider;

	UPROPERTY(Meta = (BindWidget))
		class USlider* EffectSlider;

	UPROPERTY(Meta = (BindWidget))
		class USlider* CharacterSlider;

	UPROPERTY(Meta = (BindWidget))
		class UCanvasPanel* SettingCanvas;

	ACapstone_TestCharacter* myCharacter;

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
public:
	UFUNCTION(BlueprintCallable)
		void GameExit();

	UFUNCTION(BlueprintCallable)
		void GameStart();

	UFUNCTION(BlueprintCallable)
		void GameSetting();

	UFUNCTION(BlueprintCallable)
		void VisibleSetting(bool bVisible);

	UFUNCTION(BlueprintCallable)
		void SetBGVolume(float myVolume);

	UFUNCTION(BlueprintCallable)
		void SetCharacterVolume(float myVolume);

	UFUNCTION(BlueprintCallable)
		void SetEffectVolume(float myVolume);

	UFUNCTION(BlueprintCallable)
		void MenuUp();

	UFUNCTION(BlueprintCallable)
		void MenuDown();

	UFUNCTION(BlueprintCallable)
		void MenuRight();

	UFUNCTION(BlueprintCallable)
		void MenuLeft();

	UFUNCTION(BlueprintCallable)
		void MenuClick();

	UFUNCTION(BlueprintCallable)
		void MenuOut();
};
