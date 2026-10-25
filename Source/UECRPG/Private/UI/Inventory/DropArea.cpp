// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Inventory/DropArea.h"

#include "Function/GlobalFunc.h"
#include "SubSystem/InventorySystem.h"
#include "UI/GameUI.h"
#include "UI/UIBase.h"
#include "UI/Inventory/ContainerUI.h"
#include "UI/Inventory/InventorySlot.h"
#include "UI/Inventory/InventoryUI.h"

void UDropArea::HandleOnDrop(UInventorySlot* DropItem) const
{
	if (ParentUI != DropItem->GetParentUI())
	{
		if (ParentUI->IsA(UInventoryUI::StaticClass()))
		{
			DropItem->DoAcquire();
		}
		else if (ParentUI->IsA(UContainerUI::StaticClass()))
		{
			DropItem->DoStore();
		}
		else if (ParentUI->IsA(UGameUI::StaticClass()))
		{
			DropItem->DoDiscard();
		}
	}
	else
	{
		DropItem->SetIconDragStatus(false);
	}

	UGlobalFunc::GetSubsystem<UInventorySystem>()->BroadcastOnDragStatus(false);
}
