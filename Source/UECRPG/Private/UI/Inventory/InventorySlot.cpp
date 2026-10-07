// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/UI/Inventory/InventorySlot.h"


#include "Runtime/UMG/Public/Components/Image.h"
#include "Runtime/UMG/Public/Components/TextBlock.h"
#include "UI/Item/ItemObject.h"

void UInventorySlot::RefreshData(UItemObject* InItem, const int32 ShowNum)
{
	Item = InItem;
	ItemNum = ShowNum;

	if (IsValid(Item))
	{
		Icon->SetBrushFromTexture(Item->GetData().Icon);
		Icon->SetVisibility(ESlateVisibility::Visible);

		if (ItemNum > 1)
		{
			NumText->SetText(FText::AsNumber(ItemNum));
			NumText->SetVisibility(ESlateVisibility::Visible);
		}
		else
		{
			NumText->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
	else
	{
		Icon->SetVisibility(ESlateVisibility::Collapsed);
		NumText->SetVisibility(ESlateVisibility::Collapsed);
	}
}
