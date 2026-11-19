// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Component/AttributeHandleComponent.h"

#include "Character/CharacterBase.h"
#include "Character/Component/AbilityComponent.h"
#include "GAS/Attribute/BasicAttributeSet.h"


// Sets default values for this component's properties
UAttributeHandleComponent::UAttributeHandleComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAttributeHandleComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}


// Called every frame
void UAttributeHandleComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                              FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UAttributeHandleComponent::DoInitialize()
{
	Owner = Cast<ACharacterBase>(GetOwner());
	UE_LOG(LogTemp, Warning, TEXT("UAttributeHandleComponent::DoInitialize()"));
	BindAttributeDelegates();
}

void UAttributeHandleComponent::DoReset()
{
	IUnitComponentInterface::DoReset();
}

void UAttributeHandleComponent::DoDispose()
{
	ClearAttributeDelegates();
}

ACharacterBase* UAttributeHandleComponent::GetCompOwner() const
{
	return Owner;
}

void UAttributeHandleComponent::BindAttributeDelegates()
{
	GetWorld()->GetTimerManager().SetTimerForNextTick([&]()
	{
		Owner->GetAbilityComponent()->GetGameplayAttributeValueChangeDelegate(UBasicAttributeSet::GetHealthAttribute()).
		       AddUObject(this, &UAttributeHandleComponent::OnBasicAttributeChange);
		Owner->GetAbilityComponent()->GetGameplayAttributeValueChangeDelegate(UBasicAttributeSet::GetArmorAttribute()).
		       AddUObject(this, &UAttributeHandleComponent::OnBasicAttributeChange);
		Owner->GetAbilityComponent()->GetGameplayAttributeValueChangeDelegate(UBasicAttributeSet::GetAPAttribute()).
		       AddUObject(this, &UAttributeHandleComponent::OnBasicAttributeChange);
		Owner->GetAbilityComponent()->GetGameplayAttributeValueChangeDelegate(UBasicAttributeSet::GetMPAttribute()).
		       AddUObject(this, &UAttributeHandleComponent::OnBasicAttributeChange);
	});
}

void UAttributeHandleComponent::ClearAttributeDelegates()
{
	Owner->GetAbilityComponent()->GetGameplayAttributeValueChangeDelegate(UBasicAttributeSet::GetHealthAttribute()).
	       Clear();
	Owner->GetAbilityComponent()->GetGameplayAttributeValueChangeDelegate(UBasicAttributeSet::GetArmorAttribute()).
	       Clear();
	Owner->GetAbilityComponent()->GetGameplayAttributeValueChangeDelegate(UBasicAttributeSet::GetAPAttribute()).
	       Clear();
	Owner->GetAbilityComponent()->GetGameplayAttributeValueChangeDelegate(UBasicAttributeSet::GetMPAttribute()).
	       Clear();
}

void UAttributeHandleComponent::OnBasicAttributeChange(const FOnAttributeChangeData& Data)
{
	if (OnAttributeChangeDelegate.IsBound())
	{
		OnAttributeChangeDelegate.Broadcast();
	}
}
