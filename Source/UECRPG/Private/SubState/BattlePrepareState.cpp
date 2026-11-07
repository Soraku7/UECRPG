// Fill out your copyright notice in the Description page of Project Settings.


#include "SubState/BattlePrepareState.h"

#include "Function/GlobalFunc.h"
#include "SubSystem/UISystem.h"
#include "UI/GameUI.h"

void UBattlePrepareState::StateInit(AUECRPGPlayerController* ControllerRef)
{
	Super::StateInit(ControllerRef);

	UGlobalFunc::GetSubsystem<UUISystem>()->GetUI<UGameUI>()->ShowStartButton(true);
}

void UBattlePrepareState::StateEnd()
{
	Super::StateEnd();

	UGlobalFunc::GetSubsystem<UUISystem>()->GetUI<UGameUI>()->ShowStartButton(false);
}
