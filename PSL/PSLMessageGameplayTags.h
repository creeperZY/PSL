#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

/*
 * Singleton containing native Gameplay Tags
 */

struct FPSLMessageGameplayTags
{
public:
    static const FPSLMessageGameplayTags& Get() { return GameplayTags;}
    static void InitializeNativeGameplayTags();

	FGameplayTag Message_Basic_Health;
	FGameplayTag Message_Basic_Armor;


private:
    static FPSLMessageGameplayTags GameplayTags;
};
