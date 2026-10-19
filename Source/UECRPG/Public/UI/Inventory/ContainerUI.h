// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/UIBase.h"
#include "ContainerUI.generated.h"

class AItemContainer;
class UButton;
class UWrapBox;
class UInventorySlot;
/**
 * 
 */
UCLASS()
class UECRPG_API UContainerUI : public UUIBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UInventorySlot> UContainerClass;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UWrapBox> ContainerPanel;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> CollectAllBtn;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> CloseBtn;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<AItemContainer> ItemContainer;

	UPROPERTY(EditDefaultsOnly)
	TArray<TObjectPtr<UInventorySlot>> SlotItems;

protected:
	virtual void NativeOnInitialized() override;

	virtual void BindDelegates() override;

	virtual void UnBindDelegates() override;

public:
	UFUNCTION(BlueprintCallable)
	void ShowItems(AItemContainer* Container);

	virtual void DoUnload() override;

	virtual void DoCloseAction() override;

	void RefreshData();
	
protected:
	UFUNCTION()
	void CollectItem(const int32 ItemID , const int32 Num);
	
	UFUNCTION()
	void CollectAll();
	
private:
	void AddSlot();
};
