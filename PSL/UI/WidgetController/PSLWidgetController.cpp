// Fill out your copyright notice in the Description page of Project Settings.


#include "PSLWidgetController.h"

void UPSLWidgetController::SetWidgetControllerParams(ACharacter* Char, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	Character = Char;
	AbilitySystemComponent = ASC;
	AttributeSet = AS;
}

void UPSLWidgetController::BroadcastInitialValues()
{
}

void UPSLWidgetController::BindCallbacksToDependencies()
{
}

