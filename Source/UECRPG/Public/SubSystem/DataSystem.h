// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Luban/Generated/schema.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "DataSystem.generated.h"


/**
 * 
 */
UCLASS()
class UECRPG_API UDataSystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

protected:
	cfg::Tables GlobalTables;

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	FORCEINLINE cfg::Tables GetGlobalTables() const { return GlobalTables; }

	FORCEINLINE luban::SharedPtr<cfg::item::Item> GetGlobalTable(const int32 ItemID)
	{
		return GlobalTables.TbItem.get(ItemID);
	}
};
