// Copyright Epic Games, Inc. All Rights Reserved.

#include "UECRPGGameMode.h"

#include "Public/SubSystem/UISystem.h"
#include "Public/UI/GameUI.h"

AUECRPGGameMode::AUECRPGGameMode()
{
	// stub
}

void AUECRPGGameMode::BeginPlay()
{
	Super::BeginPlay();

	GEngine->GameViewport->GetWorld()->GetGameInstance()->GetSubsystem<UUISystem>()->LoadUI<UGameUI>();
}
