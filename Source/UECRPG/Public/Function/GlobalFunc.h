// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CRPGGameState.h"
#include "UECRPGPlayerController.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "GlobalFunc.generated.h"

class UGameplayStatics;
class ACRPGGameState;
class AUECRPGPlayerController;
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

	static UTexture2D* GetCachedIcon(const FString& IconName)
	{
		static TMap<FString, TWeakObjectPtr<UTexture2D>> CachedIcons;

		if (!CachedIcons.Contains(IconName))
		{
			const auto IconResource = LoadObject<UTexture2D>(nullptr, *IconName);
			if (IsValid(IconResource))
			{
				CachedIcons.Add(IconName, IconResource);
				return IconResource;
			}
			return nullptr;
		}
		return CachedIcons[IconName].Get();
	}

	UFUNCTION(BlueprintCallable, Category = "GlobalFunc")
	static AUECRPGPlayerController* GetPlayerController()
	{
		static TWeakObjectPtr<AUECRPGPlayerController> CachedController;
		if (CachedController.IsValid())
		{
			UE_LOG(LogTemp, Warning, TEXT("has cached %s"), *CachedController->GetClass()->GetName());
			return CachedController.Get();
		}

		if (!GEngine || !GEngine->GameViewport)
			return nullptr;

		const auto World = GEngine->GameViewport->GetWorld();

		if (!IsValid(World))
			return nullptr;

		const auto PlayerController = Cast<AUECRPGPlayerController>(World->GetFirstPlayerController());
		CachedController = PlayerController;
		return PlayerController;
	}

	static ACRPGGameState* GetGameState()
	{
		static TWeakObjectPtr<ACRPGGameState> CachedGameState;

		if (CachedGameState.IsValid())
		{
			return CachedGameState.Get();
		}

		if (!GEngine || !GEngine->GameViewport)
			return nullptr;

		const auto World = GEngine->GameViewport->GetWorld();
		if (!IsValid(World))
			return nullptr;

		const auto GameState = Cast<ACRPGGameState>(UGameplayStatics::GetGameState(World));
		CachedGameState = GameState;
		return GameState;
	}

	UFUNCTION(BlueprintCallable, Category = "GlobalFunc")
	static void SetGameStateType(const EGameStateType Type)
	{
		if (const auto GameState = GetGameState() ; IsValid(GameState))
		{
			GameState->SetGameStateType(Type);
		}
	}
	
	static EGameStateType GetGameStateType(EGameStateType& Type)
	{
		if (const auto GameState = GetGameState() ; IsValid(GameState))
		{
			return GameState->GetGameStateType();
		}
		return EGameStateType::Normal;
	}
};
