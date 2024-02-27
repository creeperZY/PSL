#include "PSLMessageGameplayTags.h"
#include "GameplayTagsManager.h"

FPSLMessageGameplayTags FPSLMessageGameplayTags::GameplayTags;

void FPSLMessageGameplayTags::InitializeNativeGameplayTags()
{
	/*
	 * Basic
	 */
	GameplayTags.Message_Basic_Health = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Message.Basic.Health"),
	FString("")
	);
	
	GameplayTags.Message_Basic_Armor = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Message.Basic.Armor"),
	FString("")
	);

	/*
	 * Pickup
	 */
	GameplayTags.Message_Pickup_Grenade_Frag = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Message.Pickup.Grenade.Frag"),
	FString("")
	);

	GameplayTags.Message_Pickup_Ammo_AR556 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Message.Pickup.Ammo.AR556"),
	FString("")
	);
}
