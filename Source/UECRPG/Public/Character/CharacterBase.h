// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/CharacterDataStruct.h"
#include "Data/GlobalEnum.h"
#include "GameFramework/Character.h"
#include "CharacterBase.generated.h"

class UAttributeHandleComponent;
enum class EFactionType : uint8;

UCLASS()
class UECRPG_API ACharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacterBase();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", DisplayName = "Character ID")
	FString CharacterID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", DisplayName = "Character Faction")
	EFactionType Faction = EFactionType::NPC;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", DisplayName = "Character InfoData")
	FCharacterInfoData CharacterInfoData;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UAttributeHandleComponent> CharacterHandleComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void InitializeData();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
