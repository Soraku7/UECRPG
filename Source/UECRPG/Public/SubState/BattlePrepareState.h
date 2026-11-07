// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SubStateBase.h"
#include "BattlePrepareState.generated.h"

/**
 * 
 */
UCLASS()
class UECRPG_API UBattlePrepareState : public USubStateBase
{
	GENERATED_BODY()

public:
	virtual void StateInit(AUECRPGPlayerController* ControllerRef) override;

	virtual void StateEnd() override;
};
