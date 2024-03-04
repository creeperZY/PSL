// Fill out your copyright notice in the Description page of Project Settings.


#include "OverlayWidgetController.h"

#include "PSL/EasyMacros.h"
#include "PSL/AbilitySystem/PSLAbilitySystemComponent.h"
#include "PSL/AbilitySystem/PSLAttributeSet.h"
#include "PSL/Character/PSLCharacter.h"
#include "PSL/PlayerController/PSLPlayerController.h"
#include "PSL/PSLComponents/CombatComponent.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	const UPSLAttributeSet* PSLAttributeSet = CastChecked<UPSLAttributeSet>(AttributeSet);
	OnHealthChanged.Broadcast(PSLAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(PSLAttributeSet->GetMaxHealth());
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	const UPSLAttributeSet* PSLAttributeSet = CastChecked<UPSLAttributeSet>(AttributeSet);
	
	// It is not a DYNAMIC so do not use AddDynamic, instead, using AddUObject.
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(PSLAttributeSet->GetHealthAttribute())
	.AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnHealthChanged.Broadcast(Data.NewValue);
		}
	);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(PSLAttributeSet->GetMaxHealthAttribute())
	.AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnMaxHealthChanged.Broadcast(Data.NewValue);
		}
	);
	
	Cast<UPSLAbilitySystemComponent>(AbilitySystemComponent)->EffectAssetTagsDelegate
	.AddLambda(
		[this](const FGameplayTagContainer& AssetTags)
		{
			const APSLCharacter* PSLCharacter = Cast<APSLCharacter>(AbilitySystemComponent->GetOwner());
			const APSLPlayerController* PSLPlayerController = Cast<APSLPlayerController>(PSLCharacter->GetController());
			if (!PSLPlayerController) return; // Do not push msg for AI
			AssetTagsToBroadcastMessages(AssetTags);
		}
	);
	
	Cast<APSLCharacter>(AbilitySystemComponent->GetOwner())->GetCombat()->AmmoPickupDelegate
	.AddLambda(
		[this](const FGameplayTagContainer& AssetTags, const TMap<EWeaponType, float>& AmmoNumMap)
		{
			const APSLCharacter* PSLCharacter = Cast<APSLCharacter>(AbilitySystemComponent->GetOwner());
			const APSLPlayerController* PSLPlayerController = Cast<APSLPlayerController>(PSLCharacter->GetController());
			if (!PSLPlayerController) return;
			AssetTagsToBroadcastMessages(AssetTags);
		}
	);
	

	Cast<APSLCharacter>(AbilitySystemComponent->GetOwner())->GetCombat()->GrenadePickupDelegate
	.AddLambda(
		[this](const FGameplayTagContainer& AssetTags, const TMap<EGrenadeType, float>& GrenadeNumMap)
		{
			const APSLCharacter* PSLCharacter = Cast<APSLCharacter>(AbilitySystemComponent->GetOwner());
			const APSLPlayerController* PSLPlayerController = Cast<APSLPlayerController>(PSLCharacter->GetController());
			PRINT_ONE_VAR("%s", *this->GetName());
			if (!PSLPlayerController) return;
			PRINT_STR("combat lambda in wc222")
			for (auto& Pair : GrenadeNumMap)
			{
				PRINT_ONE_VAR("%f", Pair.Value);
			}
			AssetTagsToBroadcastMessages(AssetTags);
		}
	);
	
}


void UOverlayWidgetController::AssetTagsToBroadcastMessages(const FGameplayTagContainer& AssetTags)
{
	for (const FGameplayTag& Tag : AssetTags)
	{
		// For example, say that Tag = Message.HealthPotion
		// MatchesTag: "A.1".MatchesTag("A") will return True, "A".MatchesTag("A.1") will return False
		FGameplayTag MessageTag = FGameplayTag::RequestGameplayTag(FName("Message"));
		if (Tag.MatchesTag(MessageTag))
		{
			const FUIWidgetRow* Row = GetDataTableRowByTag<FUIWidgetRow>(MessageWidgetDataTable, Tag);
			if (Row) MessageWidgetRowDelegate.Broadcast(*Row);
		}
								
	}
}
