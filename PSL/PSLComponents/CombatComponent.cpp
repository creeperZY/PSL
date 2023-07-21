// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatComponent.h"

#include "AbilityComponent.h"
#include "Camera/CameraComponent.h"
#include "PSL/EasyMacros.h"
#include "PSL/Weapon/Weapon.h"
#include "PSL/Character/PSLCharacter.h"
#include "Engine/SkeletalMeshSocket.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

UCombatComponent::UCombatComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void UCombatComponent::BeginPlay()
{
	Super::BeginPlay();
	
}


void UCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UCombatComponent::EquipWeapon(AWeapon* WeaponToEquip)
{
	if (Character == nullptr || WeaponToEquip == nullptr) return;
	if (CombatState != ECombatState::ECS_Unoccupied) return;

	if (FirstWeapon != nullptr && SecondWeapon == nullptr)
	{
		EquipWeaponToBack2(WeaponToEquip);
	}
	else if (FirstWeapon == nullptr)
	{
		EquipWeaponToRightHand(WeaponToEquip);
		FirstWeapon = WeaponToEquip;
	}
	else if (FirstWeapon != nullptr && SecondWeapon != nullptr)
	{
		if (EquippedWeapon)
		{
			DropEquippedWeapon();
			if (EquippedWeapon == FirstWeapon) FirstWeapon = WeaponToEquip;
			if (EquippedWeapon == SecondWeapon) SecondWeapon = WeaponToEquip;
			EquipWeaponToRightHand(WeaponToEquip);
		}
		else // drop first weapon, of course we can drop second 
		{
			EquippedWeapon = FirstWeapon;
			DropEquippedWeapon();
			FirstWeapon = nullptr;
			EquipWeaponToBack1(WeaponToEquip);
			FirstWeapon = WeaponToEquip;
			EquippedWeapon = nullptr;
		}
	}
	if (EquippedWeapon)
	{
		Character->GetCharacterMovement()->bOrientRotationToMovement = false;
		Character->bUseControllerRotationYaw = true;
	}
	else
	{
		Character->GetCharacterMovement()->bOrientRotationToMovement = true;
		Character->bUseControllerRotationYaw = false;
	}

}

void UCombatComponent::HolsterWeapon()
{
	if (EquippedWeapon && EquippedWeapon == FirstWeapon)
	{
		AttachActorToBack1(EquippedWeapon);
		EquippedWeapon = nullptr;
	}
	else if (EquippedWeapon && EquippedWeapon == SecondWeapon)
	{
		AttachActorToBack2(EquippedWeapon);
		EquippedWeapon = nullptr;
	}
	Character->GetCharacterMovement()->bOrientRotationToMovement = true;
	Character->bUseControllerRotationYaw = false;
}

void UCombatComponent::EquipWeaponToRightHand(AWeapon* WeaponToEquip)
{
	if (WeaponToEquip == nullptr) return;
	//DropEquippedWeapon();
	EquippedWeapon = WeaponToEquip;
	EquippedWeapon->SetOwner(Character);
	EquippedWeapon->SetWeaponState(EWeaponState::EWS_Equipped);
	AttachActorToRightHand(WeaponToEquip);
	PlayEquipWeaponSound(WeaponToEquip);
	ReloadEmptyWeapon();
	//EquippedWeapon->EnableCustomDepth(false);
	//Character->GetCharacterMovement()->bOrientRotationToMovement = false;
	//Character->bUseControllerRotationYaw = true;
}

void UCombatComponent::EquipWeaponToBack1(AWeapon* WeaponToEquip)
{
	if (WeaponToEquip == nullptr) return; 
	FirstWeapon = WeaponToEquip;
	FirstWeapon->SetOwner(Character);
	FirstWeapon->SetWeaponState(EWeaponState::EWS_EquippedBack);
	AttachActorToBack1(WeaponToEquip);
	PlayEquipWeaponSound(WeaponToEquip);
}


void UCombatComponent::EquipWeaponToBack2(AWeapon* WeaponToEquip)
{
	if (WeaponToEquip == nullptr) return; 
	SecondWeapon = WeaponToEquip;
	SecondWeapon->SetOwner(Character);
	SecondWeapon->SetWeaponState(EWeaponState::EWS_EquippedBack);
	AttachActorToBack2(WeaponToEquip);
	PlayEquipWeaponSound(WeaponToEquip);
}

void UCombatComponent::EquipFirstWeapon()
{
	if (FirstWeapon)
	{
		if (EquippedWeapon == FirstWeapon && EquippedWeapon)
		{
			HolsterWeapon();
		}
		else if (EquippedWeapon == SecondWeapon && EquippedWeapon) // need swap animation
		{
			EquipWeaponToBack2(EquippedWeapon);
			EquipWeaponToRightHand(FirstWeapon);
		}
		else
		{
			EquipWeaponToRightHand(FirstWeapon); // on back
		}
	}
}

void UCombatComponent::EquipSecondWeapon()
{
	if (SecondWeapon)
	{
		if (EquippedWeapon == SecondWeapon && EquippedWeapon)
		{
			HolsterWeapon();
		}
		else if (EquippedWeapon == FirstWeapon && EquippedWeapon)
		{
			EquipWeaponToBack1(EquippedWeapon);
			EquipWeaponToRightHand(SecondWeapon);
		}
		else
		{
			EquipWeaponToRightHand(SecondWeapon);
		}
	}
}


void UCombatComponent::DropEquippedWeapon()
{
	if (Character == nullptr || EquippedWeapon == nullptr) return;
	EquippedWeapon->Dropped();
	EquippedWeapon->GetWeaponMesh()->AddImpulse(Character->GetActorForwardVector() * EquippedWeapon->DropFactor);
	if (EquippedWeapon == FirstWeapon) FirstWeapon = nullptr;
	if (EquippedWeapon == SecondWeapon) SecondWeapon = nullptr;
	EquippedWeapon = nullptr;

	Character->GetCharacterMovement()->bOrientRotationToMovement = true;
	Character->bUseControllerRotationYaw = false;
}


void UCombatComponent::AttachActorToLeftHand(AActor* ActorToAttach)
{
	//no use for now
}

void UCombatComponent::AttachActorToRightHand(AActor* ActorToAttach)
{
	if (Character == nullptr || Character->GetMesh() == nullptr || ActorToAttach == nullptr) return;
	const USkeletalMeshSocket* HandSocket = Character->GetMesh()->GetSocketByName(FName("RightHandSocket"));
	if (HandSocket)
	{
		HandSocket->AttachActor(ActorToAttach, Character->GetMesh());
	}
}

void UCombatComponent::AttachActorToBack1(AActor* ActorToAttach)
{
	if (Character == nullptr || Character->GetMesh() == nullptr || ActorToAttach == nullptr) return;
	const USkeletalMeshSocket* BackpackSocket = Character->GetMesh()->GetSocketByName(FName("BackSocket1"));
	if (BackpackSocket)
	{
		BackpackSocket->AttachActor(ActorToAttach, Character->GetMesh());
	}
}

void UCombatComponent::AttachActorToBack2(AActor* ActorToAttach)
{
	if (Character == nullptr || Character->GetMesh() == nullptr || ActorToAttach == nullptr) return;
	const USkeletalMeshSocket* BackpackSocket = Character->GetMesh()->GetSocketByName(FName("BackSocket2"));
	if (BackpackSocket)
	{
		BackpackSocket->AttachActor(ActorToAttach, Character->GetMesh());
	}
}

void UCombatComponent::PlayEquipWeaponSound(AWeapon* WeaponToEquip)
{
	if(Character && WeaponToEquip && WeaponToEquip->EquipSound)
	{
		UGameplayStatics::PlaySoundAtLocation(
			this,
			WeaponToEquip->EquipSound,
			Character->GetActorLocation()
		);
	}
}

void UCombatComponent::SwapWeapons()
{
	/*if (CombatState != ECombatState::ECS_Unoccupied || Character == nullptr) return;
	
	//Character->PlaySwapMontage();
	//Character->bFinishedSwapping = false;
	CombatState = ECombatState::ECS_SwappingWeapons;
	FinishSwapAttachWeapons();
	FinishSwap();*/
	//if (SecondaryWeapon) SecondaryWeapon->EnableCustomDepth(false);
}

void UCombatComponent::FinishSwap()
{
	if (Character)
	{
		CombatState = ECombatState::ECS_Unoccupied;
	}
	//if (Character) Character->bFinishedSwapping = true;
	//if (SecondaryWeapon) SecondaryWeapon->EnableCustomDepth(true);
}

void UCombatComponent::FinishSwapAttachWeapons()
{
	/*if (Character == nullptr) return;
	PlayEquipWeaponSound(SecondaryWeapon);
	
	AWeapon* TempWeapon = EquippedWeapon;
	EquippedWeapon = SecondaryWeapon;
	SecondaryWeapon = TempWeapon;

	EquippedWeapon->SetWeaponState(EWeaponState::EWS_Equipped);
	AttachActorToRightHand(EquippedWeapon);
	EquippedWeapon->SetHUDAmmo();

	SecondaryWeapon->SetWeaponState(EWeaponState::EWS_EquippedSecondary);
	AttachActorToBack(SecondaryWeapon);*/
}

void UCombatComponent::SetAiming(bool bIsAiming)
{
	if (Character == nullptr || EquippedWeapon == nullptr) return;
	bAiming = bIsAiming;
	
	if (Character && Character->GetAbility())
	{
		Character->GetCharacterMovement()->MaxWalkSpeed = bIsAiming ? Character->GetAbility()->EquippedAimWalkSpeed : Character->GetAbility()->EquippedWalkSpeed;
		Character->GetCharacterMovement()->MaxWalkSpeedCrouched = bIsAiming ? Character->GetAbility()->EquippedAimWalkSpeedCrouched : Character->GetAbility()->UnequippedWalkSpeedCrouched;
	}
}

void UCombatComponent::ThrowGrenadeFinished()
{
}

void UCombatComponent::ThrowGrenade()
{
}

bool UCombatComponent::ShouldSwapWeapons()
{
	return (EquippedWeapon != nullptr && SecondWeapon != nullptr);
}


void UCombatComponent::ReloadEmptyWeapon()
{
}

void UCombatComponent::FinishReloading()
{
}


