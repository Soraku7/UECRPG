// Fill out your copyright notice in the Description page of Project Settings.


#include "SubState/NormalState.h"

#include "UECRPGPlayerController.h"

bool UNormalState::IsTriggeringDetect()
{
	return true;
}

void UNormalState::MouseBeginClickAction()
{
	Super::MouseBeginClickAction();
	
}

void UNormalState::MouseTriggeringAction()
{
	Controller->DoInputMove();
}

void UNormalState::MouseEndClickAction()
{
	Controller->DoSimpleMove();
}
