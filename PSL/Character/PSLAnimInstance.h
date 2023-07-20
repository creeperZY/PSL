// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PSL/PSLTypes/EquippedPoses.h"
#include "PSL/PSLTypes/TurningInPlace.h"
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

	UPROPERTY(BlueprintReadOnly, Category = "Movement", meta = ( AllowPrivateAccess = "true" ))
	float YawOffset;

	UPROPERTY(BlueprintReadOnly, Category = "Movement", meta = ( AllowPrivateAccess = "true" ))
	float Lean;

	
	FRotator CharacterRotationLastFrame;
	FRotator CharacterRotation;
	FRotator DeltaRotation; //this can fix blendspace interp time, walk back jerk problem

	UPROPERTY(BlueprintReadOnly, Category = "Movement", meta = ( AllowPrivateAccess = "true" ))
	float AO_Yaw;

	UPROPERTY(BlueprintReadOnly, Category = "Movement", meta = ( AllowPrivateAccess = "true" ))
	float AO_Pitch;
	
	UPROPERTY(BlueprintReadOnly, Category = "Movement", meta = ( AllowPrivateAccess = "true" ))
	ETurningInPlace TurningInPlace;
	
	UPROPERTY(BlueprintReadOnly, Category = "Movement", meta = ( AllowPrivateAccess = "true" ))
	FTransform LeftHandTransform;

	UPROPERTY(BlueprintReadOnly, Category = "Movement", meta = ( AllowPrivateAccess = "true" ))
	FRotator RightHandRotation;
	
	//UPROPERTY(BlueprintReadOnly, Category = "Movement", meta = ( AllowPrivateAccess = "true" ))
	//bool bLocallyControlled;

	//UPROPERTY(BlueprintReadOnly, Category = "Movement", meta = ( AllowPrivateAccess = "true" ))
	//bool bRotateRootBone;

	//UPROPERTY(BlueprintReadOnly, Category = "Movement", meta = ( AllowPrivateAccess = "true" ))
	//bool bElimmed;

	UPROPERTY(BlueprintReadOnly, Category = "Movement", meta = ( AllowPrivateAccess = "true" ))
	bool bUseFABRIK;

	UPROPERTY(BlueprintReadOnly, Category = "Movement", meta = ( AllowPrivateAccess = "true" ))
	bool bUseAimOffset;

	UPROPERTY(BlueprintReadOnly, Category = "Movement", meta = ( AllowPrivateAccess = "true" ))
	bool bTransformRightHand;
};
