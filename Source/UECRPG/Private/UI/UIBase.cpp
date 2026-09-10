// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/UI/UIBase.h"

#include "Public/SubSystem/UISystem.h"

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
	bIsShow = true;
	bIsClose = false;
	SetVisibility(ESlateVisibility::SelfHitTestInvisible);

	if (CloseTimerHandle.IsValid())
	{
		GetWorld()->GetTimerManager().ClearTimer(CloseTimerHandle);
		CloseTimerDelegate.Unbind();
		CloseTimerDelegate = nullptr;
	}
}

void UUIBase::DoUnLoad()
{
	bIsShow = false;
}

void UUIBase::DoClose(const float CloseTime)
{
	DoUnLoad();
	bIsClose = true;
	SetVisibility(ESlateVisibility::Collapsed);
	CloseTimerDelegate.BindUObject(this, &UUIBase::CloseEvent);
	GetWorld()->GetTimerManager().SetTimer(CloseTimerHandle, CloseTimerDelegate, CloseTime, false);
}

void UUIBase::CloseEvent()
{
	UnBindDelegates();
	GEngine->GameViewport->GetWorld()->GetGameInstance()->GetSubsystem<UUISystem>()->RemoveFromList(this);
	RemoveFromParent();
}

void UUIBase::DoCloseAction()
{
	DoClose();
}
