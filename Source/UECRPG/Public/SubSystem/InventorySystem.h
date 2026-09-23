// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "InventorySystem.generated.h"

struct FItemData;
class UItemObject;
enum class EItemType : uint8;

USTRUCT()
struct FTypeItemHolder
{
	GENERATED_BODY()
	TArray<TObjectPtr<UItemObject>> ItemArray;

	FTypeItemHolder();
};

/**
 * 
 */
UCLASS()
class UECRPG_API UInventorySystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	TMap<EItemType, FTypeItemHolder> Inventory;

	UPROPERTY()
	TObjectPtr<UDataTable> ItemDataTable;

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	TArray<UItemObject*> GetAllItems();
	
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	UItemObject* AddItem(const int32 ItemID , const int32 Num = 1 , const bool bAutoBroadCast = true);
	
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	UItemObject* ReduceItem(const int32 ItemID , const int32 Num = 1, const bool bAutoBroadCast = true);
	
	FItemData* GetItemData(const int32 ItemID) const;
	
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	UItemObject* GetItem(const int32 ItemID) const;
	
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	int32 GetItemNum(const int32 ItemID) const;
	
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	UItemObject* CreateItem(const int32 ItemID);
};
