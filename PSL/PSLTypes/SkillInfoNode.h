#pragma once


#include "SkillInfoNode.generated.h"

class UImage;

USTRUCT(BlueprintType)
struct FSkillInfoNode
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UImage* SkillImage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString SkillName;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 CurrentLevel;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 MaxLevel;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText SkillDescription;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText OtherInfo;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> SkillGameplayEffect;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 SkillId;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 FormerSkillId;
	
};
