// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
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


private:
	UPROPERTY()
	class APSLCharacter* Character;

	UPROPERTY(EditAnywhere)
	float JumpZVelocity = 700.f;
	
	UPROPERTY(EditAnywhere)
	float BaseWalkSpeed = 500.f;

	UPROPERTY(EditAnywhere)
	float BaseWalkSpeedCrouched = 300.f;
	
	UPROPERTY(EditAnywhere)
	float AimWalkSpeed = 450.f;

	UPROPERTY(EditAnywhere)
	float AimWalkSpeedCrouched = 300.f;
	
	UPROPERTY(EditAnywhere)
	float JogSpeed = 700.f;


};
