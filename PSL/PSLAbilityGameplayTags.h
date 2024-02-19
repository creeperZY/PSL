#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

/*
 * Singleton containing native Gameplay Tags
 */

struct FPSLAbilityGameplayTags
{
public:
    static const FPSLAbilityGameplayTags& Get() { return GameplayTags;}
    static void InitializeNativeGameplayTags();
	
	FGameplayTag Ability_A_Soldier_LV1;
	FGameplayTag Ability_A_Soldier_LV2;
	FGameplayTag Ability_A_Soldier_LV3;
	FGameplayTag Ability_A_Soldier_LV4;
	FGameplayTag Ability_A_Soldier_LV5;
	FGameplayTag Ability_A_Soldier_LV6;
	FGameplayTag Ability_A_Soldier_LV7;
	FGameplayTag Ability_A_Soldier_LV8;
	FGameplayTag Ability_A_Soldier_LV9;

	FGameplayTag Ability_B_Medic_LV1;
	FGameplayTag Ability_B_Medic_LV2;
	FGameplayTag Ability_B_Medic_LV3;
	FGameplayTag Ability_B_Medic_LV4;
	FGameplayTag Ability_B_Medic_LV5;
	FGameplayTag Ability_B_Medic_LV6;
	FGameplayTag Ability_B_Medic_LV7;
	FGameplayTag Ability_B_Medic_LV8;
	FGameplayTag Ability_B_Medic_LV9;

	FGameplayTag Ability_C_Weaponeer_LV1;
	FGameplayTag Ability_C_Weaponeer_LV2;
	FGameplayTag Ability_C_Weaponeer_LV3;
	FGameplayTag Ability_C_Weaponeer_LV4;
	FGameplayTag Ability_C_Weaponeer_LV5;
	FGameplayTag Ability_C_Weaponeer_LV6;
	FGameplayTag Ability_C_Weaponeer_LV7;
	FGameplayTag Ability_C_Weaponeer_LV8;
	FGameplayTag Ability_C_Weaponeer_LV9;

	FGameplayTag Ability_D_Craftsman_LV1;
	FGameplayTag Ability_D_Craftsman_LV2;
	FGameplayTag Ability_D_Craftsman_LV3;
	FGameplayTag Ability_D_Craftsman_LV4;
	FGameplayTag Ability_D_Craftsman_LV5;
	FGameplayTag Ability_D_Craftsman_LV6;
	FGameplayTag Ability_D_Craftsman_LV7;
	FGameplayTag Ability_D_Craftsman_LV8;
	FGameplayTag Ability_D_Craftsman_LV9;
	FGameplayTag Ability_D_Craftsman_LV10;
	FGameplayTag Ability_D_Craftsman_LV11;

	FGameplayTag Ability_E_Godfather_LV1;
	FGameplayTag Ability_E_Godfather_LV2;
	FGameplayTag Ability_E_Godfather_LV3;
	FGameplayTag Ability_E_Godfather_LV4;
	FGameplayTag Ability_E_Godfather_LV5;
	FGameplayTag Ability_E_Godfather_LV6;
	FGameplayTag Ability_E_Godfather_LV7;
	FGameplayTag Ability_E_Godfather_LV8;
	FGameplayTag Ability_E_Godfather_LV9;
	FGameplayTag Ability_E_Godfather_LV10;
	FGameplayTag Ability_E_Godfather_LV11;
	FGameplayTag Ability_E_Godfather_LV12;

	FGameplayTag Ability_F_Athlete_LV1;
	FGameplayTag Ability_F_Athlete_LV2;
	FGameplayTag Ability_F_Athlete_LV3;
	FGameplayTag Ability_F_Athlete_LV4;
	FGameplayTag Ability_F_Athlete_LV5;
	FGameplayTag Ability_F_Athlete_LV6;
	FGameplayTag Ability_F_Athlete_LV7;
	FGameplayTag Ability_F_Athlete_LV8;
	FGameplayTag Ability_F_Athlete_LV9;

private:
    static FPSLAbilityGameplayTags GameplayTags;
};
