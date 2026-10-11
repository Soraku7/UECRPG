// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Universal/UniversalToggle.h"

#include <wrl/event.h>

#include "Runtime/UMG/Public/Components/Button.h"
#include "Runtime/UMG/Public/Components/TextBlock.h"

void UUniversalToggle::NativePreConstruct()
{
	Super::NativePreConstruct();
	if (!TextContent.IsEmpty())
	{
		BtnText->SetText(TextContent);
	}
}

void UUniversalToggle::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	Btn->OnClicked.AddDynamic(this, &UUniversalToggle::OnClickAction);
}

void UUniversalToggle::OnInitCallback(const std::function<void(UUniversalToggle*)>& InCallback)
{
	Callback = InCallback;
}

void UUniversalToggle::SetText(const FString& Text)
{
	BtnText->SetText(FText::FromString(Text));
}

void UUniversalToggle::SetSelected(const bool bSelected)
{
	bIsSelected = bSelected;
	OnSelectBP();
}

void UUniversalToggle::OnClickAction()
{
	if (Callback != nullptr)
	{
		Callback(this);
	}
}
