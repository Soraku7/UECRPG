// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/UI/Inventory/InventoryUI.h"


#include "Components/Button.h"
#include "Components/WrapBox.h"
#include "Data/GlobalEnum.h"
#include "Function/GlobalFunc.h"
#include "SubSystem/InventorySystem.h"
#include "UI/Inventory/InventorySlot.h"
#include "UI/Item/ItemObject.h"
#include "UI/Inventory/ItemTypeToggle.h"

void UInventoryUI::NativeOnInitialized()
{
	for (EItemType ItemType : TEnumRange<EItemType>())
	{
		const auto Toggle = CreateWidget<UItemTypeToggle>(this, UItemTypeToggleClass);
		Toggle->RefreshData(ItemType);
		Toggle->OnInitCallback([&](const UUniversalToggle* SelToggle)
		{
			OnToggleSelected(SelToggle);
		});
		ItemTypePanel->AddChild(Toggle);
		ItemTypeMap.Add(ItemType, Toggle);
	}

	ItemTypePanel->SetInnerSlotPadding(FVector2D(10, 5));


	for (uint8 i = 0; i < 20; i++)
	{
		AddSlot();
	}
	CurType = EItemType::All;
	for (const auto Toggle : ItemTypeMap)
	{
		Toggle.Value->SetSelected(Toggle.Key == CurType);
	}

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

void UInventoryUI::DoUnload()
{
	Super::DoUnload();
}

void UInventoryUI::RefreshData()
{
	uint8 Index = 0;
	for (auto Item : UGlobalFunc::GetSubsystem<UInventorySystem>()->GetItemsByType(CurType))
	{
		if (Item->GetData().bIsStackable)
		{
			const bool bTotalDivided = Item->Num % Item->GetData().MaxStack == 0;
			const uint8 SlotNeed = Item->Num / Item->GetData().MaxStack + (bTotalDivided ? 0 : 1);
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

void UInventoryUI::OnToggleSelected(const UUniversalToggle* SelectToggle)
{
	const auto Toggle = Cast<UItemTypeToggle>(SelectToggle);
	if (CurType == Toggle->GetItemType())
	{
		return;
	}
	
	ItemTypeMap[CurType]->SetSelected(false);
	CurType = Toggle->GetItemType();
	ItemTypeMap[CurType]->SetSelected(true);
	
	RefreshData();
}

void UInventoryUI::AddSlot()
{
	const auto ItemSlot = CreateWidget<UInventorySlot>(this, UInventorySlotClass);
	InventoryPanel->AddChild(ItemSlot);
	ItemSlot->RefreshData(nullptr);
	ItemSlot->SetParent(this);
	SlotItems.Add(ItemSlot);
}
