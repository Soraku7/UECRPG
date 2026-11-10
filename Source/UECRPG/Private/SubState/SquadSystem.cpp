// Fill out your copyright notice in the Description page of Project Settings.


#include "SubState/SquadSystem.h"

#include "UECRPGCharacter.h"
#include "Function/GlobalFunc.h"

void USquadSystem::LoadPlayer()
{
	const auto StartPoint = UGlobalFunc::GetGameMode()->FindPlayerStart(UGlobalFunc::GetPlayerController());
	const auto Player = UGlobalFunc::SpawnBPActor<AUECRPGCharacter>(
		TEXT("TopDown/Blueprints"), TEXT("BP_TopDownCharacter"),
		FTransform(StartPoint->GetActorTransform()));
	UGlobalFunc::GetPlayerController()->SetCurCharacter(Player);
}
