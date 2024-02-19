// Copyright Epic Games, Inc. All Rights Reserved.

#include "PSLGameMode.h"
#include "PSL/AbilitySystem/PSLAbilitySystemComponent.h"
#include "PSL/AbilitySystem/PSLAttributeSet.h"
#include "PSL/PlayerController/PSLPlayerController.h"
#include "PSL/UI/HUD/PSLHUD.h"
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


void APSLGameMode::AddToCharacterWidgetControllerMap(ACharacter* Character, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	APSLPlayerController* PSLPlayerController = Cast<APSLPlayerController>(PlayerController);
	if(PSLPlayerController)
	{
		APSLHUD* PSLHUD = Cast<APSLHUD>(PSLPlayerController->GetHUD());
		if (PSLHUD)
		{
			PSLHUD->AddToCharacterWidgetControllerMap(Character, ASC, AS);
		}
	}

}

void APSLGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}
