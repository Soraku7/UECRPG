#pragma once

#include "CoreMinimal.h"
#include "Luban/Generated/schema.h"
#include "UniversalDataStruct.generated.h"

USTRUCT(BlueprintType)
struct FInfoData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info", DisplayName = "Name")
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info", DisplayName = "Description")
	FString Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info", DisplayName = "Icon")
	FString Icon;

	FInfoData() : Name(""), Description(""), Icon("")
	{
	}

	explicit FInfoData(const std::shared_ptr<cfg::Uni::BasicInfo>& TableData) :
		Name(UTF8_TO_TCHAR(TableData->name.c_str())), Description(UTF8_TO_TCHAR(TableData->des.c_str())),
		Icon(UTF8_TO_TCHAR(TableData->icon.c_str()))
	{
	}

	static FInfoData Set(const FInfoData InInfo)
	{
		FInfoData Info;
		Info.Name = InInfo.Name;
		Info.Description = InInfo.Description;
		Info.Icon = InInfo.Icon;
		return Info;
	}
};
