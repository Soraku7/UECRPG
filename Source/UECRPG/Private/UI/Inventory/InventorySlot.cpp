// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/UI/Inventory/InventorySlot.h"


#include "Function/GlobalFunc.h"
#include "Runtime/UMG/Public/Components/Image.h"
#include "Runtime/UMG/Public/Components/TextBlock.h"
#include "SubSystem/InventorySystem.h"
#include "UI/Inventory/DragItem.h"
#include "UI/Inventory/ItemDragDropOperation.h"
#include "UI/Item/ItemObject.h"

FReply UInventorySlot::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply Reply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
	{
		if (IsValid(Item))
		{
			return Reply.Handled().DetectDrag(TakeWidget(), EKeys::LeftMouseButton);
		}
	}

	return Reply.Unhandled();
}

FReply UInventorySlot::NativeOnMouseButtonDoubleClick(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply Reply = Super::NativeOnMouseButtonDoubleClick(InGeometry, InMouseEvent);
	if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
	{
		if (IsValid(Item))
		{
			DoAutoAction();
			return Reply.Handled();
		}
	}

	return Reply.Unhandled();
}

void UInventorySlot::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent,
                                          UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

	const auto DragItem = CreateWidget<UDragItem>(this, UDragItemClass);
	DragItem->SetContent(Item);

	const auto DragOperation = NewObject<UItemDragDropOperation>(this);
	DragOperation->InventoryItem = this;
	DragOperation->DefaultDragVisual = DragItem;
	DragOperation->Pivot = EDragPivot::TopLeft;
	DragOperation->OnDragCancelled.AddDynamic(this, &UInventorySlot::HandleOnDragCancelled);
	OutOperation = DragOperation;

	SetIconDragStatus(true);
	UGlobalFunc::GetSubsystem<UInventorySystem>()->BroadcastOnDragStatus(true);
}

void UInventorySlot::HandleOnDragCancelled(UDragDropOperation* Operation)
{
	Operation->OnDragCancelled.Clear();
	SetIconDragStatus(false);
	UGlobalFunc::GetSubsystem<UInventorySystem>()->BroadcastOnDragStatus(false);
}

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

		SetIconDragStatus(false);
	}
	else
	{
		Icon->SetVisibility(ESlateVisibility::Collapsed);
		NumText->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UInventorySlot::DoAutoAction()
{
}

void UInventorySlot::DoAcquire()
{
}

void UInventorySlot::DoStore()
{
	UGlobalFunc::GetSubsystem<UInventorySystem>()->CollectItem(Item->GetItemID(), -ItemNum);
}

void UInventorySlot::DoDiscard()
{
	UGlobalFunc::GetSubsystem<UInventorySystem>()->ReduceItem(Item->GetItemID(), ItemNum);
}

void UInventorySlot::SetIconDragStatus(const bool bIsDrag) const
{
	if (bIsDrag)
	{
		Icon->SetBrushTintColor(FLinearColor::Gray);
	}
	else
	{
		Icon->SetBrushTintColor(FLinearColor::White);
	}
}
