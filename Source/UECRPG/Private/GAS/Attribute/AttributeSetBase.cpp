// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Attribute/AttributeSetBase.h"

#include "Character/CharacterBase.h"
#include "Function/GlobalFunc.h"
#include "GameFramework/Character.h"
#include "SubSystem/DataSystem.h"

void UAttributeSetBase::DoInitialize()
{
	Owner = Cast<ACharacterBase>(GetOwningActor());

	const auto TbCharacterData = UGlobalFunc::GetSubsystem<UDataSystem>()->GetTbCharacterData(Owner->GetCharacterID());
	if (TbCharacterData != nullptr)
	{
		ReadDataFromTable(TbCharacterData);
	}
}

void UAttributeSetBase::ReadDataFromTable(const luban::SharedPtr<cfg::Character::CharacterTable>& TbCharacterData)
{
}
