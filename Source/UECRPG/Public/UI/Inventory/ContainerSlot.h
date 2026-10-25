// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventorySlot.h"
#include "ContainerSlot.generated.h"

/**
 * 
 */
UCLASS()
class UECRPG_API UContainerSlot : public UInventorySlot
{
	GENERATED_BODY()

public:
	virtual void DoAutoAction() override;

	virtual void DoAcquire() override;

	virtual void DoStore() override;

	virtual void DoDiscard() override;
};
