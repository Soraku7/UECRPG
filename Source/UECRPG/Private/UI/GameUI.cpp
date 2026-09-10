// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/UI/GameUI.h"

#include "Public/SubSystem/UISystem.h"
#include "Public/UI/Inventory/InventoryUI.h"
#include "Runtime/UMG/Public/Components/Button.h"

void UGameUI::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UGameUI::BindDelegates()
{
	Super::BindDelegates();

	InventoryButton->OnClicked.AddDynamic(this , &UGameUI::ToggleInventory);
}

void UGameUI::UnBindDelegates()
{
	Super::UnBindDelegates();
	InventoryButton->OnClicked.Clear();
}

void UGameUI::ToggleInventory()
{
	GEngine->GameViewport->GetWorld()->GetGameInstance()->GetSubsystem<UUISystem>()->ToggleUI<UInventoryUI>();
}
