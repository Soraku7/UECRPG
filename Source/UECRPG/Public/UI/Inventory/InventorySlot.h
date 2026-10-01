// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "InventorySlot.generated.h"

class UUIBase;
class UItemObject;
class UTextBlock;
class UImage;
/**
 * 
 */
UCLASS()
class UECRPG_API UInventorySlot : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UImage> Icon;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> NumText;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UItemObject> Item;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UUIBase> ParentUI;

	int32 ItemNum;

public:
	virtual void RefreshData(UItemObject* InItem, const int32 ShowNum = 1);

	FORCEINLINE UItemObject* GetItemNum() { return Item; }

	FORCEINLINE void SetParent(UUIBase* InParentUI) { ParentUI = InParentUI; }

	FORCEINLINE UUIBase* GetParent() { return ParentUI; }
};
