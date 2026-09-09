// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "UIBase.generated.h"

/**
 * 
 */
UCLASS()
class UECRPG_API UUIBase : public UUserWidget
{
	GENERATED_BODY()

protected:
	bool bIsShow;

	FTimerDelegate CloseTimerDelegate;

	FTimerHandle CloseTimerHandle;

public:
	bool bIsClose;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Config", DisplayName = "Sort")
	int32 ZOrder = 0;

protected:
	virtual void NativeOnInitialized() override;

	virtual void BindDelegates();

	virtual void UnBindDelegates();

public:
	virtual void DoLoad();

	virtual void DoUnLoad();

	virtual void DoClose(const float CloseTime = 5.f);
	
	virtual void CloseEvent();
	
	UFUNCTION()
	virtual void DoCloseAction();
};
