// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemTypeToggle.h"
#include "Public/UI/UIBase.h"
#include "InventoryUI.generated.h"

class UDropArea;
class UUniversalToggle;
class UItemTypeToggle;
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

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UItemTypeToggle> UItemTypeToggleClass;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UWrapBox> InventoryPanel;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UWrapBox> ItemTypePanel;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButton> CloseBtn;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UDropArea> DropArea;

	UPROPERTY()
	TArray<TObjectPtr<UInventorySlot>> SlotItems;

	UPROPERTY()
	TMap<EItemType, TObjectPtr<UItemTypeToggle>> ItemTypeMap;

	EItemType CurType;

protected:
	virtual void NativeOnInitialized() override;

	virtual void BindDelegates() override;

	virtual void UnBindDelegates() override;

	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
		UDragDropOperation* InOperation) override;

public:
	virtual void DoLoad() override;

	virtual void DoUnload() override;

	void RefreshData();

protected:
	UFUNCTION()
	virtual void OnRefreshInventory(const int32 ItemID);

	void OnToggleSelected(const UUniversalToggle* SelectToggle);

	UFUNCTION()
	virtual void AddSlot();
};
