// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "PSL/PSLGameplayTags.h"

#include "AbilityComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PSL_API UAbilityComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UAbilityComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	friend class APSLCharacter;
	friend class UCombatComponent;
	
protected:
	virtual void BeginPlay() override;

public:
	FGameplayTagContainer AbilityTagContainer;
	const FPSLGameplayTags& GameplayTags = FPSLGameplayTags::Get();

private:
	UPROPERTY()
	class APSLCharacter* Character;

	UPROPERTY(EditAnywhere)
	float JumpZVelocity = 700.f;
	UPROPERTY(EditAnywhere)
	float UnequippedWalkSpeed = 500.f;
	UPROPERTY(EditAnywhere)
	float UnequippedWalkSpeedCrouched = 350.f;
	UPROPERTY(EditAnywhere)
	float UnequippedJogSpeed = 800.f;

	UPROPERTY(EditAnywhere)
	float EquippedWalkSpeed = 500.f;
	UPROPERTY(EditAnywhere)
	float EquippedWalkSpeedCrouched = 350.f;
	UPROPERTY(EditAnywhere)
	float EquippedAimWalkSpeed = 450.f;
	UPROPERTY(EditAnywhere)
	float EquippedAimWalkSpeedCrouched = 300.f;
	UPROPERTY(EditAnywhere)
	float EquippedJogSpeed = 700.f;
	
};
