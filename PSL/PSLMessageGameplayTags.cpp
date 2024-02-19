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
	

}
