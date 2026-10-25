// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Inventory/DragItem.h"

#include "Runtime/UMG/Public/Components/Image.h"
#include "UI/Item/ItemObject.h"

void UDragItem::SetContent(const UItemObject* Item) const
{
	Icon->SetBrushFromTexture(Item->GetData().Icon);
}
