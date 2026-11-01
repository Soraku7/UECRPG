#pragma once

#include "CoreMinimal.h"
#include "GlobalEnum.h"
#include "Luban/Generated/schema.h"
#include "ItemDataStruct.generated.h"

USTRUCT(BlueprintType)
struct FItemData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item", DisplayName = "Type")
	EItemType ItemType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item", DisplayName = "Quality")
	EItemQuality ItemQuality;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item", DisplayName = "Weight")
	float Weight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item", DisplayName = "Buy Price")
	float BuyPrice;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item", DisplayName = "Sell Price")
	float SellPrice;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item", DisplayName = "Stackable")
	bool bIsStackable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item", DisplayName = "Max Stack")
	int MaxStack;

	FItemData() : ItemType(EItemType::All), ItemQuality(EItemQuality::Poor),
	              Weight(0), BuyPrice(0), SellPrice(0), bIsStackable(false), MaxStack(0)
	{
	}

	explicit FItemData(const luban::SharedPtr<cfg::Item::ItemData>& TableData) :
		ItemType(static_cast<EItemType>(TableData->type)),
		ItemQuality(static_cast<EItemQuality>(TableData->quality)),
		Weight(TableData->weight), BuyPrice(TableData->buy), SellPrice(TableData->sell),
		bIsStackable(TableData->stackable),
		MaxStack(TableData->maxStack)
	{
	}

	static FItemData Set(const FItemData& InItemData)
	{
		FItemData Item;
		Item.ItemType = InItemData.ItemType;
		Item.ItemQuality = InItemData.ItemQuality;
		Item.Weight = InItemData.Weight;
		Item.BuyPrice = InItemData.BuyPrice;
		Item.SellPrice = InItemData.SellPrice;
		Item.bIsStackable = InItemData.bIsStackable;
		Item.MaxStack = InItemData.MaxStack;
		return Item;
	}
};

USTRUCT(BlueprintType)
struct FItemPack
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemPack", DisplayName = "ID")
	int32 ItemID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemPack", DisplayName = "Num")
	int32 Num;

	FItemPack() : ItemID(0), Num(0)
	{
	}
};
