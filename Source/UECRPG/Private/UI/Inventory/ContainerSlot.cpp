// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Inventory/ContainerSlot.h"

#include "Function/GlobalFunc.h"
#include "SubSystem/InventorySystem.h"
#include "UI/Item/ItemObject.h"

void UContainerSlot::DoAutoAction()
{
	DoAcquire();
}

void UContainerSlot::DoAcquire()
{
	UGlobalFunc::GetSubsystem<UInventorySystem>()->CollectItem(Item->GetItemID(), ItemNum);
}

void UContainerSlot::DoStore()
{
}

void UContainerSlot::DoDiscard()
{
	SetIconDragStatus(false);
}
