// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatComponent.h"

#include "AbilityComponent.h"
#include "PSL/EasyMacros.h"
#include "PSL/Weapon/Weapon.h"
#include "PSL/Character/PSLCharacter.h"
#include "Engine/SkeletalMeshSocket.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
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
}


void UCombatComponent::PickupWeapon(AWeapon* WeaponToEquip)
{
	if (Character == nullptr || WeaponToEquip == nullptr) return;
	if (CombatState != ECombatState::ECS_Unoccupied) return;

	// Freely swap weapons
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

	// Old School 1 Rifle 2 Pistol
	/*switch (WeaponToEquip->GetEquippedPoseType())
	{
	case EEquippedPoseType::EEPT_PistolPose:
		if (SecondWeapon != nullptr)
		{
			if(EquippedWeapon == SecondWeapon)
			{
				DropEquippedWeapon();
				SecondWeapon = WeaponToEquip;
				EquipWeaponToRightHand(WeaponToEquip);
			}
			else
			{
				AWeapon* TempWeapon = EquippedWeapon;
				EquippedWeapon = SecondWeapon;
				DropEquippedWeapon();
				SecondWeapon = nullptr;
				EquipWeaponToBack2(WeaponToEquip);
				SecondWeapon = WeaponToEquip;
				EquippedWeapon = TempWeapon;
			}
		}
		else
		{
			EquipWeaponToBack2(WeaponToEquip);
		}
		break;
	case EEquippedPoseType::EEPT_RiflePose:
		if (FirstWeapon != nullptr)
		{
			if(EquippedWeapon == FirstWeapon)
			{
				DropEquippedWeapon();
				FirstWeapon = WeaponToEquip;
				EquipWeaponToRightHand(WeaponToEquip);
			}
			else
			{
				AWeapon* TempWeapon = EquippedWeapon;
				EquippedWeapon = FirstWeapon;
				DropEquippedWeapon();
				FirstWeapon = nullptr;
				EquipWeaponToBack1(WeaponToEquip);
				FirstWeapon = WeaponToEquip;
				EquippedWeapon = TempWeapon;
			}
		}
		else
		{
			EquipWeaponToBack1(WeaponToEquip);
		}
		break;
	}*/

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


void UCombatComponent::EquipFirstWeapon()
{
	if (FirstWeapon)
	{
		if (EquippedWeapon == FirstWeapon && EquippedWeapon)
		{
			UnequipWeapon(EquippedWeapon);
			//HolsterWeapon();
		}
		//else if (EquippedWeapon == SecondWeapon && EquippedWeapon) // need swap animation
		//{
		//	EquipWeaponToBack2(EquippedWeapon);
		//	EquipWeaponToRightHand(FirstWeapon);
		//}
		else
		{
			//EquipWeaponToBack2(EquippedWeapon); 
			//EquipWeaponToRightHand(FirstWeapon); // on back
			EquipWeapon(FirstWeapon);
		}
	}
}


void UCombatComponent::EquipSecondWeapon()
{
	if (SecondWeapon)
	{
		if (EquippedWeapon == SecondWeapon && EquippedWeapon)
		{
			UnequipWeapon(EquippedWeapon);
			//HolsterWeapon();
		}
		//else if (EquippedWeapon == FirstWeapon && EquippedWeapon)
		//{
		//	EquipWeaponToBack1(EquippedWeapon);
		//	EquipWeaponToRightHand(SecondWeapon);
		//}
		else
		{
			//EquipWeaponToBack1(EquippedWeapon); 
			//EquipWeaponToRightHand(SecondWeapon);
			EquipWeapon(SecondWeapon);
		}
	}

}


void UCombatComponent::EquipWeapon(AWeapon* WeaponToEquip)
{
	if (CombatState != ECombatState::ECS_Unoccupied || Character == nullptr) return;
	if (WeaponToEquip == nullptr) return;
	TempWeapon = WeaponToEquip;
	Character->PlayEquipMontage(WeaponToEquip);
	CombatState = ECombatState::ECS_SwappingWeapons;
}



void UCombatComponent::FinishSwapAttachWeapons()
{
	if (TempWeapon == FirstWeapon && TempWeapon)
	{
		EquipWeaponToBack2(EquippedWeapon);
		EquipWeaponToRightHand(FirstWeapon);
	}
	else if (TempWeapon == SecondWeapon && TempWeapon)
	{
		EquipWeaponToBack1(EquippedWeapon);
		EquipWeaponToRightHand(SecondWeapon);
	}
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
	
	if (Character && Character->GetAbility())
	{
		Character->GetCharacterMovement()->MaxWalkSpeed = bIsAiming ? Character->GetAbility()->EquippedAimWalkSpeed : Character->GetAbility()->EquippedWalkSpeed;
		Character->GetCharacterMovement()->MaxWalkSpeedCrouched = bIsAiming ? Character->GetAbility()->EquippedAimWalkSpeedCrouched : Character->GetAbility()->UnequippedWalkSpeedCrouched;
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
		TraceEnd = End; //xxx

		
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
		}
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
	
}

void UCombatComponent::ReloadEmptyWeapon()
{
}

void UCombatComponent::FinishReloading()
{
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
	return !EquippedWeapon->IsEmpty() && bTimeUpCanFire && CombatState == ECombatState::ECS_Unoccupied
	&& !Character->GetCharacterMovement()->IsFalling();
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
		FVector ToTarget = HitTarget - StartingLocation;
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
		}
	}
	
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
	
	if (Character == nullptr || Character->GetCombat() == nullptr || World == nullptr || Socket == nullptr) return;
	
	FTransform SocketTransform = Socket->GetSocketTransform(Character->GetMesh());
	FVector Start = Character->GetActorLocation();
	FVector End = SocketTransform.GetLocation() + Character->GetActorForwardVector() * (40.f);

	FHitResult TraceHitResult;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(Character);
	if (Character->GetCombat()->FirstWeapon)
		Params.AddIgnoredActor(Character->GetCombat()->FirstWeapon);
	if (Character->GetCombat()->SecondWeapon)
		Params.AddIgnoredActor(Character->GetCombat()->SecondWeapon);
	Params.AddIgnoredActor(Character->GetEquippedWeapon());
	World->LineTraceSingleByChannel(
		TraceHitResult,
		Start,
		End,
		ECollisionChannel::ECC_Visibility
		,Params
	);
	
	APSLCharacter* OtherPSLCharacter = Cast<APSLCharacter>(TraceHitResult.GetActor());
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
	
	DrawDebugSphere(GetWorld(), Start,2.f, 12, FColor::Blue, false, 12.f);
	DrawDebugSphere(GetWorld(), End, 2.f, 12, FColor::Cyan, false,12.f);
}

void UCombatComponent::MeleeAttackFinished()
{
	CombatState = ECombatState::ECS_Unoccupied;
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

