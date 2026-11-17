// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSetBase.h"
#include "BasicAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, ClassName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(ClassName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(ClassName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(ClassName)

/**
 * 
 */
UCLASS()
class UECRPG_API UBasicAttributeSet : public UAttributeSetBase
{
	GENERATED_BODY()

public:
	UBasicAttributeSet();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attribute", DisplayName = "Health")
	FGameplayAttributeData Health;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attribute", DisplayName = "MaxHealth")
	FGameplayAttributeData MaxHealth;

	ATTRIBUTE_ACCESSORS_BASIC(UBasicAttributeSet, Health)
	ATTRIBUTE_ACCESSORS_BASIC(UBasicAttributeSet, MaxHealth)

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attribute", DisplayName = "Armor")
	FGameplayAttributeData Armor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attribute", DisplayName = "MaxArmor")
	FGameplayAttributeData MaxArmor;

	ATTRIBUTE_ACCESSORS_BASIC(UBasicAttributeSet, Armor)
	ATTRIBUTE_ACCESSORS_BASIC(UBasicAttributeSet, MaxArmor)

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attribute", DisplayName = "AP")
	FGameplayAttributeData AP;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attribute", DisplayName = "MaxAP")
	FGameplayAttributeData MaxAP;

	ATTRIBUTE_ACCESSORS_BASIC(UBasicAttributeSet, AP)
	ATTRIBUTE_ACCESSORS_BASIC(UBasicAttributeSet, MaxAP)

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attribute", DisplayName = "MP")
	FGameplayAttributeData MP;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attribute", DisplayName = "MaxMP")
	FGameplayAttributeData MaxMP;

	ATTRIBUTE_ACCESSORS_BASIC(UBasicAttributeSet, MP)
	ATTRIBUTE_ACCESSORS_BASIC(UBasicAttributeSet, MaxMP)

public:
	virtual void ReadDataFromTable(const luban::SharedPtr<cfg::Character::CharacterTable>& TbCharacterData) override;

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;

	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& EffectData) override;
};
