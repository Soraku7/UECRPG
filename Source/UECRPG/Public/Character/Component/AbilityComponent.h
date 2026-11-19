// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "Interfaces/UnitComponentInterface.h"
#include "AbilityComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UECRPG_API UAbilityComponent : public UAbilitySystemComponent, public IUnitComponentInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UAbilityComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

protected:
	TObjectPtr<ACharacterBase> Owner;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	virtual void DoInitialize() override;

	virtual void DoReset() override;

	virtual void DoDispose() override;

	virtual ACharacterBase* GetCompOwner() const override;
};
