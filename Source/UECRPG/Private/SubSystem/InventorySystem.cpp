// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/SubSystem/InventorySystem.h"

void UInventorySystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	ItemDataTable = LoadObject<UDataTable>(nullptr, TEXT("/Game/Data/ItemDataTable"));

	if (IsValid(ItemDataTable))
	{
		UE_LOG(LogTemp, Warning, TEXT("ItemDataTable is valid"));
	}
}
