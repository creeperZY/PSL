// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PSL/PSLTypes/EquippedPoses.h"
#include "PSLAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PSL_API UPSLAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaTime) override;

private:
	UPROPERTY(BlueprintReadOnly, Category = Character, meta = (AllowPrivateAccess = "true"))
	class APSLCharacter* PSLCharacter;
	
	UPROPERTY(BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	float Speed;

	UPROPERTY(BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	bool bIsInAir;

	UPROPERTY(BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	bool bIsAccelerating;

	UPROPERTY(BlueprintReadOnly, Category = "Movement", meta = ( AllowPrivateAccess = "true" ))
	bool bWeaponEquipped;

	class AWeapon* EquippedWeapon;

	UPROPERTY(BlueprintReadOnly, Category = "Movement", meta = ( AllowPrivateAccess = "true" ))
	EEquippedPoseType EquippedPoseType;

	UPROPERTY(BlueprintReadOnly, Category = "Movement", meta = ( AllowPrivateAccess = "true" ))
	bool bIsCrouched;

	UPROPERTY(BlueprintReadOnly, Category = "Movement", meta = ( AllowPrivateAccess = "true" ))
	bool bAiming;
};
