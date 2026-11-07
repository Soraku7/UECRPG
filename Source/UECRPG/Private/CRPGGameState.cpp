// Fill out your copyright notice in the Description page of Project Settings.


#include "CRPGGameState.h"

#include "Function/GlobalFunc.h"
#include "SubState/BattlePrepareState.h"
#include "SubState/NormalState.h"

void ACRPGGameState::BeginPlay()
{
	Super::BeginPlay();
	SetGameStateType(EGameStateType::Normal);
}

void ACRPGGameState::SetGameStateType(const EGameStateType Type)
{
	if (CurSubState != nullptr)
	{
		CurSubState->StateEnd();
	}

	CurGameStateType = Type;
	switch (CurGameStateType)
	{
	case EGameStateType::Normal:
	case EGameStateType::Scenario:
	case EGameStateType::PlayerBattle:
	case EGameStateType::AIBattle:
	case EGameStateType::BattleEnd:
		CurSubState = NewObject<UNormalState>(this);
		break;
	case EGameStateType::BattlePrePare:
		CurSubState = NewObject<UBattlePrepareState>(this);
		break;
	}

	CurSubState->StateInit(UGlobalFunc::GetPlayerController());
}
