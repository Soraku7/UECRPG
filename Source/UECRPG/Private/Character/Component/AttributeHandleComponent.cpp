// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Component/AttributeHandleComponent.h"

#include "Character/CharacterBase.h"


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
}

void UAttributeHandleComponent::DoReset()
{
	IUnitComponentInterface::DoReset();
}

void UAttributeHandleComponent::DoDispose()
{
	IUnitComponentInterface::DoDispose();
}

ACharacterBase* UAttributeHandleComponent::GetCompOwner() const
{
	return Owner;
}
