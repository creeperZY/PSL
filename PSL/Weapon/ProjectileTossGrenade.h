// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectileGrenade.h"
#include "WeaponTypes.h"
#include "ProjectileTossGrenade.generated.h"

/**
 * 
 */
UCLASS()
class PSL_API AProjectileTossGrenade : public AProjectileGrenade
{
	GENERATED_BODY()
	
public:
#if WITH_EDITOR
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& Event) override;
#endif
		


	
public:
	virtual void ExplodeDamage() override;
	UPROPERTY(EditAnywhere)
	EGrenadeType GrenadeType = EGrenadeType::EWT_GrenadeFrag;
};
