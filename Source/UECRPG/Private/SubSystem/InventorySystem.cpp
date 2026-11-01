// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/SubSystem/InventorySystem.h"

#include "Data/ItemDataStruct.h"
#include "Function/GlobalFunc.h"
#include "SubSystem/DataSystem.h"
#include "UI/Item/ItemObject.h"

FTypeItemHolder::FTypeItemHolder()
{
}

void UInventorySystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

TArray<UItemObject*> UInventorySystem::GetAllItems()
{
	TArray<UItemObject*> AllItems;

	for (const auto TypeItem : Inventory)
	{
		for (const auto Item : TypeItem.Value.ItemArray)
		{
			AllItems.Add(Item);
		}
	}

	return AllItems;
}

TArray<UItemObject*> UInventorySystem::GetItemsByType(const EItemType ItemType)
{
	if (ItemType == EItemType::All)
	{
		return GetAllItems();
	}

	return Inventory.FindRef(ItemType).ItemArray;
}

UItemObject* UInventorySystem::AddItem(const int32 ItemID, const int32 Num, const bool bAutoBroadCast)
{
	const EItemType ItemType = GetItemType(ItemID);
	if (ItemType == EItemType::All)
		return nullptr;

	if (!Inventory.Contains(ItemType))
	{
		const FTypeItemHolder NewTypeItemHolder;
		Inventory.Add(ItemType, NewTypeItemHolder);
	}

	auto CurTypeItems = Inventory.FindRef(ItemType);
	const auto CurItem = CurTypeItems.ItemArray.FindByPredicate([ItemID](const UItemObject* ArrayItem)
	{
		return ArrayItem->GetItemID() == ItemID;
	});

	if (CurItem)
	{
		const auto CurItemRef = *CurItem;
		CurItemRef->Num += Num;

		if (CurItemRef->Num <= 0)
		{
			CurTypeItems.ItemArray.Remove(CurItemRef);
			Inventory.Add(ItemType, CurTypeItems);
		}

		if (bAutoBroadCast)
		{
			if (OnItemChangeDelegate.IsBound())
			{
				OnItemChangeDelegate.Broadcast(ItemID);
			}
		}
		return CurItemRef;
	}

	if (Num > 0)
	{
		const auto NewItem = CreateItem(ItemID);
		if (!IsValid(NewItem))
			return nullptr;

		NewItem->Num = Num;

		CurTypeItems.ItemArray.Add(NewItem);
		Inventory.Add(ItemType, CurTypeItems);

		if (bAutoBroadCast)
		{
			if (OnItemChangeDelegate.IsBound())
			{
				OnItemChangeDelegate.Broadcast(ItemID);
			}
		}

		return NewItem;
	}

	return nullptr;
}

UItemObject* UInventorySystem::ReduceItem(const int32 ItemID, const int32 Num, const bool bAutoBroadCast)
{
	return AddItem(ItemID, -Num, bAutoBroadCast);
}

void UInventorySystem::CollectItem(const int32 ItemID, const int32 Num)
{
	AddItem(ItemID, Num, true);
	BroadcastItemCollect(ItemID, Num);
}

EItemType UInventorySystem::GetItemType(const int32 ItemID) const
{
	const auto TbItemData = UGlobalFunc::GetSubsystem<UDataSystem>()->GetTbItemData(ItemID);
	if (TbItemData != nullptr)
	{
		return static_cast<EItemType>(TbItemData->itemData->type);
	}
	return EItemType::All;
}

UItemObject* UInventorySystem::GetItem(const int32 ItemID) const
{
	const EItemType ItemType = GetItemType(ItemID);
	if (ItemType == EItemType::All)
		return nullptr;

	if (!Inventory.Contains(ItemType))
		return nullptr;

	auto CurTypeItems = Inventory.FindRef(ItemType);
	const auto CurItem = CurTypeItems.ItemArray.FindByPredicate([ItemID](const UItemObject* ArrayItem)
	{
		return ArrayItem->GetItemID() == ItemID;
	});

	if (CurItem)
	{
		return *CurItem;
	}
	return nullptr;
}

int32 UInventorySystem::GetItemNum(const int32 ItemID) const
{
	const auto CurItem = GetItem(ItemID);
	if (!IsValid(CurItem))
		return 0;

	return CurItem->Num;
}

UItemObject* UInventorySystem::CreateItem(const int32 ItemID)
{
	const EItemType ItemType = GetItemType(ItemID);
	if (ItemType == EItemType::All)
		return nullptr;

	UItemObject* Item = NewObject<UItemObject>();

	// switch (ItemType)
	// {
	// case EItemType::Consumable:
	// 	Item = NewObject<UItemObject>();
	// 	break;
	// default:
	// 	Item = NewObject<UItemObject>();
	// 	break;
	// }

	Item->Initialized(ItemID);
	return Item;
}

void UInventorySystem::BroadcastItemChange() const
{
	if (OnItemChangeDelegate.IsBound())
	{
		OnItemChangeDelegate.Broadcast(0);
	}
}

void UInventorySystem::BroadcastItemCollect(const int32 ItemID, const int32 Num) const
{
	if (OnItemCollectDelegate.IsBound())
	{
		OnItemCollectDelegate.Broadcast(ItemID, Num);
	}
}

void UInventorySystem::BroadcastOnDragStatus(const bool bIsDragging) const
{
	if (OnDragDelegate.IsBound())
	{
		OnDragDelegate.Broadcast(bIsDragging);
	}
}
