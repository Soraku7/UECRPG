// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Inventory/ItemTypeToggle.h"

#include "UECRPG.h"

void UItemTypeToggle::RefreshData(const EItemType InType)
{
	ItemType = InType;
	SetText(ItemTypeName[static_cast<uint8>(InType)]);
}
