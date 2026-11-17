// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Attribute/BasicAttributeSet.h"

UBasicAttributeSet::UBasicAttributeSet()
{
	InitHealth(0);
	InitMaxHealth(0);
	InitArmor(0);
	InitMaxArmor(0);
	InitAP(0);
	InitMaxAP(0);
	InitMP(0);
	InitMaxMP(0);
}

void UBasicAttributeSet::ReadDataFromTable(const luban::SharedPtr<cfg::Character::CharacterTable>& TbCharacterData)
{
	SetMaxHealth(GetMaxHealth() + TbCharacterData->initAttrBasic->hp);
	SetHealth(GetHealth() + TbCharacterData->initAttrBasic->hp);

	SetMaxArmor(GetMaxArmor() + TbCharacterData->initAttrBasic->arp);
	SetArmor(GetArmor() + TbCharacterData->initAttrBasic->arp);

	SetMaxAP(GetMaxAP() + TbCharacterData->initAttrBasic->ap);
	SetAP(GetAP() + TbCharacterData->initAttrBasic->ap);

	SetMaxMP(GetMaxMP() + TbCharacterData->initAttrBasic->mp);
	SetMP(GetMP() + TbCharacterData->initAttrBasic->mp);
}

void UBasicAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxHealth());
	}
	else if (Attribute == GetArmorAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxArmor());
	}
	else if (Attribute == GetAPAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxAP());
	}
	else if (Attribute == GetMPAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxMP());
	}
}

void UBasicAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
	Super::PostAttributeChange(Attribute, OldValue, NewValue);
}

void UBasicAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& EffectData)
{
	Super::PostGameplayEffectExecute(EffectData);
}
