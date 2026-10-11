// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include <functional>
#include "CoreMinimal.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "UniversalToggle.generated.h"

class UTextBlock;
class UButton;
/**
 * 
 */
UCLASS()
class UECRPG_API UUniversalToggle : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UButton> Btn;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> BtnText;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, DisplayName = "Button Text")
	FText TextContent;

	std::function<void(UUniversalToggle*)> Callback;

public:
	UPROPERTY(BlueprintReadOnly)
	bool bIsSelected;

protected:
	virtual void NativePreConstruct() override;

	virtual void NativeOnInitialized() override;

public:
	virtual void OnInitCallback(const std::function<void(UUniversalToggle*)>& InCallback = nullptr);

	virtual void SetText(const FString& Text);

	void SetSelected(const bool bSelected);

protected:
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void OnSelectBP();

	UFUNCTION()
	virtual void OnClickAction();
};
