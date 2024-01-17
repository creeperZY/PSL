// Fill out your copyright notice in the Description page of Project Settings.


#include "OverlayWidgetController.h"

#include "PSL/AbilitySystem/PSLAttributeSet.h"

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
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(PSLAttributeSet->GetHealthAttribute()).AddUObject(this, &UOverlayWidgetController::HealthChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(PSLAttributeSet->GetMaxHealthAttribute()).AddUObject(this, &UOverlayWidgetController::MaxHealthChanged);
}

void UOverlayWidgetController::HealthChanged(const FOnAttributeChangeData& Data) const
{
	OnHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxHealthChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxHealthChanged.Broadcast(Data.NewValue);
}
