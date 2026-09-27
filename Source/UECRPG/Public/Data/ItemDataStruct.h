#pragma once

#include "CoreMinimal.h"
#include "GlobalEnum.h"
#include "ItemDataStruct.generated.h"

USTRUCT(BlueprintType)
struct FItemData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item", DisplayName = "Name")
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item", DisplayName = "Description")
	FString Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item", DisplayName = "Icon")
	TObjectPtr<UTexture2D> Icon;

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
	int maxStack;

	FItemData() : Name(""), Description(""), Icon(nullptr), ItemType(EItemType::All), ItemQuality(EItemQuality::Poor),
	              Weight(0), BuyPrice(0), SellPrice(0), bIsStackable(false), maxStack(0)
	{
	}
	
	static FItemData Set(const FItemData& InItemData)
	{
		FItemData Item;
		Item.Name = InItemData.Name;
		Item.Description = InItemData.Description;
		Item.Icon = InItemData.Icon;
		Item.ItemType = InItemData.ItemType;
		Item.ItemQuality = InItemData.ItemQuality;
		Item.Weight = InItemData.Weight;
		Item.BuyPrice = InItemData.BuyPrice;
		Item.SellPrice = InItemData.SellPrice;
		Item.bIsStackable = InItemData.bIsStackable;
		Item.maxStack = InItemData.maxStack;
		return Item;
	}
};
