// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/UI/Inventory/InventoryUI.h"

#include "ItemObject.h"
#include "Components/Button.h"
#include "Components/WrapBox.h"
#include "Data/GlobalEnum.h"
#include "Function/GlobalFunc.h"
#include "SubSystem/InventorySystem.h"
#include "UI/Inventory/InventorySlot.h""

void UInventoryUI::NativeOnInitialized()
{
	for (int i = 0; i < 20; i++)
	{
		AddSlot();
	}
	CurType = EItemType::All;

	Super::NativeOnInitialized();
}

void UInventoryUI::BindDelegates()
{
	CloseBtn->OnClicked.AddDynamic(this, &UInventoryUI::DoCloseAction);
	UGlobalFunc::GetSubsystem<UInventorySystem>()->OnItemChangeDelegate.AddDynamic(
		this, &UInventoryUI::OnRefreshInventory);
}

void UInventoryUI::UnBindDelegates()
{
	CloseBtn->OnClicked.Clear();
	UGlobalFunc::GetSubsystem<UInventorySystem>()->OnItemChangeDelegate.RemoveDynamic(
		this, &UInventoryUI::OnRefreshInventory);
}

void UInventoryUI::DoLoad()
{
	Super::DoLoad();
	RefreshData();
}

void UInventoryUI::RefreshData()
{
	uint8 Index = 0;
	for (auto Item : UGlobalFunc::GetSubsystem<UInventorySystem>()->GetItemsByType(CurType))
	{
		if (Item->GetData().bIsStackable)
		{
			const bool bTotalDivided = Item->Num % Item->GetData().MaxStack == 0;
			const uint8 SlotNeed = Item->Num / Item->GetData().MaxStack;
			for (uint8 i = 0; i < SlotNeed; i++)
			{
				const uint8 ShowNum = (i < SlotNeed - 1 || bTotalDivided)
					                      ? Item->GetData().MaxStack
					                      : Item->Num % Item->GetData().MaxStack;
				if (Index >= SlotItems.Num())
				{
					AddSlot();
				}
				SlotItems[Index++]->RefreshData(Item, ShowNum);
			}
		}
		else
		{
			for (uint8 i = 0; i < Item->Num; i++)
			{
				if (Index >= SlotItems.Num())
				{
					AddSlot();
				}
				SlotItems[Index++]->RefreshData(Item);
			}
		}
	}

	for (uint8 i = Index; i < SlotItems.Num(); i++)
	{
		SlotItems[i]->RefreshData(nullptr);
	}
}

void UInventoryUI::OnRefreshInventory(const int32 ItemID)
{
	RefreshData();
}

void UInventoryUI::AddSlot()
{
	const auto ItemSlot = CreateWidget<UInventorySlot>(this, UInventorySlotClass);
	InventoryPanel->AddChild(ItemSlot);
	ItemSlot->RefreshData();
	ItemSlot->SetParent(this);
	SlotItems.Add(ItemSlot);
}
