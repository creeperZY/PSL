#include "PSLGameplayTags.h"
#include "GameplayTagsManager.h"

FPSLGameplayTags FPSLGameplayTags::GameplayTags;

void FPSLGameplayTags::InitializeNativeGameplayTags()
{
	/*
	 * A Soldier
	 */
	GameplayTags.A_Soldier_LV1 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("A.Soldier.LV1"),
	FString("")
	);

	GameplayTags.A_Soldier_LV2 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("A.Soldier.LV2"),
	FString("")
	);
	
	GameplayTags.A_Soldier_LV3 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("A.Soldier.LV3"),
	FString("")
	);
	
	GameplayTags.A_Soldier_LV4 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("A.Soldier.LV4"),
	FString("")
	);
		
	GameplayTags.A_Soldier_LV5 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("A.Soldier.LV5"),
	FString("")
	);
	
	GameplayTags.A_Soldier_LV6 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("A.Soldier.LV6"),
	FString("")
	);

	GameplayTags.A_Soldier_LV7 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("A.Soldier.LV7"),
	FString("")
	);

	GameplayTags.A_Soldier_LV8 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("A.Soldier.LV8"),
	FString("")
	);

	GameplayTags.A_Soldier_LV9 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("A.Soldier.LV9"),
	FString("")
	);

	/*
	 * B Medic
	 */
	GameplayTags.B_Medic_LV1 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("B.Medic.LV1"),
	FString("aaaa")
	);

	GameplayTags.B_Medic_LV2 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("B.Medic.LV2"),
	FString("bbbb")
	);

	GameplayTags.B_Medic_LV3 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("B.Medic.LV3"),
	FString("")
	);

	GameplayTags.B_Medic_LV4 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("B.Medic.LV4"),
	FString("")
	);

	GameplayTags.B_Medic_LV5 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("B.Medic.LV5"),
	FString("")
	);

	GameplayTags.B_Medic_LV6 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("B.Medic.LV6"),
	FString("")
	);

	GameplayTags.B_Medic_LV7 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("B.Medic.LV7"),
	FString("")
	);

	GameplayTags.B_Medic_LV8 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("B.Medic.LV8"),
	FString("")
	);

	GameplayTags.B_Medic_LV9 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("B.Medic.LV9"),
	FString("")
	);

	/*
	 * C Weaponeer
	 */
	GameplayTags.C_Weaponeer_LV1 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("C.Weaponeer.LV1"),
	FString("")
	);

	GameplayTags.C_Weaponeer_LV2 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("C.Weaponeer.LV2"),
	FString("")
	);

	GameplayTags.C_Weaponeer_LV3 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("C.Weaponeer.LV3"),
	FString("")
	);

	GameplayTags.C_Weaponeer_LV4 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("C.Weaponeer.LV4"),
	FString("")
	);

	GameplayTags.C_Weaponeer_LV5 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("C.Weaponeer.LV5"),
	FString("")
	);

	GameplayTags.C_Weaponeer_LV6 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("C.Weaponeer.LV6"),
	FString("")
	);

	GameplayTags.C_Weaponeer_LV7 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("C.Weaponeer.LV7"),
	FString("")
	);

	GameplayTags.C_Weaponeer_LV8 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("C.Weaponeer.LV8"),
	FString("")
	);

	GameplayTags.C_Weaponeer_LV9 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("C.Weaponeer.LV9"),
	FString("")
	);

	/*
	 * D Craftsman
	 */
	GameplayTags.D_Craftsman_LV1 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("D.Craftsman.LV1"),
	FString("")
	);

	GameplayTags.D_Craftsman_LV2 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("D.Craftsman.LV2"),
	FString("")
	);

	GameplayTags.D_Craftsman_LV3 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("D.Craftsman.LV3"),
	FString("")
	);

	GameplayTags.D_Craftsman_LV4 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("D.Craftsman.LV4"),
	FString("")
	);

	GameplayTags.D_Craftsman_LV5 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("D.Craftsman.LV5"),
	FString("")
	);

	GameplayTags.D_Craftsman_LV6 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("D.Craftsman.LV6"),
	FString("")
	);

	GameplayTags.D_Craftsman_LV7 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("D.Craftsman.LV7"),
	FString("")
	);

	GameplayTags.D_Craftsman_LV8 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("D.Craftsman.LV8"),
	FString("")
	);

	GameplayTags.D_Craftsman_LV9 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("D.Craftsman.LV9"),
	FString("")
	);

	GameplayTags.D_Craftsman_LV10 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("D.Craftsman.LV10"),
	FString("")
	);
	
	GameplayTags.D_Craftsman_LV11 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("D.Craftsman.LV11"),
	FString("")
	);

	/*
	 * E Godfather
	 */
	GameplayTags.E_Godfather_LV1 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("E.Godfather.LV1"),
	FString("")
	);

	GameplayTags.E_Godfather_LV2 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("E.Godfather.LV2"),
	FString("")
	);

	GameplayTags.E_Godfather_LV3 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("E.Godfather.LV3"),
	FString("")
	);

	GameplayTags.E_Godfather_LV4 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("E.Godfather.LV4"),
	FString("")
	);

	GameplayTags.E_Godfather_LV5 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("E.Godfather.LV5"),
	FString("")
	);

	GameplayTags.E_Godfather_LV6 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("E.Godfather.LV6"),
	FString("")
	);

	GameplayTags.E_Godfather_LV7 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("E.Godfather.LV7"),
	FString("")
	);

	GameplayTags.E_Godfather_LV8 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("E.Godfather.LV8"),
	FString("")
	);

	GameplayTags.E_Godfather_LV9 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("E.Godfather.LV9"),
	FString("")
	);

	GameplayTags.E_Godfather_LV10 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("E.Godfather.LV10"),
	FString("")
	);

	GameplayTags.E_Godfather_LV11 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("E.Godfather.LV11"),
	FString("")
	);

	GameplayTags.E_Godfather_LV12 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("E.Godfather.LV12"),
	FString("")
	);

	/*
	 * F Athlete
	 */
	GameplayTags.F_Athlete_LV1 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("F.Athlete.LV1"),
	FString("")
	);

	GameplayTags.F_Athlete_LV2 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("F.Athlete.LV2"),
	FString("")
	);

	GameplayTags.F_Athlete_LV3 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("F.Athlete.LV3"),
	FString("")
	);

	GameplayTags.F_Athlete_LV4 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("F.Athlete.LV4"),
	FString("")
	);

	GameplayTags.F_Athlete_LV5 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("F.Athlete.LV5"),
	FString("")
	);

	GameplayTags.F_Athlete_LV6 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("F.Athlete.LV6"),
	FString("")
	);

	GameplayTags.F_Athlete_LV7 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("F.Athlete.LV7"),
	FString("")
	);

	GameplayTags.F_Athlete_LV8 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("F.Athlete.LV8"),
	FString("")
	);

	GameplayTags.F_Athlete_LV9 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("F.Athlete.LV9"),
	FString("")
	);

}
