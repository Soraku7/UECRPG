// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "SubStateBase.generated.h"

class AUECRPGPlayerController;
/**
 * 
 */
UCLASS()
class UECRPG_API USubStateBase : public UObject
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	TObjectPtr<AUECRPGPlayerController> Controller;

public:
	virtual void StateInit(AUECRPGPlayerController* ControllerRef);

	virtual void StateEnd();

	virtual bool IsTriggeringDetect();

	virtual void MouseBeginClickAction();

	virtual void MouseEndClickAction();

	virtual void MouseCancelClickActon();
};
