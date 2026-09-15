// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Public/UI/UIBase.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "UISystem.generated.h"

class UUIBase;
/**
 * 
 */
UCLASS()
class UECRPG_API UUISystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	TArray<TObjectPtr<UUIBase>> UIList;

public:
	template <typename WidgetT = UUIBase>
	WidgetT* LoadUI()
	{
		const FString WidgetName = WidgetT::StaticClass()->GetName();
		if (WidgetT* InListUI = GetUI<WidgetT>(); IsValid(InListUI))
		{
			UE_LOG(LogTemp, Warning, TEXT("UI %s"), *WidgetName);
			if (InListUI->bIsClose)
			{
				UE_LOG(LogTemp, Warning, TEXT("%s UI关闭 重新显示"), *WidgetName);
				InListUI->DoLoad();
			}
			return InListUI;
		}

		const FString Path = FString::Printf(
			TEXT("/Script/Engine.Blueprint'/Game/Widget/WBP_%s.WBP_%s_C'"), *WidgetName, *WidgetName);

		UClass* WidgetClass = LoadClass<UUIBase>(nullptr, *Path);
		if (WidgetClass)
		{
			if (WidgetT* UI = Cast<WidgetT>(CreateWidget<UUserWidget>(GetWorld(), WidgetClass)))
			{
				UI->AddToViewport(UI->ZOrder);
				UI->DoLoad();
				UIList.Add(UI);
				return UI;
			}
			return nullptr;
		}

		return nullptr;
	}

	template <typename WidgetT = UUIBase>
	WidgetT* GetUI()
	{
		UClass* ParentClass = GetParentNativeClass(WidgetT::StaticClass());
		const TObjectPtr<UUIBase>* FoundUIClass = UIList.FindByPredicate([ParentClass](const UUIBase* UIBase)
		{
			return GetParentNativeClass(UIBase->GetClass()) == ParentClass;
		});

		if (FoundUIClass)
		{
			WidgetT* UI = Cast<WidgetT>(*FoundUIClass);
			return UI;
		}

		return nullptr;
	}

	template <typename WidgetT = UUIBase>
	void ToggleUI()
	{
		if (WidgetT* UI = GetUI<WidgetT>(); IsValid(UI))
		{
			if (UI->bIsClose)
			{
				UI->DoLoad();
			}
			else
			{
				UI->DoClose();
			}
		}
		else
		{
			LoadUI<WidgetT>();
		}
	}

	void RemoveFromList(UUIBase* UI)
	{
		UIList.Remove(UI);
	}
	
	template <typename WidgetT = UUIBase>
	void CloseUI()
	{
		WidgetT* UI = GetUI<WidgetT>();
		if (IsValid(UI))
		{
			if (!UI->bIsClose)
			{
				UI->DoClose();
			}
		}
	}

	UFUNCTION(BlueprintCallable)
	FORCEINLINE UUIBase* LoadUI(const TSubclassOf<UUIBase> WidgetClass)
	{
		UUIBase* InListUI = GetUI(WidgetClass);
		if (IsValid(InListUI))
		{
			if (InListUI->bIsClose)
			{
				InListUI->DoLoad();
			}
			return InListUI;
		}

		if (WidgetClass)
		{
			if (UUIBase* UI = Cast<UUIBase>(CreateWidget<UUserWidget>(GetWorld(), WidgetClass)))
			{
				UI->AddToViewport(UI->ZOrder);
				UI->DoLoad();
				UIList.Add(UI);
				return UI;
			}
			return nullptr;
		}
		return nullptr;
	}

	UFUNCTION(BlueprintCallable)
	FORCEINLINE UUIBase* GetUI(const TSubclassOf<UUIBase> WidgetClass)
	{
		UClass* ParentClass = GetParentNativeClass(WidgetClass);
		const TObjectPtr<UUIBase>* FoundUIClass = UIList.FindByPredicate([ParentClass](const UUIBase* UIClass)
		{
			return GetParentNativeClass(UIClass->GetClass()) == ParentClass;
		});
		if (FoundUIClass)
		{
			UUIBase* UI = Cast<UUIBase>(*FoundUIClass);
			return UI;
		}

		return nullptr;
	}
	
	UFUNCTION(BlueprintCallable)
	FORCEINLINE void CloseUI(const TSubclassOf<UUIBase> WidgetClass)
	{
		UUIBase* UI = GetUI(WidgetClass);
		if (IsValid(UI))
		{
			if (!UI->bIsClose)
			{
				UI->DoClose();
			}
		}
	}
};
