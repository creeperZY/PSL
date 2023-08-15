#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

/*
 * Singleton containing native Gameplay Tags
 */

struct FPSLGameplayTags
{
public:
    static const FPSLGameplayTags& Get() { return GameplayTags;}
    static void InitializeNativeGameplayTags();

	FGameplayTag A_Soldier_LV1;
	FGameplayTag A_Soldier_LV2;
	FGameplayTag A_Soldier_LV3;
	FGameplayTag A_Soldier_LV4;
	FGameplayTag A_Soldier_LV5;
	FGameplayTag A_Soldier_LV6;
	FGameplayTag A_Soldier_LV7;
	FGameplayTag A_Soldier_LV8;
	FGameplayTag A_Soldier_LV9;

	FGameplayTag B_Medic_LV1;
	FGameplayTag B_Medic_LV2;
	FGameplayTag B_Medic_LV3;
	FGameplayTag B_Medic_LV4;
	FGameplayTag B_Medic_LV5;
	FGameplayTag B_Medic_LV6;
	FGameplayTag B_Medic_LV7;
	FGameplayTag B_Medic_LV8;
	FGameplayTag B_Medic_LV9;

	FGameplayTag C_Weaponeer_LV1;
	FGameplayTag C_Weaponeer_LV2;
	FGameplayTag C_Weaponeer_LV3;
	FGameplayTag C_Weaponeer_LV4;
	FGameplayTag C_Weaponeer_LV5;
	FGameplayTag C_Weaponeer_LV6;
	FGameplayTag C_Weaponeer_LV7;
	FGameplayTag C_Weaponeer_LV8;
	FGameplayTag C_Weaponeer_LV9;

	FGameplayTag D_Craftsman_LV1;
	FGameplayTag D_Craftsman_LV2;
	FGameplayTag D_Craftsman_LV3;
	FGameplayTag D_Craftsman_LV4;
	FGameplayTag D_Craftsman_LV5;
	FGameplayTag D_Craftsman_LV6;
	FGameplayTag D_Craftsman_LV7;
	FGameplayTag D_Craftsman_LV8;
	FGameplayTag D_Craftsman_LV9;
	FGameplayTag D_Craftsman_LV10;
	FGameplayTag D_Craftsman_LV11;

	FGameplayTag E_Godfather_LV1;
	FGameplayTag E_Godfather_LV2;
	FGameplayTag E_Godfather_LV3;
	FGameplayTag E_Godfather_LV4;
	FGameplayTag E_Godfather_LV5;
	FGameplayTag E_Godfather_LV6;
	FGameplayTag E_Godfather_LV7;
	FGameplayTag E_Godfather_LV8;
	FGameplayTag E_Godfather_LV9;
	FGameplayTag E_Godfather_LV10;
	FGameplayTag E_Godfather_LV11;
	FGameplayTag E_Godfather_LV12;

	FGameplayTag F_Athlete_LV1;
	FGameplayTag F_Athlete_LV2;
	FGameplayTag F_Athlete_LV3;
	FGameplayTag F_Athlete_LV4;
	FGameplayTag F_Athlete_LV5;
	FGameplayTag F_Athlete_LV6;
	FGameplayTag F_Athlete_LV7;
	FGameplayTag F_Athlete_LV8;
	FGameplayTag F_Athlete_LV9;

private:
    static FPSLGameplayTags GameplayTags;
};
