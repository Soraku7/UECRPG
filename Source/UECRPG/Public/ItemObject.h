// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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
	
public:
	int32 Num;
	
	UFUNCTION(BlueprintCallable , Category = "Inventory")
	FORCEINLINE int32 GetItemID() const { return ID; }
	
	bool operator==(const UItemObject& Other) const { return ID == Other.ID; }
};
