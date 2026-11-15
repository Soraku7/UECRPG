// Fill out your copyright notice in the Description page of Project Settings.


#include "SubState/SquadSystem.h"

#include "Character/CharacterBase.h"
#include "Function/GlobalFunc.h"

void USquadSystem::LoadPlayer()
{
	const auto StartPoint = UGlobalFunc::GetGameMode()->FindPlayerStart(UGlobalFunc::GetPlayerController());
	const auto Player = UGlobalFunc::SpawnBPActor<ACharacterBase>(
		TEXT("Blueprints/Character"), TEXT("BP_Player"),
		FTransform(StartPoint->GetActorTransform()));
	UGlobalFunc::GetPlayerController()->SetCurCharacter(Player);
}
