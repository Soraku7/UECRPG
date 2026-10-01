// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Public/UI/UIBase.h"
#include "InventoryUI.generated.h"

enum class EItemType : uint8;
class UButton;
class UWrapBox;
class UInventorySlot;
/**
 * 
 */
UCLASS()
class UECRPG_API UInventoryUI : public UUIBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UInventorySlot> UInventorySlotClass;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UWrapBox> InventoryPanel;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButton> CloseBtn;

	UPROPERTY()
	TArray<TObjectPtr<UInventorySlot>> SlotItems;

	EItemType CurType;

protected:
	virtual void NativeOnInitialized() override;

	virtual void BindDelegates() override;

	virtual void UnBindDelegates() override;

public:
	virtual void DoLoad() override;

	virtual void DoUnload() override;

	void RefreshData();

protected:
	UFUNCTION()
	virtual void OnRefreshInventory(const int32 ItemID);

	UFUNCTION()
	virtual void AddSlot();
};
