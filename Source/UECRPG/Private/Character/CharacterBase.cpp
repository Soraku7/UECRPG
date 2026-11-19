// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CharacterBase.h"

#include "Character/Component/AbilityComponent.h"
#include "Character/Component/AttributeHandleComponent.h"
#include "Components/CapsuleComponent.h"
#include "Function/GlobalFunc.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GAS/Attribute/BasicAttributeSet.h"
#include "SubSystem/DataSystem.h"


// Sets default values
ACharacterBase::ACharacterBase()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CharacterHandleComponent = CreateDefaultSubobject<UAttributeHandleComponent>(TEXT("CharacterHandleComponent"));
	AbilityComponent = CreateDefaultSubobject<UAbilityComponent>(TEXT("AbilityComponent"));

	BasicAttribute = CreateDefaultSubobject<UBasicAttributeSet>(TEXT("BasicAttribute"));
}

// Called when the game starts or when spawned
void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();

	InitializeData();
}

void ACharacterBase::InitializeData_Implementation()
{
	const auto TbCharacter = UGlobalFunc::GetSubsystem<UDataSystem>()->GetTbCharacterData(CharacterID);

	if (TbCharacter != nullptr)
	{
		CharacterInfoData = FCharacterInfoData(TbCharacter);
		Faction = static_cast<EFactionType>(TbCharacter->faction);
	}

	for (UAttributeSet* UAttributeSet : GetAbilityComponent()->GetSpawnedAttributes())
	{
		const auto AttrSet = Cast<UAttributeSetBase>(UAttributeSet);
		AttrSet->DoInitialize();
	}

	const auto UnitComponents = GetComponentsByInterface(UUnitComponentInterface::StaticClass());

	for (const auto& Unit : UnitComponents)
	{
		Cast<IUnitComponentInterface>(Unit)->DoInitialize();
	}
}

// Called every frame
void ACharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ACharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

UAbilitySystemComponent* ACharacterBase::GetAbilitySystemComponent() const
{
	return AbilityComponent;
}
