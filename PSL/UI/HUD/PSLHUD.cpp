// Fill out your copyright notice in the Description page of Project Settings.


#include "PSLHUD.h"

#include "Blueprint/UserWidget.h"
#include "Components/VerticalBox.h"
#include "PSL/UI/Widget/PSLOverlayWidget.h"
#include "PSL/UI/Widget/PSLUserWidget.h"
#include "PSL/UI/WidgetController/OverlayWidgetController.h"

UOverlayWidgetController* APSLHUD::GetOverlayWidgetController(ACharacter* Character, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	UOverlayWidgetController* OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
	checkf(OverlayWidgetControllerClass, TEXT("Overlay Widget Controller Class uninitialized, please fill out BP_OverlayWidgetController"))
	OverlayWidgetController->SetWidgetControllerParams(Character, ASC, AS);
	OverlayWidgetController->BindCallbacksToDependencies();

	return OverlayWidgetController;
}

void APSLHUD::InitOverlay(ACharacter* Character, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	checkf(OverlayWidgetClass, TEXT("Overlay Widget Class uninitialized, please fill out BP_PSLHUD"));
	checkf(OverlayWidgetControllerClass, TEXT("Overlay Widget Controller Class uninitialized, please fill out BP_OverlayWidgetController"))
	
	/*if (!OverlayWidget)
	{
		UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
		OverlayWidget = Cast<UPSLOverlayWidget>(Widget);
	}
	
	UOverlayWidgetController* WidgetController = GetOverlayWidgetController(Character, ASC, AS);
	OverlayWidget->SetWidgetController(WidgetController);
	WidgetController->BroadcastInitialValues();
	// should also broadcast weapon ammo and etc. 

	OverlayWidget->AddToViewport();*/
}

void APSLHUD::AddToCharacterWidgetControllerMap(ACharacter* Character, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	//UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	//OverlayWidget = Cast<UPSLUserWidget>(Widget);
	
	if (!CharacterWidgetControllerMap.Contains(Character))
	{
		if (!OverlayWidget)
		{
			UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
			OverlayWidget = Cast<UPSLOverlayWidget>(Widget);
			Widget->AddToViewport();
		}
		
		UOverlayWidgetController* WidgetController = GetOverlayWidgetController(Character, ASC, AS);
		
		CharacterWidgetControllerMap.Add(Character, WidgetController);
		UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), CharacterStateWidgetClass);
		UPSLUserWidget* CharacterStateWidget = Cast<UPSLUserWidget>(Widget);
		CharacterStateWidget->SetWidgetController(WidgetController);
		CharacterUserWidgetMap.Add(Character, CharacterStateWidget);
		WidgetController->BroadcastInitialValues();
		OverlayWidget->CharacterStateVerticalBox->AddChild(Widget);
		Widget->AddToViewport();
		
	}
}


