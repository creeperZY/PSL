// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "PSLWidgetController.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;
class AGameMode;
class APSLCharacterBase;

/**
 * 
 */
UCLASS()
class PSL_API UPSLWidgetController : public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void SetWidgetControllerParams(
		ACharacter* Char,
		UAbilitySystemComponent* ASC,
		UAttributeSet* AS);
	virtual void BroadcastInitialValues();
	virtual void BindCallbacksToDependencies();
	
protected:

	UPROPERTY(BlueprintReadOnly, Category="WidgetController")
	TObjectPtr<ACharacter> Character = nullptr;

	UPROPERTY(BlueprintReadOnly, Category="WidgetController")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent = nullptr;

	UPROPERTY(BlueprintReadOnly, Category="WidgetController")
	TObjectPtr<UAttributeSet> AttributeSet = nullptr;
};
