// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/UI/UIBase.h"

#include "Public/Function/GlobalFunc.h"
#include "Public/SubSystem/UISystem.h"
#include "Public/UI/GameUI.h"

void UUIBase::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	BindDelegates();
}

void UUIBase::BindDelegates()
{
}

void UUIBase::UnBindDelegates()
{
}

void UUIBase::DoLoad()
{
	bIsClose = false;
	SetVisibility(ESlateVisibility::SelfHitTestInvisible);

	if (CloseTimerHandle.IsValid())
	{
		GetWorld()->GetTimerManager().ClearTimer(CloseTimerHandle);
		CloseTimerDelegate.Unbind();
		CloseTimerDelegate = nullptr;
	}
}

void UUIBase::DoUnload()
{
}

void UUIBase::DoClose(const float CloseTime)
{
	DoUnload();
	bIsClose = true;
	SetVisibility(ESlateVisibility::Collapsed);
	CloseTimerDelegate.BindUObject(this, &UUIBase::CloseEvent);
	GetWorld()->GetTimerManager().SetTimer(CloseTimerHandle, CloseTimerDelegate, CloseTime, false);
}

void UUIBase::CloseEvent()
{
	UnBindDelegates();
	UGlobalFunc::GetSubsystem<UUISystem>()->RemoveFromList(this);
	RemoveFromParent();
}

void UUIBase::DoCloseAction()
{
	DoClose();
}
