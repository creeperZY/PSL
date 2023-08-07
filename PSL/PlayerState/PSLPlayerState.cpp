// Fill out your copyright notice in the Description page of Project Settings.


#include "PSLPlayerState.h"

#include "PSL/AbilitySystem/PSLAbilitySystemComponent.h"
#include "PSL/AbilitySystem/PSLAttributeSet.h"

APSLPlayerState::APSLPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UPSLAbilitySystemComponent>("AbilitySystemComponent");
	AttributeSet = CreateDefaultSubobject<UPSLAttributeSet>("AttributeSet");
}
