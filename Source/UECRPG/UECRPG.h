// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

/** Main log category used across the project */
DECLARE_LOG_CATEGORY_EXTERN(LogUECRPG, Log, All);

inline FString ItemTypeName[] = {
	TEXT("All"), TEXT("Consumable"), TEXT("Weapon"), TEXT("Prop"), TEXT("Collectable"), TEXT("Quest"), TEXT("Mundane")
};
