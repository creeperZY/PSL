// Copyright Epic Games, Inc. All Rights Reserved.

#include "PSLGameMode.h"
#include "PSL/AbilitySystem/PSLAbilitySystemComponent.h"
#include "PSL/AbilitySystem/PSLAttributeSet.h"
#include "UObject/ConstructorHelpers.h"

APSLGameMode::APSLGameMode()
{
	AbilitySystemComponent = CreateDefaultSubobject<UPSLAbilitySystemComponent>("AbilitySystemComponent");

	AttributeSet = CreateDefaultSubobject<UPSLAttributeSet>("AttributeSet");
}

UAbilitySystemComponent* APSLGameMode::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void APSLGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}
