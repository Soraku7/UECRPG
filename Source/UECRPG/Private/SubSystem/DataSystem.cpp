// Fill out your copyright notice in the Description page of Project Settings.


#include "SubSystem/DataSystem.h"

void UDataSystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	const std::string Path = TCHAR_TO_UTF8(*FPaths::ProjectContentDir());
	if (GlobalTables.load([&](::luban::ByteBuf& buf, const std::string& s)
	{
		return buf.loadFromFile(Path + "Data/LubanGenerated/" + s + ".bytes");
	}))
	{
		UE_LOG(LogTemp, Warning, TEXT("Loading LubanGenerated Data"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Loading LubanGenerated Data failed"));
	}
}
