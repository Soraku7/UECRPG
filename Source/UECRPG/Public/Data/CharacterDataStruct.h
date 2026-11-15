#pragma once
#include "CoreMinimal.h"
#include "UniversalDataStruct.h"
#include "CharacterDataStruct.generated.h"

USTRUCT(BlueprintType)
struct FCharacterInfoData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterInfoData, DisplayName = "Character Info")
	FInfoData InfoData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterInfoData, DisplayName = "Character Age")
	int32 Age;

	UPROPERTY(Editanywhere, BlueprintReadWrite, Category = CharacterInfoData, DisplayName = "Character Story")
	FString Story;

	FCharacterInfoData() : Age{0}, Story("")
	{
	}

	explicit FCharacterInfoData(const luban::SharedPtr<cfg::Character::CharacterTable>& CharacterTable) :
		InfoData(FInfoData(CharacterTable->basicInfo)), Age(CharacterTable->age),
		Story(UTF8_TO_TCHAR(CharacterTable->story.c_str()))
	{
	}
};
