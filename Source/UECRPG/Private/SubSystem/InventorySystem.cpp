// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/SubSystem/InventorySystem.h"

#include "ItemObject.h"
#include "Data/ItemDataStruct.h"

FTypeItemHolder::FTypeItemHolder()
{
}

void UInventorySystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	ItemDataTable = LoadObject<UDataTable>(nullptr, TEXT("/Game/Data/ItemDataTable"));
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
	const auto ItemData = GetItemData(ItemID);
	if (!ItemData)
	{
		return nullptr;
	}

	EItemType ItemType = ItemData->ItemType;

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

FItemData* UInventorySystem::GetItemData(const int32 ItemID) const
{
	if (IsValid(ItemDataTable))
	{
		FItemData* ItemData = ItemDataTable->FindRow<FItemData>(FName(*FString::FromInt(ItemID)), TEXT(""));
		return ItemData;
	}

	return nullptr;
}

UItemObject* UInventorySystem::GetItem(const int32 ItemID) const
{
	const auto ItemData = GetItemData(ItemID);
	if (!ItemData)
		return nullptr;

	const EItemType ItemType = ItemData->ItemType;
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
	const auto ItemData = GetItemData(ItemID);
	if (!ItemData)
		return nullptr;

	const EItemType ItemType = ItemData->ItemType;
	if (ItemType == EItemType::All)
		return nullptr;

	UItemObject* Item;

	switch (ItemType)
	{
	case EItemType::Consumable:
		Item = NewObject<UItemObject>();
		break;
	default:
		Item = NewObject<UItemObject>();
		break;
	}

	Item->Initialized(ItemID, *ItemData);
	return Item;
}
