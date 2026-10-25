// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/UMG/Public/Blueprint/DragDropOperation.h"
#include "ItemDragDropOperation.generated.h"

class UInventorySlot;
/**
 * 
 */
UCLASS()
class UECRPG_API UItemDragDropOperation : public UDragDropOperation
{
	GENERATED_BODY()

public:
	TObjectPtr<UInventorySlot> InventoryItem;
};
