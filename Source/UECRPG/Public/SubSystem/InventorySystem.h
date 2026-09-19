// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "InventorySystem.generated.h"

/**
 * 
 */
UCLASS()
class UECRPG_API UInventorySystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

protected:

	UPROPERTY()
	TObjectPtr<UDataTable> ItemDataTable;
	
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
};
