// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SubStateBase.h"
#include "NormalState.generated.h"

/**
 * 
 */
UCLASS()
class UECRPG_API UNormalState : public USubStateBase
{

	GENERATED_BODY()
	
public:
	virtual bool IsTriggeringDetect() override;
	virtual void MouseBeginClickAction() override;
	virtual void MouseTriggeringAction() override;
	virtual void MouseEndClickAction() override;

};
