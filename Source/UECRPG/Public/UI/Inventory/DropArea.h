// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "DropArea.generated.h"

class UInventorySlot;
class UUIBase;
/**
 * 
 */
UCLASS()
class UECRPG_API UDropArea : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	TObjectPtr<UUIBase> ParentUI;

public:
	void HandleOnDrop(UInventorySlot* DropItem) const;

	FORCEINLINE void SetParent(UUIBase* InParentUI) { ParentUI = InParentUI; }
};
