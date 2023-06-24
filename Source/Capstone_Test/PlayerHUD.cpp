// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHUD.h"
#include "PlayerMainUI.h"

/*
APlayerHUD::APlayerHUD()
{
	static ConstructorHelpers::FClassFinder<UPlayerMainUI> WB_Main(TEXT("WidgetBlueprint'/Game/WIdget/PlayerMainUI'"));
	if (WB_Main.Succeeded())
	{
		MainUIClass = WB_Main.Class;
	}
}

void APlayerHUD::BeginPlay()
{
	Super::BeginPlay();

	CheckUIObject(); // �����ϸ� UI�� �����Ѵ�.
}

bool APlayerHUD::CheckUIObject()
{
	if (MainUIObject == nullptr) // UI�� ���ٸ� ����.
	{
		return CreateUIObject();
	}
	return true; // �ִٸ� True.
}

bool APlayerHUD::CreateUIObject()
{
	if (MainUIClass)
	{
		MainUIObject = CreateWidget<UPlayerMainUI>(GetOwningPlayerController(), MainUIClass);
		if (MainUIObject)
		{
			MainUIObject->AddToViewport();
			return true; // ������ٸ� true.
		}
	}
	return false; // �� ������ٸ� false.
}

void APlayerHUD::SetHealthPersent(float PlayerHP)
{
	MainUIObject->SetHealthPersent(PlayerHP);
}

void APlayerHUD::SetStaminaPersent(float PlayerStamina)
{
	MainUIObject->SetStaminaPersent(PlayerStamina);
}

void APlayerHUD::SetImage(UTexture2D* CurrentImage)
{
	MainUIObject->SetImage(CurrentImage);
}

void APlayerHUD::SetImageUse()
{
	MainUIObject->SetImageUse();
}

void APlayerHUD::SetImageNotUse()
{
	MainUIObject->SetImageNotUse();
}

void APlayerHUD::SetImageVisible()
{
	MainUIObject->SetImageVisible();
}

void APlayerHUD::SetImageHidden()
{
	MainUIObject->SetImageHidden();
}

void APlayerHUD::SetProjectileText(int nProjectile)
{
	MainUIObject->SetProjectileText(nProjectile);
}

void APlayerHUD::SetDefaultText(int nProjectile)
{
	MainUIObject->SetDefaultText(nProjectile);
}

void APlayerHUD::SetTextVisible()
{
	MainUIObject->SetTextVisible();
}

void APlayerHUD::SetTextHidden()
{
	MainUIObject->SetTextHidden();
}

void APlayerHUD::SetInventoryHidden()
{
	MainUIObject->SetInventoryHidden();
}

void APlayerHUD::SetInventoryVisible()
{
	MainUIObject->SetInventoryVisible();
}

void APlayerHUD::SetListInit(int nIndex, FString strName, int nCount, UTexture2D* setImage)
{
	MainUIObject->SetListInit(nIndex, strName, nCount, setImage);
}

void APlayerHUD::SetListCount(int nIndex, int nCount)
{
	MainUIObject->SetListCount(nIndex, nCount);
}

void APlayerHUD::SetListView(int nIndex, FString strName, int nCount, UTexture2D* setImage)
{
	MainUIObject->SetListView(nIndex, strName, nCount, setImage);
}

void APlayerHUD::ListUpdate()
{
	MainUIObject->ListUpdate();
}

void APlayerHUD::SetWeaponImage(UTexture2D* setImage)
{
	MainUIObject->SetWeaponImage(setImage);
}

void APlayerHUD::SetEndHidden()
{
	MainUIObject->SetEndHidden();
}

void APlayerHUD::SetEndVisible()
{
	MainUIObject->SetEndVisible();
}

void APlayerHUD::SetWin()
{
	MainUIObject->SetWin();
}

void APlayerHUD::SetLose()
{
	MainUIObject->SetLose();
}

void APlayerHUD::SetPreviewUI()
{
	MainUIObject->SetPreviewUI();
}

void APlayerHUD::SetEsc(bool IsEsc)
{
	MainUIObject->SetEsc(IsEsc);
}
*/