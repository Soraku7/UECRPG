// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UIBase.h"
#include "GameUI.generated.h"

class UDropArea;
class UButton;
/**
 * 
 */
UCLASS()
class UECRPG_API UGameUI : public UUIBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> InventoryButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UDropArea> DropArea;

protected:
	virtual void NativeOnInitialized() override;

	virtual void BindDelegates() override;

	virtual void UnBindDelegates() override;

	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
	                          UDragDropOperation* InOperation) override;

protected:
	UFUNCTION()
	void ToggleInventory();

	UFUNCTION()
	void OnItemDrop(const bool bIsDragging);
};
