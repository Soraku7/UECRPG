// Fill out your copyright notice in the Description page of Project Settings.


#include "SubState/SubStateBase.h"

void USubStateBase::StateInit(AUECRPGPlayerController* ControllerRef)
{
	Controller = ControllerRef;

	FInputModeGameAndUI InputMode;
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputMode.SetHideCursorDuringCapture(false);
	GetWorld()->GetFirstPlayerController()->SetInputMode(InputMode);
}

bool USubStateBase::IsTriggeringDetect()
{
	return false;
}
