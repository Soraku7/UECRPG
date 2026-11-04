// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/GlobalEnum.h"
#include "GameFramework/GameStateBase.h"
#include "CRPGGameState.generated.h"

class USubStateBase;
/**
 * 
 */
UCLASS()
class UECRPG_API ACRPGGameState : public AGameStateBase
{
protected:
	virtual void BeginPlay() override;

private:
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	EGameStateType CurGameStateType = EGameStateType::Normal;

	UPROPERTY()
	TObjectPtr<USubStateBase> CurSubState;

protected:
	void SetGameStateType(const EGameStateType Type);

	FORCEINLINE EGameStateType GetGameStateType() const { return CurGameStateType; }

	FORCEINLINE USubStateBase* GetSubState() const { return CurSubState; }
};
