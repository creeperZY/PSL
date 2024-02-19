#include "PSLAbilityGameplayTags.h"
#include "GameplayTagsManager.h"

FPSLAbilityGameplayTags FPSLAbilityGameplayTags::GameplayTags;

void FPSLAbilityGameplayTags::InitializeNativeGameplayTags()
{

	/*
	 * A Soldier
	 */
	GameplayTags.Ability_A_Soldier_LV1 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Attribute.Ability.A.Soldier.LV1"),
	FString("")
	);

	GameplayTags.Ability_A_Soldier_LV2 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Attribute.Ability.A.Soldier.LV2"),
	FString("")
	);
	
	GameplayTags.Ability_A_Soldier_LV3 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Attribute.Ability.A.Soldier.LV3"),
	FString("")
	);
	
	GameplayTags.Ability_A_Soldier_LV4 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Attribute.Ability.A.Soldier.LV4"),
	FString("")
	);
		
	GameplayTags.Ability_A_Soldier_LV5 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Attribute.Ability.A.Soldier.LV5"),
	FString("")
	);
	
	GameplayTags.Ability_A_Soldier_LV6 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Attribute.Ability.A.Soldier.LV6"),
	FString("")
	);

	GameplayTags.Ability_A_Soldier_LV7 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Attribute.Ability.A.Soldier.LV7"),
	FString("")
	);

	GameplayTags.Ability_A_Soldier_LV8 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Attribute.Ability.A.Soldier.LV8"),
	FString("")
	);

	GameplayTags.Ability_A_Soldier_LV9 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Attribute.Ability.A.Soldier.LV9"),
	FString("")
	);

	/*
	 * B Medic
	 */
	GameplayTags.Ability_B_Medic_LV1 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Attribute.Ability.B.Medic.LV1"),
	FString("aaaa")
	);

	GameplayTags.Ability_B_Medic_LV2 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Attribute.Ability.B.Medic.LV2"),
	FString("bbbb")
	);

	GameplayTags.Ability_B_Medic_LV3 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Attribute.Ability.B.Medic.LV3"),
	FString("")
	);

	GameplayTags.Ability_B_Medic_LV4 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Attribute.Ability.B.Medic.LV4"),
	FString("")
	);

	GameplayTags.Ability_B_Medic_LV5 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Attribute.Ability.B.Medic.LV5"),
	FString("")
	);

	GameplayTags.Ability_B_Medic_LV6 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Attribute.Ability.B.Medic.LV6"),
	FString("")
	);

	GameplayTags.Ability_B_Medic_LV7 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Attribute.Ability.B.Medic.LV7"),
	FString("")
	);

	GameplayTags.Ability_B_Medic_LV8 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Attribute.Ability.B.Medic.LV8"),
	FString("")
	);

	GameplayTags.Ability_B_Medic_LV9 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Attribute.Ability.B.Medic.LV9"),
	FString("")
	);

	/*
	 * C Weaponeer
	 */
	GameplayTags.Ability_C_Weaponeer_LV1 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Attribute.Ability.C.Weaponeer.LV1"),
	FString("")
	);

	GameplayTags.Ability_C_Weaponeer_LV2 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Attribute.Ability.C.Weaponeer.LV2"),
	FString("")
	);

	GameplayTags.Ability_C_Weaponeer_LV3 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Attribute.Ability.C.Weaponeer.LV3"),
	FString("")
	);

	GameplayTags.Ability_C_Weaponeer_LV4 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Attribute.Ability.C.Weaponeer.LV4"),
	FString("")
	);

	GameplayTags.Ability_C_Weaponeer_LV5 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Attribute.Ability.C.Weaponeer.LV5"),
	FString("")
	);

	GameplayTags.Ability_C_Weaponeer_LV6 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Attribute.Ability.C.Weaponeer.LV6"),
	FString("")
	);

	GameplayTags.Ability_C_Weaponeer_LV7 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Attribute.Ability.C.Weaponeer.LV7"),
	FString("")
	);

	GameplayTags.Ability_C_Weaponeer_LV8 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Attribute.Ability.C.Weaponeer.LV8"),
	FString("")
	);

	GameplayTags.Ability_C_Weaponeer_LV9 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Attribute.Ability.C.Weaponeer.LV9"),
	FString("")
	);

	/*
	 * D Craftsman
	 */
	GameplayTags.Ability_D_Craftsman_LV1 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Attribute.Ability.D.Craftsman.LV1"),
	FString("")
	);

	GameplayTags.Ability_D_Craftsman_LV2 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Attribute.Ability.D.Craftsman.LV2"),
	FString("")
	);

	GameplayTags.Ability_D_Craftsman_LV3 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Attribute.Ability.D.Craftsman.LV3"),
	FString("")
	);

	GameplayTags.Ability_D_Craftsman_LV4 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Attribute.Ability.D.Craftsman.LV4"),
	FString("")
	);

	GameplayTags.Ability_D_Craftsman_LV5 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Attribute.Ability.D.Craftsman.LV5"),
	FString("")
	);

	GameplayTags.Ability_D_Craftsman_LV6 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Attribute.Ability.D.Craftsman.LV6"),
	FString("")
	);

	GameplayTags.Ability_D_Craftsman_LV7 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Attribute.Ability.D.Craftsman.LV7"),
	FString("")
	);

	GameplayTags.Ability_D_Craftsman_LV8 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Attribute.Ability.D.Craftsman.LV8"),
	FString("")
	);

	GameplayTags.Ability_D_Craftsman_LV9 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Attribute.Ability.D.Craftsman.LV9"),
	FString("")
	);

	GameplayTags.Ability_D_Craftsman_LV10 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Attribute.Ability.D.Craftsman.LV10"),
	FString("")
	);
	
	GameplayTags.Ability_D_Craftsman_LV11 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Attribute.Ability.D.Craftsman.LV11"),
	FString("")
	);

	/*
	 * E Godfather
	 */
	GameplayTags.Ability_E_Godfather_LV1 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Attribute.Ability.E.Godfather.LV1"),
	FString("")
	);

	GameplayTags.Ability_E_Godfather_LV2 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Attribute.Ability.E.Godfather.LV2"),
	FString("")
	);

	GameplayTags.Ability_E_Godfather_LV3 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Attribute.Ability.E.Godfather.LV3"),
	FString("")
	);

	GameplayTags.Ability_E_Godfather_LV4 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Attribute.Ability.E.Godfather.LV4"),
	FString("")
	);

	GameplayTags.Ability_E_Godfather_LV5 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Attribute.Ability.E.Godfather.LV5"),
	FString("")
	);

	GameplayTags.Ability_E_Godfather_LV6 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Attribute.Ability.E.Godfather.LV6"),
	FString("")
	);

	GameplayTags.Ability_E_Godfather_LV7 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Attribute.Ability.E.Godfather.LV7"),
	FString("")
	);

	GameplayTags.Ability_E_Godfather_LV8 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Attribute.Ability.E.Godfather.LV8"),
	FString("")
	);

	GameplayTags.Ability_E_Godfather_LV9 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Attribute.Ability.E.Godfather.LV9"),
	FString("")
	);

	GameplayTags.Ability_E_Godfather_LV10 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Attribute.Ability.E.Godfather.LV10"),
	FString("")
	);

	GameplayTags.Ability_E_Godfather_LV11 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Attribute.Ability.E.Godfather.LV11"),
	FString("")
	);

	GameplayTags.Ability_E_Godfather_LV12 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Attribute.Ability.E.Godfather.LV12"),
	FString("")
	);

	/*
	 * F Athlete
	 */
	GameplayTags.Ability_F_Athlete_LV1 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Attribute.Ability.F.Athlete.LV1"),
	FString("")
	);

	GameplayTags.Ability_F_Athlete_LV2 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Attribute.Ability.F.Athlete.LV2"),
	FString("")
	);

	GameplayTags.Ability_F_Athlete_LV3 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Attribute.Ability.F.Athlete.LV3"),
	FString("")
	);

	GameplayTags.Ability_F_Athlete_LV4 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Attribute.Ability.F.Athlete.LV4"),
	FString("")
	);

	GameplayTags.Ability_F_Athlete_LV5 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Attribute.Ability.F.Athlete.LV5"),
	FString("")
	);

	GameplayTags.Ability_F_Athlete_LV6 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Attribute.Ability.F.Athlete.LV6"),
	FString("")
	);

	GameplayTags.Ability_F_Athlete_LV7 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Attribute.Ability.F.Athlete.LV7"),
	FString("")
	);

	GameplayTags.Ability_F_Athlete_LV8 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Attribute.Ability.F.Athlete.LV8"),
	FString("")
	);

	GameplayTags.Ability_F_Athlete_LV9 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Attribute.Ability.F.Athlete.LV9"),
	FString("")
	);

}
