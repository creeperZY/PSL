// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/GameMode.h"
#include "PSLGameMode.generated.h"

class APSLCharacter;
class UPSLWidgetController;
class UPSLUserWidget;
class UOverlayWidgetController;

UCLASS(minimalapi)
class APSLGameMode : public AGameMode,  public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	APSLGameMode();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() const { return AttributeSet; }

	void AddToCharacterWidgetControllerMap(ACharacter* Character, UAbilitySystemComponent* ASC, UAttributeSet* AS);
	
	
protected:
	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

private:
	UPROPERTY()
	ACharacter* CurrentCharacter;
	UPROPERTY()
	APlayerController* PlayerController;


public:
	
	FORCEINLINE void SetCurrentCharacter(ACharacter* Character) {CurrentCharacter = Character; }
	FORCEINLINE ACharacter* GetCurrentCharacter() const {return CurrentCharacter; }
	FORCEINLINE void SetPlayerController(APlayerController* Controller) {PlayerController = Controller; }
	FORCEINLINE APlayerController* GetPlayerController() const {return PlayerController; }
	
};



