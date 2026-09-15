// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GlobalFunc.generated.h"

/**
 * 
 */
UCLASS()
class UECRPG_API UGlobalFunc : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	template <typename TargetClass = UGameInstanceSubsystem>
	static TargetClass* GetSubsystem()
	{
		static TWeakObjectPtr<TargetClass> CachedSubSystem;

		if (CachedSubSystem.IsValid())
		{
			UE_LOG(LogTemp, Warning, TEXT("此SubSystem由缓存%s"), *CachedSubSystem->GetClass()->GetName());
			return CachedSubSystem.Get();
		}

		if (!GEngine || !GEngine->GameViewport)
		{
			return nullptr;
		}

		const auto World = GEngine->GameViewport->GetWorld();
		if (!IsValid(World))
		{
			return nullptr;
		}

		const auto GameInstance = World->GetGameInstance();
		if (!IsValid(GameInstance))
		{
			return nullptr;
		}

		TargetClass* Subsystem = GameInstance->GetSubsystem<TargetClass>();
		CachedSubSystem = Subsystem;
		return Subsystem;
	}
};
