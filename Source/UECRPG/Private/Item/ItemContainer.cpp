// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/ItemContainer.h"

#include "Data/ItemDataStruct.h"
#include "Function/GlobalFunc.h"
#include "SubSystem/InventorySystem.h"
#include "UI/Item/ItemObject.h"


class UInventorySystem;
// Sets default values
AItemContainer::AItemContainer()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void AItemContainer::BeginPlay()
{
	Super::BeginPlay();

	for (const auto ItemPack : ItemPacks)
	{
		UItemObject* Item = UGlobalFunc::GetSubsystem<UInventorySystem>()->CreateItem(ItemPack.ItemID);
		if (IsValid(Item))
		{
			Item->Num = ItemPack.Num;
			ContainedItems.Add(Item);
		}
	}
}

void AItemContainer::AddItem(const int32 ItemID, const int32 Num)
{
	const auto CurItem = ContainedItems.FindByPredicate([ItemID](const UItemObject* ArrayItem)
	{
		return ArrayItem->GetItemID() == ItemID;
	});

	if (CurItem)
	{
		const auto CurItemRef = *CurItem;
		CurItemRef->Num += Num;

		if (CurItemRef->Num <= 0)
		{
			ContainedItems.Remove(CurItemRef);
		}
		return;
	}

	if (Num > 0)
	{
		const auto NewItem = UGlobalFunc::GetSubsystem<UInventorySystem>()->CreateItem(ItemID);
		if (IsValid(NewItem))
		{
			NewItem->Num = Num;
			ContainedItems.Add(NewItem);
		}
	}
}

void AItemContainer::RemoveALl()
{
	if (ContainedItems.Num() > 0)
	{
		for (const auto Item : ContainedItems)
		{
			UGlobalFunc::GetSubsystem<UInventorySystem>()->AddItem(Item->GetItemID(), Item->Num, false);
		}
		UGlobalFunc::GetSubsystem<UInventorySystem>()->DoItemChangeBroadcast();
		ContainedItems.Empty();
	}
}
