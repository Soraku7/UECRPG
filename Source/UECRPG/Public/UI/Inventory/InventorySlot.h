// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "InventorySlot.generated.h"

class UDragItem;
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
protected:
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	virtual FReply
	NativeOnMouseButtonDoubleClick(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent,
	                                  UDragDropOperation*& OutOperation) override;

	UFUNCTION()
	void HandleOnDragCancelled(UDragDropOperation* Operation);

private:
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UDragItem> UDragItemClass;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UImage> Icon;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> NumText;

	TObjectPtr<UItemObject> Item;

	TObjectPtr<UUIBase> ParentUI;

	int32 ItemNum;

public:
	virtual void RefreshData(UItemObject* InItem, const int32 ShowNum = 1);

	virtual void DoAutoAction();

	virtual void DoAcquire();

	virtual void DoStore();

	virtual void DoDiscard();

	void SetIconDragStatus(const bool bIsDrag) const;

	FORCEINLINE UItemObject* GetItemNum() { return Item; }

	FORCEINLINE void SetParent(UUIBase* InParentUI) { ParentUI = InParentUI; }

	FORCEINLINE UUIBase* GetParentUI() { return ParentUI; }
};
