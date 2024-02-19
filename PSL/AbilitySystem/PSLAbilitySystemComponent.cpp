// Fill out your copyright notice in the Description page of Project Settings.


#include "PSLAbilitySystemComponent.h"

#include "PSL/EasyMacros.h"

void UPSLAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UPSLAbilitySystemComponent::EffectApplied);
}

void UPSLAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* AbilitySystemComponent,
                                               const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle)
{
	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer);

	EffectAssetTagsDelegate.Broadcast(TagContainer);

}
