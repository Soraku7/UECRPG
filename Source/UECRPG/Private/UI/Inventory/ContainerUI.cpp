// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Inventory/ContainerUI.h"

#include "Function/GlobalFunc.h"
#include "Item/ItemContainer.h"
#include "Runtime/UMG/Public/Components/Button.h"
#include "Runtime/UMG/Public/Components/WrapBox.h"
#include "SubSystem/InventorySystem.h"
#include "UI/Inventory/ContainerSlot.h"
#include "UI/Inventory/DropArea.h"
#include "UI/Inventory/ItemDragDropOperation.h"
#include "UI/Item/ItemObject.h"

void UContainerUI::NativeOnInitialized()
{
	DropArea->SetParent(this);
	
	for (uint8 i = 0; i < 10; i++)
	{
		AddSlot();
	}

	Super::NativeOnInitialized();
}

void UContainerUI::BindDelegates()
{
	CollectAllBtn->OnClicked.AddDynamic(this, &UContainerUI::CollectAll);
	CloseBtn->OnClicked.AddDynamic(this, &UContainerUI::DoCloseAction);
	UGlobalFunc::GetSubsystem<UInventorySystem>()->OnItemCollectDelegate.AddDynamic(this, &UContainerUI::CollectItem);
}

void UContainerUI::UnBindDelegates()
{
	CollectAllBtn->OnClicked.Clear();
	CloseBtn->OnClicked.Clear();
	UGlobalFunc::GetSubsystem<UInventorySystem>()->OnItemCollectDelegate.
	                                               RemoveDynamic(this, &UContainerUI::CollectItem);
}

void UContainerUI::ShowItems(AItemContainer* Container)
{
	if (!IsValid(Container))
	{
		return;
	}

	ItemContainer = Container;
	const TArray<UItemObject*> ContainerItems = Container->GetContainedItems();

	uint8 Index = 0;
	for (auto Item : ContainerItems)
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

	CollectAllBtn->SetVisibility(Index > 0 ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
}

void UContainerUI::DoUnload()
{
	Super::DoUnload();
	ItemContainer = nullptr;
}

void UContainerUI::DoCloseAction()
{
	Super::DoCloseAction();
}

void UContainerUI::RefreshData()
{
}

void UContainerUI::CollectItem(const int32 ItemID, const int32 Num)
{
	if (IsValid(ItemContainer))
	{
		ItemContainer->AddItem(ItemID, -Num);
		ShowItems(ItemContainer);
	}
}

void UContainerUI::CollectAll()
{
	if (IsValid(ItemContainer))
	{
		ItemContainer->RemoveALl();
		ShowItems(ItemContainer);
	}
}

void UContainerUI::AddSlot()
{
	const auto ItemSlot = CreateWidget<UContainerSlot>(this, UContainerClass);
	ContainerPanel->AddChild(ItemSlot);
	ItemSlot->RefreshData(nullptr);
	ItemSlot->SetParent(this);
	SlotItems.Add(ItemSlot);
}

bool UContainerUI::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
                                UDragDropOperation* InOperation)
{
	const auto DragOperation = Cast<UItemDragDropOperation>(InOperation);

	if (IsValid(DragOperation))
	{
		if (DropArea->GetCachedGeometry().IsUnderLocation(InDragDropEvent.GetScreenSpacePosition()))
		{
			DropArea->HandleOnDrop(DragOperation->InventoryItem);
			return true;
		}
	}

	return false;
}
