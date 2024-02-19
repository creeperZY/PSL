// Fill out your copyright notice in the Description page of Project Settings.


#include "OverlayWidgetController.h"

#include "PSL/EasyMacros.h"
#include "PSL/AbilitySystem/PSLAbilitySystemComponent.h"
#include "PSL/AbilitySystem/PSLAttributeSet.h"
#include "PSL/Character/PSLCharacter.h"
#include "PSL/PlayerController/PSLPlayerController.h"

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
	.AddUObject(this, &UOverlayWidgetController::HealthChanged);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(PSLAttributeSet->GetMaxHealthAttribute())
	.AddUObject(this, &UOverlayWidgetController::MaxHealthChanged);

	Cast<UPSLAbilitySystemComponent>(AbilitySystemComponent)->EffectAssetTagsDelegate
	.AddLambda(
		[this](const FGameplayTagContainer& AssetTags)
		{

			//xxx
			const APSLCharacter* PSLCharacter = Cast<APSLCharacter>(AbilitySystemComponent->GetOwner());
			const APSLPlayerController* PSLPlayerController = Cast<APSLPlayerController>(PSLCharacter->GetController());
			if (!PSLPlayerController) return;
			
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
	);
}

void UOverlayWidgetController::HealthChanged(const FOnAttributeChangeData& Data) const
{
	OnHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxHealthChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxHealthChanged.Broadcast(Data.NewValue);
}
