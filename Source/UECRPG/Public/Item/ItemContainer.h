// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemContainer.generated.h"

class UItemObject;
struct FItemPack;

UCLASS()
class UECRPG_API AItemContainer : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AItemContainer();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<USceneComponent> Root;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<UStaticMeshComponent> Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, CateGory = "Config", DisplayName = "ItemPacks")
	TArray<FItemPack> ItemPacks;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, CateGory = "Config", DisplayName = "ItemObjects")
	TArray<TObjectPtr<UItemObject>> ContainedItems;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable)
	FORCEINLINE TArray<UItemObject*> GetContainedItems() const { return ContainedItems; }

	void AddItem(const int32 ItemID, const int32 Num);

	void RemoveALl();
};
