// Fill out your copyright notice in the Description page of Project Settings.


#include "PSLWidgetController.h"

void UPSLWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& WCParams)
{
	GameMode = WCParams.GameMode;
	PlayerController = WCParams.PlayerController;
	PlayerState = WCParams.PlayerState;
	AbilitySystemComponent = WCParams.AbilitySystemComponent;
	AttributeSet = WCParams.AttributeSet;
}
