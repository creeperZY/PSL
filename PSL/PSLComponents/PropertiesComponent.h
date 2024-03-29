// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "PSL/PSLAbilityGameplayTags.h"

#include "PropertiesComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PSL_API UPropertiesComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPropertiesComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	friend class APSLCharacter;
	friend class UCombatComponent;
	friend class UPSLAbilitySystemComponent;
	friend class UPSLAttributeSet;
	
protected:
	virtual void BeginPlay() override;

public:
	FGameplayTagContainer AbilityTagContainer;
	const FPSLAbilityGameplayTags& AbilityGameplayTags = FPSLAbilityGameplayTags::Get();

private:
	UPROPERTY()
	class APSLCharacter* Character;

	UPROPERTY(EditAnywhere)
	float JumpZVelocity = 700.f;
	UPROPERTY(EditAnywhere)
	float UnequippedWalkSpeed = 550.f;
	UPROPERTY(EditAnywhere)
	float UnequippedWalkSpeedCrouched = 300.f;
	UPROPERTY(EditAnywhere)
	float UnequippedSprintSpeed = 550.f;

	UPROPERTY(EditAnywhere)
	float EquippedWalkSpeed = 400.f;
	UPROPERTY(EditAnywhere)
	float EquippedWalkSpeedCrouched = 275.f;
	UPROPERTY(EditAnywhere)
	float EquippedAimWalkSpeed = 400.f;
	UPROPERTY(EditAnywhere)
	float EquippedAimWalkSpeedCrouched = 275.f;
	UPROPERTY(EditAnywhere)
	float EquippedSprintSpeed = 550.f;
	
};
