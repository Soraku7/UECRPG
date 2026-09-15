// Copyright Epic Games, Inc. All Rights Reserved.

#include "UECRPGGameMode.h"

#include "Public/Function/GlobalFunc.h"
#include "Public/SubSystem/UISystem.h"
#include "Public/UI/GameUI.h"

AUECRPGGameMode::AUECRPGGameMode()
{
	// stub
}

void AUECRPGGameMode::BeginPlay()
{
	Super::BeginPlay();

	UGlobalFunc::GetSubsystem<UUISystem>()->LoadUI<UGameUI>();
}
