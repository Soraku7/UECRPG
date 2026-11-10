// Copyright Epic Games, Inc. All Rights Reserved.

#include "UECRPGGameMode.h"

#include "Public/Function/GlobalFunc.h"
#include "Public/SubSystem/UISystem.h"
#include "Public/UI/GameUI.h"
#include "SubState/SquadSystem.h"

AUECRPGGameMode::AUECRPGGameMode()
{
	// stub
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/BP_Camera"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void AUECRPGGameMode::BeginPlay()
{
	Super::BeginPlay();

	UGlobalFunc::GetSubsystem<UUISystem>()->LoadUI<UGameUI>();
	UGlobalFunc::GetSubsystem<USquadSystem>()->LoadPlayer();
}
