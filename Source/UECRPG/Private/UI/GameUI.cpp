// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/UI/GameUI.h"

#include "Public/Function/GlobalFunc.h"
#include "Public/SubSystem/UISystem.h"
#include "Public/UI/Inventory/InventoryUI.h"
#include "Runtime/UMG/Public/Components/Button.h"
#include "SubSystem/InventorySystem.h"
#include "UI/Inventory/DropArea.h"
#include "UI/Inventory/ItemDragDropOperation.h"

void UGameUI::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	DropArea->SetParent(this);
	DropArea->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
}

void UGameUI::BindDelegates()
{
	Super::BindDelegates();

	InventoryButton->OnClicked.AddDynamic(this, &UGameUI::ToggleInventory);
	UGlobalFunc::GetSubsystem<UInventorySystem>()->OnDragDelegate.AddUObject(this, &UGameUI::OnItemDrop);
}

void UGameUI::UnBindDelegates()
{
	Super::UnBindDelegates();
	InventoryButton->OnClicked.Clear();
	UGlobalFunc::GetSubsystem<UInventorySystem>()->OnDragDelegate.Clear();
}

void UGameUI::ToggleInventory()
{
	UGlobalFunc::GetSubsystem<UUISystem>()->ToggleUI<UInventoryUI>();
}

void UGameUI::OnItemDrop(const bool bIsDragging)
{
	if (bIsDragging)
	{
		DropArea->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		DropArea->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}
}

bool UGameUI::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
                           UDragDropOperation* InOperation)
{
	const auto DragDropOperation = Cast<UItemDragDropOperation>(InOperation);
	if (IsValid(DragDropOperation))
	{
		if (DropArea->GetCachedGeometry().IsUnderLocation(InDragDropEvent.GetScreenSpacePosition()))
		{
			DropArea->HandleOnDrop(DragDropOperation->InventoryItem);
			return true;
		}
	}
	return false;
}
