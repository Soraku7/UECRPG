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
		}
		return CurItemRef;
	}

	if (Num > 0)
	{
		const auto NewItem = CreateItem(ItemID);
		NewItem->Num = Num;
		CurTypeItems.ItemArray.Add(NewItem);
		Inventory.Add(ItemType, CurTypeItems);

		if (bAutoBroadCast)
		{
		}

		return NewItem;
	}

	return nullptr;
}

FItemData* UInventorySystem::GetItemData(const int32 ItemID) const
{
	if (IsValid(ItemDataTable))
	{
		FItemData* ItemData = ItemDataTable->FindRow<FItemData>(FName(*FString::FromInt(ItemID)), TEXT(""));
		return ItemData;
	}
}
