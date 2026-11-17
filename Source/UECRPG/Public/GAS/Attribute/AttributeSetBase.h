// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "Luban/Generated/schema.h"
#include "AttributeSetBase.generated.h"

class ACharacterBase;
/**
 * 
 */
UCLASS()
class UECRPG_API UAttributeSetBase : public UAttributeSet
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	TObjectPtr<ACharacterBase> Owner;

public:
	virtual void DoInitialize();

	virtual void ReadDataFromTable(const luban::SharedPtr<cfg::Character::CharacterTable>& TbCharacterData);
};
