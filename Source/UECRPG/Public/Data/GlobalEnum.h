#pragma once

#include "CoreMinimal.h"
#include "GlobalEnum.generated.h"

UENUM()
enum class EItemType : uint8
{
	All = 0 UMETA(DisplayName = "All"),
	Consumable = 1 UMETA(DisplayName = "Consumable"),
	Weapon = 2 UMETA(DisplayName = "Weapon"),
	Prop = 3 UMETA(DisplayName = "Prop"),
	Collectable = 4 UMETA(DisplayName = "Collectable"),
	Quest = 5 UMETA(DisplayName = "Quest"),
	Mundane = 6 UMETA(DisplayName = "Mundane"),
};

ENUM_RANGE_BY_FIRST_AND_LAST(EItemType, EItemType::All, EItemType::Mundane)

UENUM()
enum class EItemQuality : uint8
{
	Poor = 0 UMETA(DisplayName = "Poor"),
	Common = 1 UMETA(DisplayName = "Common"),
	Good = 2 UMETA(DisplayName = "Good"),
	Epic = 3 UMETA(DisplayName = "Epic"),
	Legendary = 4 UMETA(DisplayName = "Legendary"),
};
