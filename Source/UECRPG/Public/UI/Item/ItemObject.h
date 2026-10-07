// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/ItemDataStruct.h"
#include "UObject/Object.h"
#include "ItemObject.generated.h"

/**
 * 
 */
UCLASS()
class UECRPG_API UItemObject : public UObject
{
	GENERATED_BODY()

protected:
	int32 ID;
	
	FItemData Data;
	
public:
	int32 Num;
	
	virtual void Initialized(const int32 ItemID , const FItemData& InItemData);
	
	UFUNCTION(BlueprintCallable , Category = "Inventory")
	FORCEINLINE int32 GetItemID() const { return ID; }
	
	UFUNCTION(BlueprintCallable , Category = "Inventory")
	FORCEINLINE FItemData GetData() const { return Data; }
	
	bool operator==(const UItemObject& Other) const { return ID == Other.ID; }
};
