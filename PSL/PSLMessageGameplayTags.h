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

	FGameplayTag Message_Pickup_Grenade_Frag;

	FGameplayTag Message_Pickup_Ammo_AR556;

private:
    static FPSLMessageGameplayTags GameplayTags;
};
