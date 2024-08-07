// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatComponent.h"

#include "Camera/CameraComponent.h"
#include "PSL/EasyMacros.h"
#include "PSL/Weapon/Weapon.h"
#include "PSL/Character/PSLCharacter.h"
#include "Engine/SkeletalMeshSocket.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "PSL/PSL.h"
#include "PSL/Weapon/ProjectileTossGrenade.h"
#include "Sound/SoundCue.h"

UCombatComponent::UCombatComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UCombatComponent::BeginPlay()
{
	Super::BeginPlay();
}


void UCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (Character)
	{
		FHitResult HitResult;
		TraceUnderCrosshairs(HitResult);
		if(HitResult.bBlockingHit) HitTarget = HitResult.ImpactPoint;
		else HitTarget = HitResult.TraceEnd;
		DRAW_SPHERE_AT_LOCATION(HitTarget)
	}

	RecoilRecovery(DeltaTime);
}

void UCombatComponent::BindCallbacksToDependencies()
{
	
}

void UCombatComponent::EquipWeaponToCorrectSlot(AWeapon* WeaponToEquip){
	if (WeaponToEquip == nullptr) return;
	if (!Character->bUseMocapAnimations) return;

	if (WeaponToEquip->GetEquippedPoseType() == EEquippedPoseType::EEPT_RiflePose) {
		if (FirstWeapon) {
			//drop
			FirstWeapon->Dropped();
			FirstWeapon = nullptr;
		}
		EquipWeaponToSlot1(WeaponToEquip);
		
	} else if (WeaponToEquip->GetEquippedPoseType() == EEquippedPoseType::EEPT_PistolPose) {
		if (SecondWeapon) {
			//drop
			SecondWeapon->Dropped();
			SecondWeapon = nullptr;
		}
		EquipWeaponToSlot2(WeaponToEquip);
		
	}
	
}


void UCombatComponent::PickupWeapon(AWeapon* WeaponToEquip)
{
	if (Character == nullptr || WeaponToEquip == nullptr) return;
	if (CombatState != ECombatState::ECS_Unoccupied) return;
	if (WeaponToEquip == nullptr) return;
	
	EquipWeapon(WeaponToEquip);

}

void UCombatComponent::HolsterWeapon()
{
	if (EquippedWeapon && EquippedWeapon == FirstWeapon)
	{
		EquipWeaponToSlot1(EquippedWeapon);
		EquippedWeapon = nullptr;
	}
	else if (EquippedWeapon && EquippedWeapon == SecondWeapon)
	{
		EquipWeaponToSlot2(EquippedWeapon);
		EquippedWeapon = nullptr;
	}
	Character->GetCharacterMovement()->bOrientRotationToMovement = true;
	Character->bUseControllerRotationYaw = false;
	
	//Character->GetCharacterMovement()->MaxWalkSpeed = Character->GetProperties()->UnequippedWalkSpeed;
	//Character->GetCharacterMovement()->MaxWalkSpeedCrouched = Character->GetProperties()->UnequippedWalkSpeedCrouched;
}

void UCombatComponent::EquipWeaponToRightHand(AWeapon* WeaponToEquip)
{
	if (WeaponToEquip == nullptr) return;
	EquippedWeapon = WeaponToEquip;
	EquippedWeapon->SetOwner(Character);
	EquippedWeapon->SetWeaponState(EWeaponState::EWS_Equipped);
	AttachActorToRightHand(WeaponToEquip);
	PlayEquipWeaponSound(WeaponToEquip);
	ReloadEmptyWeapon();
	
	//Character->GetCharacterMovement()->MaxWalkSpeed = Character->GetProperties()->EquippedWalkSpeed;
	//Character->GetCharacterMovement()->MaxWalkSpeedCrouched = Character->GetProperties()->EquippedWalkSpeedCrouched;
}

void UCombatComponent::EquipWeaponToSlot1(AWeapon* WeaponToEquip)
{
	if (WeaponToEquip == nullptr) return; 
	FirstWeapon = WeaponToEquip;
	FirstWeapon->SetOwner(Character);
	FirstWeapon->SetWeaponState(EWeaponState::EWS_EquippedBack);
	switch (WeaponToEquip->GetEquippedPoseType())
	{
	case EEquippedPoseType::EEPT_RiflePose:
		AttachActorToBack1(WeaponToEquip);
		break;
	case EEquippedPoseType::EEPT_PistolPose:
		AttachActorToPelvis1(WeaponToEquip);
		break;
	}
	//PlayEquipWeaponSound(WeaponToEquip);
}


void UCombatComponent::EquipWeaponToSlot2(AWeapon* WeaponToEquip)
{
	if (WeaponToEquip == nullptr) return; 
	SecondWeapon = WeaponToEquip;
	SecondWeapon->SetOwner(Character);
	SecondWeapon->SetWeaponState(EWeaponState::EWS_EquippedBack);
	switch (WeaponToEquip->GetEquippedPoseType())
	{
	case EEquippedPoseType::EEPT_RiflePose:
		AttachActorToBack2(WeaponToEquip);
		break;
	case EEquippedPoseType::EEPT_PistolPose:
		AttachActorToPelvis2(WeaponToEquip);
		break;
	}
	//PlayEquipWeaponSound(WeaponToEquip);
}


void UCombatComponent::DropEquippedWeapon()
{
	if (Character == nullptr || EquippedWeapon == nullptr) return;
	if (CombatState != ECombatState::ECS_Unoccupied && CombatState != ECombatState::ECS_Sprinting) return;
	EquippedWeapon->Dropped();
	
	EquippedWeapon->GetWeaponMesh()->AddImpulse(Character->GetFollowCamera()->GetComponentRotation().Vector() * EquippedWeapon->DropFactor);
	if (EquippedWeapon == FirstWeapon) FirstWeapon = nullptr;
	if (EquippedWeapon == SecondWeapon) SecondWeapon = nullptr;
	EquippedWeapon = nullptr;

	Character->GetCharacterMovement()->bOrientRotationToMovement = true;
	Character->bUseControllerRotationYaw = false;

	if (Character->bUseMocapAnimations) {
		if (FirstWeapon) {
			EquipFirstWeapon();
		}
		else if (SecondWeapon) {
			EquipSecondWeapon();
		}
	}
}


void UCombatComponent::AttachActorToLeftHand(AActor* ActorToAttach)
{
	//no use for now
}

void UCombatComponent::AttachActorToRightHand(AActor* ActorToAttach)
{
	if (Character == nullptr || Character->GetMesh() == nullptr || ActorToAttach == nullptr) return;

	const USkeletalMeshSocket* HandSocket = nullptr;
	
	AWeapon* AttachedWeapon = Cast<AWeapon>(ActorToAttach);
	if(AttachedWeapon)
	{
		switch (AttachedWeapon->GetEquippedPoseType())
		{
		case EEquippedPoseType::EEPT_PistolPose:
			HandSocket = Character->GetMesh()->GetSocketByName(FName("RightHandSocketPistol"));
			break;
		case EEquippedPoseType::EEPT_RiflePose:
			HandSocket = Character->GetMesh()->GetSocketByName(FName("RightHandSocketRifle"));
			break;
		case EEquippedPoseType::EEPT_MeleePose:
			HandSocket = Character->GetMesh()->GetSocketByName(FName("RightHandSocketMelee"));
			break;
		}
	}
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

void UCombatComponent::AttachActorToPelvis1(AActor* ActorToAttach)
{
	if (Character == nullptr || Character->GetMesh() == nullptr || ActorToAttach == nullptr) return;
	const USkeletalMeshSocket* BackpackSocket = Character->GetMesh()->GetSocketByName(FName("PelvisSocket1"));
	if (BackpackSocket)
	{
		BackpackSocket->AttachActor(ActorToAttach, Character->GetMesh());
	}
}

void UCombatComponent::AttachActorToPelvis2(AActor* ActorToAttach)
{
	if (Character == nullptr || Character->GetMesh() == nullptr || ActorToAttach == nullptr) return;
	const USkeletalMeshSocket* BackpackSocket = Character->GetMesh()->GetSocketByName(FName("PelvisSocket2"));
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

void UCombatComponent::PlayReloadEjectSound()
{
	if(Character && Character->IsWeaponEquipped() && EquippedWeapon->ReloadEjectSound)
	{
		UGameplayStatics::PlaySoundAtLocation(
			this,
			EquippedWeapon->ReloadEjectSound,
			EquippedWeapon->GetActorLocation()
		);
	}
}

void UCombatComponent::PlayReloadInsertSound()
{
	if(Character && Character->IsWeaponEquipped() && EquippedWeapon->ReloadInsertSound)
	{
		UGameplayStatics::PlaySoundAtLocation(
			this,
			EquippedWeapon->ReloadInsertSound,
			EquippedWeapon->GetActorLocation()
		);
	}
}

void UCombatComponent::PlayReloadSliderSound()
{
	
	if(Character && Character->IsWeaponEquipped() && EquippedWeapon->ReloadSliderSound)
	{
		UGameplayStatics::PlaySoundAtLocation(
			this,
			EquippedWeapon->ReloadSliderSound,
			EquippedWeapon->GetActorLocation()
		);
		PlayReloadSliderAnimation();
	}
	
}

void UCombatComponent::PlayReloadSliderAnimation()
{
	if(Character && Character->IsWeaponEquipped())
	{
		EquippedWeapon->PlayReloadSliderAninmation();
	}
}


void UCombatComponent::EquipFirstWeapon()
{

	if (FirstWeapon)
	{
		if (Character->bUseMocapAnimations){
			if (EquippedWeapon == FirstWeapon && EquippedWeapon)
			{
				UnequipWeapon(EquippedWeapon);
			}
			else
			{
				EquipWeapon(FirstWeapon);
			}
		} else {
			if (EquippedWeapon == FirstWeapon && EquippedWeapon)
			{
				UnequipWeapon(EquippedWeapon);
			}
			else
			{
				EquipWeapon(FirstWeapon);
			}
		}
	}
}


void UCombatComponent::EquipSecondWeapon()
{
	if (SecondWeapon)
	{
		if (Character->bUseMocapAnimations){
			if (EquippedWeapon == SecondWeapon && EquippedWeapon)
			{
				UnequipWeapon(EquippedWeapon);
			}
			else
			{
				EquipWeapon(SecondWeapon);
			}
		}else{
			if (EquippedWeapon == SecondWeapon && EquippedWeapon)
			{
				UnequipWeapon(EquippedWeapon);
			}
			else
			{
				EquipWeapon(SecondWeapon);
			}
		}
	}

}


void UCombatComponent::FinishSwapAttachWeapons()
{
	// Swap Weapons
	if (TempWeapon == FirstWeapon && TempWeapon)
	{
		EquipWeaponToSlot2(SecondWeapon);
		EquipWeaponToRightHand(FirstWeapon);
	}
	else if (TempWeapon == SecondWeapon && TempWeapon)
	{
		EquipWeaponToSlot1(FirstWeapon);
		EquipWeaponToRightHand(SecondWeapon);
	}
	
	// Pickup Weapon
	else if (FirstWeapon != nullptr && SecondWeapon == nullptr)
	{
		EquipWeaponToSlot1(FirstWeapon);
		EquipWeaponToRightHand(TempWeapon);
		SecondWeapon = TempWeapon; 
	}
	else if (FirstWeapon == nullptr) // X
	{
		EquipWeaponToSlot2(SecondWeapon);
		EquipWeaponToRightHand(TempWeapon);
		FirstWeapon = TempWeapon;
	}
	else if (FirstWeapon != nullptr && SecondWeapon != nullptr)
	{
		if (EquippedWeapon)
		{
			DropEquippedWeapon();
			if (EquippedWeapon == FirstWeapon) FirstWeapon = TempWeapon;
			if (EquippedWeapon == SecondWeapon) SecondWeapon = TempWeapon;
			EquipWeaponToRightHand(TempWeapon);
		}
		else // drop first weapon, of course we can drop second or UI hint equip one
		{
			EquippedWeapon = FirstWeapon;
			DropEquippedWeapon();
			FirstWeapon = nullptr;
			EquipWeaponToSlot1(TempWeapon);
			FirstWeapon = TempWeapon;
			EquippedWeapon = nullptr;
		}
	}
	
}

void UCombatComponent::SwapUnequippedAttach()
{
	if (!FirstWeapon || !SecondWeapon) return;
	if (!Character->bUseMocapAnimations) return;
	if (EquippedWeapon == FirstWeapon)
	{
		EquipWeaponToSlot1(FirstWeapon);
		//EquipWeaponToRightHand(FirstWeapon);
	}
	else if (EquippedWeapon == SecondWeapon)
	{
		EquipWeaponToSlot2(SecondWeapon);
		//EquipWeaponToRightHand(SecondWeapon);
	}
}

void UCombatComponent::SwapEquippedAttach()
{
	if (!FirstWeapon || !SecondWeapon) return;
	if (!Character->bUseMocapAnimations) return;
	if (EquippedWeapon == FirstWeapon)
	{
		//EquipWeaponToSlot2(SecondWeapon);
		EquipWeaponToRightHand(SecondWeapon);
	}
	else if (EquippedWeapon == SecondWeapon)
	{
		//EquipWeaponToSlot1(FirstWeapon);
		EquipWeaponToRightHand(FirstWeapon);
	}
}


void UCombatComponent::EquippedAttach(){
	if (Character->bUseMocapAnimations) {
		if (TempWeapon == FirstWeapon && TempWeapon)
		{
			EquipWeaponToRightHand(FirstWeapon);
		}
		else if (TempWeapon == SecondWeapon && TempWeapon)
		{
			EquipWeaponToRightHand(SecondWeapon);
		}
	}
}

void UCombatComponent::UnequippedAttach(){
	if (Character->bUseMocapAnimations) {
		if (EquippedWeapon == FirstWeapon && EquippedWeapon)
		{
			EquipWeaponToSlot1(FirstWeapon);
		}
		else if (EquippedWeapon == SecondWeapon && EquippedWeapon)
		{
			EquipWeaponToSlot2(SecondWeapon);
		}
	}
}


void UCombatComponent::EquipWeapon(AWeapon* WeaponToEquip)
{
	if (CombatState != ECombatState::ECS_Unoccupied || Character == nullptr) return;
	if (WeaponToEquip == nullptr) return;	
	TempWeapon = WeaponToEquip;
	if (Character->bUseMocapAnimations) {
		EquipWeaponToCorrectSlot(WeaponToEquip);
	}
	CombatState = ECombatState::ECS_SwappingWeapons;
	Character->PlayEquipMontage(WeaponToEquip);
}

void UCombatComponent::SwapWeapon(AWeapon* WeaponToEquip)
{
	if (CombatState != ECombatState::ECS_Unoccupied || Character == nullptr) return;
	if (WeaponToEquip == nullptr) return;
	if (!Character->bUseMocapAnimations) return;

	TempWeapon = WeaponToEquip;
	CombatState = ECombatState::ECS_SwappingWeapons;
	Character->PlaySwapMontage(WeaponToEquip);
	
}

void UCombatComponent::FinishEquip()
{
	if (Character)
	{
		CombatState = ECombatState::ECS_Unoccupied;
	}
}

void UCombatComponent::UnequipWeapon(AWeapon* WeaponToUnequip)
{
	if (CombatState != ECombatState::ECS_Unoccupied || Character == nullptr) return;
	
	CombatState = ECombatState::ECS_SwappingWeapons;
	Character->PlayUnequipMontage(WeaponToUnequip);
	
}

void UCombatComponent::FinishUnequipWeapon()
{
	if (Character)
	{
		HolsterWeapon();
	}
	CombatState = ECombatState::ECS_Unoccupied;
}



void UCombatComponent::FireButtonPressed(bool bPressed)
{
	bFireButtonPressed = bPressed;

	if (bFireButtonPressed)
	{
		Fire();
	}
}


void UCombatComponent::SetAiming(bool bIsAiming)
{
	if (Character == nullptr || EquippedWeapon == nullptr) return;
	bAiming = bIsAiming;
	
	if (Character && Character->GetProperties())
	{
		Character->GetCharacterMovement()->MaxWalkSpeed = bIsAiming ? Character->GetProperties()->EquippedAimWalkSpeed : Character->GetProperties()->EquippedWalkSpeed;
		Character->GetCharacterMovement()->MaxWalkSpeedCrouched = bIsAiming ? Character->GetProperties()->EquippedAimWalkSpeedCrouched : Character->GetProperties()->UnequippedWalkSpeedCrouched;
	}
}

void UCombatComponent::TraceUnderCrosshairs(FHitResult& TraceHitResult)
{
	FVector2d ViewPortSize;
	if(GEngine && GEngine->GameViewport)
	{
		GEngine->GameViewport->GetViewportSize(ViewPortSize);
	}

	FVector2d CrossHairLocation(ViewPortSize.X / 2.f, ViewPortSize.Y / 2.f);
	FVector CrosshairWorldPosition;
	FVector CrosshairWorldDirection;
	bool bScreenToWorld = UGameplayStatics::DeprojectScreenToWorld(
		UGameplayStatics::GetPlayerController(this, 0),
		CrossHairLocation,
		CrosshairWorldPosition,
		CrosshairWorldDirection
	);

	if(bScreenToWorld)
	{
		FVector Start = CrosshairWorldPosition;

		if (Character)
		{
			float DistanceToCharacter = (Character->GetActorLocation() - Start).Size();
			Start += CrosshairWorldDirection * (DistanceToCharacter + 50.f);
			DrawDebugSphere(GetWorld(), Start, 2.f, 12, FColor::Orange, false);
		}
		
		FVector End = Start + CrosshairWorldDirection * TRACE_LENGTH;
		

		
		if (Character && Character->GetCombat())
		{
			FCollisionQueryParams Params;
			Params.AddIgnoredActor(Character);
			if (Character->GetCombat()->FirstWeapon)
				Params.AddIgnoredActor(Character->GetCombat()->FirstWeapon);
			if (Character->GetCombat()->SecondWeapon)
				Params.AddIgnoredActor(Character->GetCombat()->SecondWeapon);
			Params.AddIgnoredActor(Character->GetEquippedWeapon());
			GetWorld()->LineTraceSingleByChannel(
				TraceHitResult,
				Start,
				End,
				ECollisionChannel::ECC_Visibility
				,Params
			);

			// weapon down when near wall
			if (Character->GetEquippedWeapon())
			{
				const USkeletalMeshSocket* HandSocket = Character->GetMesh()->GetSocketByName(FName("RightHandSocketRifle"));
				const FTransform HandSocketTransform = HandSocket->GetSocketTransform(Character->GetMesh());
				
				const USkeletalMeshSocket* AmmoEjectSocket = Character->GetEquippedWeapon()->GetWeaponMesh()->GetSocketByName(FName("AmmoEject"));
				const FTransform AmmoEjectSocketTransform = AmmoEjectSocket->GetSocketTransform(Character->GetEquippedWeapon()->GetWeaponMesh());

				const USkeletalMeshSocket* MuzzleFlashSocket = Character->GetEquippedWeapon()->GetWeaponMesh()->GetSocketByName(FName("MuzzleFlash"));
				const FTransform MuzzleFlashSocketTransform = MuzzleFlashSocket->GetSocketTransform(Character->GetEquippedWeapon()->GetWeaponMesh());


				FVector NearStart = MuzzleFlashSocketTransform.GetLocation();
				FVector NearEnd = NearStart + (1.0f * Character->GetActorForwardVector()) * (MuzzleFlashSocketTransform.GetLocation() - AmmoEjectSocketTransform.GetLocation()).Size();
				
				DrawDebugSphere(GetWorld(), NearStart, 2.f, 12, FColor::Blue, false);
				DrawDebugSphere(GetWorld(), NearEnd, 2.f, 12, FColor::Green, false);
				FHitResult NearHitResult;
				//params ignore ememy when near
				GetWorld()->LineTraceSingleByChannel(
					NearHitResult,
					NearStart,
					NearEnd,
					ECollisionChannel::ECC_Visibility
					,Params
				);
				if (NearHitResult.bBlockingHit)
				{
					bNearWall = true;
				}else
				{
					bNearWall = false;
				}

				if (bNearWall)
				{
					//End = MuzzleFlashSocketTransform.GetRotation().GetForwardVector() * TRACE_LENGTH;
				} 
				
			}
			
		}

		TraceEnd = End; //xxx
	}
}


void UCombatComponent::Fire()
{
	if (CanFire())
	{
		bTimeUpCanFire = false;
		if(EquippedWeapon)
		{
			Character->PlayFireMontage(bAiming);
			switch (EquippedWeapon->FireType)
			{
			case EFireType::EFT_Projectile:
				FireProjectileWeapon();
				break;
			case EFireType::EFT_HitScan:
				FireHitScanWeapon();
				break;
			case EFireType::EFT_Shotgun:
				FireShotgun();
				break;
			}
		}
		StartFireTimer();
	}
}

void UCombatComponent::FireProjectileWeapon()
{
	if (EquippedWeapon == nullptr) return;
	HitTarget = EquippedWeapon->bUseScatter ? EquippedWeapon->TraceEndWithScatter(HitTarget) : HitTarget;
	EquippedWeapon->Fire(HitTarget);
}

void UCombatComponent::FireHitScanWeapon()
{

}

void UCombatComponent::FireShotgun()
{

}

void UCombatComponent::Reload()
{
	if (CombatState != ECombatState::ECS_Unoccupied || EquippedWeapon == nullptr) return;
	if (Character && EquippedWeapon)
	{
		CombatState = ECombatState::ECS_Reloading;
		Character->PlayReloadMontage();
	}
}

void UCombatComponent::ReloadEmptyWeapon()
{
	if (EquippedWeapon && EquippedWeapon->IsEmpty())
	{
		Reload();
	}
}

void UCombatComponent::FinishReloading()
{
	CombatState = ECombatState::ECS_Unoccupied;
}


void UCombatComponent::StartFireTimer()
{
	if (EquippedWeapon == nullptr || Character == nullptr) return;
	Character->GetWorldTimerManager().SetTimer(
		FireTimer,
		this,
		&UCombatComponent::FireTimerFinished,
		EquippedWeapon->FireDelay
	);
}

void UCombatComponent::FireTimerFinished()
{
	if (EquippedWeapon == nullptr) return;
	bTimeUpCanFire = true;
	if (bFireButtonPressed && EquippedWeapon->bAutomatic)
	{
		Fire();
	}
	//ReloadEmptyWeapon();
}

bool UCombatComponent::CanFire()
{
	if (EquippedWeapon == nullptr) return false;
	if (Character->IsSprinting())
	{
		SprintButtonPressed(false);
	}
	return !EquippedWeapon->IsEmpty() && bTimeUpCanFire
	&& CombatState == ECombatState::ECS_Unoccupied
	//&& !Character->IsSprinting()
	&& !Character->GetCharacterMovement()->IsFalling();
}

void UCombatComponent::RecoilRecovery(float DeltaTime)
{
	if (EquippedWeapon && bTimeUpCanFire && !bFireButtonPressed)
	{
		EquippedWeapon->CurveDeltaTimeDecrease(DeltaTime);
	}
}

bool UCombatComponent::ShouldSwapWeapons()
{
	return (EquippedWeapon != nullptr && SecondWeapon != nullptr);
}


void UCombatComponent::ThrowGrenadeFinished()
{
	CombatState = ECombatState::ECS_Unoccupied;
}

void UCombatComponent::ThrowGrenade()
{
	if (CombatState != ECombatState::ECS_Unoccupied || EquippedWeapon == nullptr) return;
	if (Character)
	{
		if(EquippedGrenades <= 0) return;
		CombatState = ECombatState::ECS_ThrowingGrenade;
		Character->PlayThrowGrenadeMontage();
		//AttachActorToLeftHand(EquippedWeapon);
		ShowAttachedGrenade(true);
		PRINT_STR("throw grenade");
	}
	
}

void UCombatComponent::LaunchGrenade()
{
	ShowAttachedGrenade(false);
	
	if (GrenadeClassMap.Contains(EquippedGrenadeType) &&
		CarriedGrenadesMap.Contains(EquippedGrenadeType) &&
		Character->GetAttachedGrenade())
	{
		const FVector StartingLocation = Character->GetAttachedGrenade()->GetComponentLocation();
		const FVector ToTarget = HitTarget - StartingLocation;
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = Character;
		SpawnParams.Instigator = Character;
		UWorld* World = GetWorld();
		if (World)
		{
			AProjectileTossGrenade* TossGrenade = World->SpawnActor<AProjectileTossGrenade>(
				GrenadeClassMap[EquippedGrenadeType],
				StartingLocation,
				ToTarget.Rotation(),
				SpawnParams
			);
			
			const FVector GrenadeImpulse =
				(Character->GetActorUpVector() * 0.5f
				+ Character->GetActorForwardVector().GetSafeNormal()
				+ ToTarget.GetSafeNormal())
				.GetSafeNormal() * FMath::Clamp(ToTarget.Length(), 150.f, 600.f);
			if (TossGrenade) TossGrenade->GetProjectileMesh()->AddImpulse(GrenadeImpulse);
		}
	}
	
}

float UCombatComponent::CalcThrowGrenadeMontagePlayRate()
{
	if (Character->GetAttachedGrenade())
	{
		const FVector StartingLocation = Character->GetAttachedGrenade()->GetComponentLocation();
		const FVector ToTarget = HitTarget - StartingLocation;
		return FMath::Clamp(FMath::Clamp(ToTarget.Length(), 0.f, 500.f) / 500.f, 0.7f, 1.f);
	}
	return 1.f;

}

void UCombatComponent::MeleeAttack()
{
	if (CombatState != ECombatState::ECS_Unoccupied || EquippedWeapon == nullptr) return;
	if (Character)
	{
		CombatState = ECombatState::ECS_ThrowingGrenade;
		Character->PlayMeleeAttackMontage();
	}
	
}

void UCombatComponent::MeleeAttackConfirm()
{
	PRINT_STR("melee attack")

	UWorld* World = GetWorld();
	const USkeletalMeshSocket* Socket = Character->GetMesh()->GetSocketByName(FName("RightHandSocketRifle"));
	//const USkeletalMeshSocket* EndSocket = Character->GetMesh()->GetSocketByName(FName("MuzzleFlash"));
	
	if (Character == nullptr || Character->GetCombat() == nullptr || World == nullptr || Socket == nullptr) return;
	
	FTransform SocketTransform = Socket->GetSocketTransform(Character->GetMesh());
	FVector Start = SocketTransform.GetLocation();
	FVector End = Start;
	FHitResult TraceHitResult;
	ETraceTypeQuery Query = UEngineTypes::ConvertToTraceType(ECC_TraceMelee);
	UKismetSystemLibrary::SphereTraceSingle(
		this,
		Start,
		End,
		25.f,
		Query,
		false,
		TArray<AActor*>(),
		EDrawDebugTrace::ForDuration,
		TraceHitResult,
		true);
	
	const APSLCharacter* OtherPSLCharacter = Cast<APSLCharacter>(TraceHitResult.GetActor());
	if (OtherPSLCharacter)
	{
		PRINT_STR("melee HIT")
		World->GetFirstPlayerController()->PlayerCameraManager->StartCameraShake(Character->MeleeAttackCameraShake, 1.f);
	}
	else if (OtherPSLCharacter == Character)
	{
		PRINT_STR("====")
	}
	else
	{
		PRINT_STR("void")
	}
}

void UCombatComponent::MeleeAttackFinished()
{
	CombatState = ECombatState::ECS_Unoccupied;
}

void UCombatComponent::SprintButtonPressed(bool bPressed)
{
	if (!EquippedWeapon) return;
	if (bPressed && CombatState == ECombatState::ECS_Unoccupied)
	{
		bSprinting = true;
		Character->GetCharacterMovement()->bOrientRotationToMovement = true;
		Character->bUseControllerRotationYaw = false;
		CombatState = ECombatState::ECS_Sprinting;
		Character->GetCharacterMovement()->MaxWalkSpeed = Character->GetProperties()->EquippedSprintSpeed;
	}
	else
	{
		if (EquippedWeapon) Character->TurnFromSprinting();
		bSprinting = false;
		CombatState = ECombatState::ECS_Unoccupied;
		Character->GetCharacterMovement()->MaxWalkSpeed = Character->GetProperties()->EquippedWalkSpeed;
	}
}


void UCombatComponent::ShowAttachedGrenade(bool bShowGrenade)
{
	if(GrenadeClassMap.Contains(EquippedGrenadeType))
	{
		UStaticMesh* GrenadeMesh = GrenadeClassMap[EquippedGrenadeType]->GetDefaultObject<AProjectileTossGrenade>()->GetProjectileMesh()->GetStaticMesh();
		if (GrenadeMesh)
		{
			Character->GetAttachedGrenade()->SetStaticMesh(GrenadeMesh);
			//Character->GetAttachedGrenade()->SetWorldScale3D(FVector(10.f,10.f,10.f));
			Character->GetAttachedGrenade()->SetVisibility(bShowGrenade);
		}
	}

	//GrenadeMesh->SetupAttachment(Character->GetMesh(), FName("LeftHandSocketGrenade"));
	//GrenadeMesh->SetWorldScale3D(FVector(10.f,10.f,10.f));
	//GrenadeMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	/*if (GrenadeMeshMap.Contains(EquippedGrenadeType))
	{
		UStaticMeshComponent* GrenadeMesh = GrenadeMeshMap[EquippedGrenadeType];
		GrenadeMesh->SetVisibility(bShowGrenade);
	}*/
}

