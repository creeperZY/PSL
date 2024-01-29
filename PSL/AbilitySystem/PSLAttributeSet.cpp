// Fill out your copyright notice in the Description page of Project Settings.


#include "PSLAttributeSet.h"

UPSLAttributeSet::UPSLAttributeSet()
{
	InitHealth(50.f);
	InitMaxHealth(100.f);
}

void UPSLAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealth());
	}
}
