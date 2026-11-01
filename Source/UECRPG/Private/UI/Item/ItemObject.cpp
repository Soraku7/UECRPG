// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Item/ItemObject.h"

#include "Function/GlobalFunc.h"
#include "SubSystem/DataSystem.h"


void UItemObject::Initialized(const int32 ItemID)
{
	const auto TbItemData = UGlobalFunc::GetSubsystem<UDataSystem>()->GetTbItemData(ItemID);
	if (TbItemData != nullptr)
	{
		ID = TbItemData->id;
		InfoData = FInfoData(TbItemData->basicInfo);
		Data = FItemData(TbItemData->itemData);
	}
}
