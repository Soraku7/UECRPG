// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/ItemObject.h"

void UItemObject::Initialized(const int32 ItemID, const FItemData& InItemData)
{
	ID = ItemID;
	Data = FItemData::Set(InItemData);
}
