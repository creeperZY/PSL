// Fill out your copyright notice in the Description page of Project Settings.


#include "PSLAnimInstance.h"
#include "PSLCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"


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
	EquippedPoseType = PSLCharacter->GetEquippedPoseType();
	bIsCrouched = PSLCharacter->bIsCrouched;
	bAiming = PSLCharacter->IsAiming();
}
