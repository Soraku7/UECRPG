// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UIBase.h"
#include "GameUI.generated.h"

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

protected:
	virtual void NativeOnInitialized() override;

	virtual void BindDelegates() override;

	virtual void UnBindDelegates() override;

protected:
	UFUNCTION()
	void ToggleInventory();
};
