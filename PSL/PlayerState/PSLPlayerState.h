// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "PSLPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class PSL_API APSLPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	APSLPlayerState();
protected:
	
	UPROPERTY()
	TObjectPtr<class UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<class UAttributeSet> AttributeSet;
	
};
