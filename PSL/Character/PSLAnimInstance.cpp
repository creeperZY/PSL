// Fill out your copyright notice in the Description page of Project Settings.


#include "PSLAnimInstance.h"
#include "PSLCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "PSL/PSLTypes/CombatState.h"
#include "PSL/Weapon/Weapon.h"


void UPSLAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	
	PSLCharacter = Cast<APSLCharacter>(TryGetPawnOwner());
}

void UPSLAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);

	if (PSLCharacter == nullptr)
	{
		PSLCharacter = Cast<APSLCharacter>(TryGetPawnOwner());
	}

	if (PSLCharacter == nullptr) return;
	
	FVector Velocity = PSLCharacter->GetVelocity();
	Velocity.Z = 0.f;
	Speed = Velocity.Size();

	bIsInAir = PSLCharacter->GetCharacterMovement()->IsFalling();
	bIsAccelerating = PSLCharacter->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0.f ? true : false;
	bWeaponEquipped = PSLCharacter->IsWeaponEquipped();
	EquippedWeapon = PSLCharacter->GetEquippedWeapon();
	EquippedPoseType = PSLCharacter->GetEquippedPoseType();
	bIsCrouched = PSLCharacter->bIsCrouched;
	bAiming = PSLCharacter->IsAiming();
	TurningInPlace = PSLCharacter->GetTurningInPlace();
	//bRotateRootBone = BlasterCharacter->ShouldRotateRootBone();
	//bElimmed = BlasterCharacter->IsElimmed();

	// Offset Yaw for Strafing
	FRotator AimRotation = PSLCharacter->GetBaseAimRotation();
	FRotator MovementRotation = UKismetMathLibrary::MakeRotFromX(PSLCharacter->GetVelocity());
	FRotator DeltaRot = UKismetMathLibrary::NormalizedDeltaRotator(MovementRotation, AimRotation);
	DeltaRotation = FMath::RInterpTo(DeltaRotation, DeltaRot, DeltaTime, 6.f);
	YawOffset = DeltaRotation.Yaw;
	
	CharacterRotationLastFrame = CharacterRotation;
	CharacterRotation = PSLCharacter->GetActorRotation();
	const FRotator Delta = UKismetMathLibrary::NormalizedDeltaRotator(CharacterRotation, CharacterRotationLastFrame);
	const float Target = Delta.Yaw / DeltaTime;
	const float Interp = FMath::FInterpTo(Lean, Target, DeltaTime, 4.f);
	Lean = FMath::Clamp(Interp, -60.f, 60.f);

	AO_Yaw = PSLCharacter->GetAO_Yaw();
	AO_Pitch = PSLCharacter->GetAO_Pitch();
	
	if (bWeaponEquipped && EquippedWeapon && EquippedWeapon->GetWeaponMesh() && PSLCharacter->GetMesh())
	{
		LeftHandTransform = EquippedWeapon->GetWeaponMesh()->GetSocketTransform(FName("LeftHandSocket"), ERelativeTransformSpace::RTS_World);
		FVector OutPosition;
		FRotator OutRotation;
		PSLCharacter->GetMesh()->TransformToBoneSpace(FName("hand_r"), LeftHandTransform.GetLocation(), FRotator::ZeroRotator, OutPosition, OutRotation);
		LeftHandTransform.SetLocation(OutPosition);
		LeftHandTransform.SetRotation(FQuat(OutRotation));
		
		FTransform RightHandTransform = EquippedWeapon->GetWeaponMesh()->GetSocketTransform(FName("lowerarm_r"), ERelativeTransformSpace::RTS_World);
		FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(RightHandTransform.GetLocation(), RightHandTransform.GetLocation() + (RightHandTransform.GetLocation() - PSLCharacter->GetHitTarget()));
		RightHandRotation = FMath::RInterpTo(RightHandRotation, LookAtRotation, DeltaTime, 30.f);
		
		
		FTransform MuzzleTipTransform = EquippedWeapon->GetWeaponMesh()->GetSocketTransform(FName("MuzzleFlash"), ERelativeTransformSpace::RTS_World);
		FVector MuzzleX(FRotationMatrix(MuzzleTipTransform.GetRotation().Rotator()).GetUnitAxis(EAxis::X));
		//DrawDebugLine(GetWorld(), MuzzleTipTransform.GetLocation(), MuzzleTipTransform.GetLocation() + MuzzleX * 1000.f, FColor::Red);
		//DrawDebugLine(GetWorld(), MuzzleTipTransform.GetLocation(), PSLCharacter->GetHitTarget(), FColor::Orange);
	}

	bUseFABRIK = PSLCharacter->GetCombatState() == ECombatState::ECS_Unoccupied || PSLCharacter->GetCombatState() == ECombatState::ECS_Sprinting;
	//bool bFABRIKOverride = 	PSLCharacter->IsLocallyControlled() &&
	//	PSLCharacter->GetCombatState() != ECombatState::ECS_ThrowingGrenade &&
	//	PSLCharacter->bFinishedSwapping;
	//if (bFABRIKOverride)
	{
//		bUseFABRIK = !PSLCharacter->IsLocallyReloading();
	}
	bUseAimOffset =  PSLCharacter->GetCombatState() == ECombatState::ECS_Unoccupied && !bIsInAir && !PSLCharacter->IsSprinting();// && !PSLCharacter->GetDisableGameplay();
	bTransformRightHand = PSLCharacter->GetCombatState() == ECombatState::ECS_Unoccupied && !bIsInAir && !PSLCharacter->IsSprinting();// && !PSLCharacter->GetDisableGameplay();
	bSprinting = PSLCharacter->IsSprinting() && bIsAccelerating;
}
