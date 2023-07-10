// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PSL/PSLTypes/CombatState.h"
#include "CombatComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PSL_API UCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCombatComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	friend class APSLCharacter;
	friend class UAbilityComponent;

protected:
	virtual void BeginPlay() override;

	// Weapon
	void EquipWeapon(class AWeapon* WeaponToEquip);
	void HolsterWeapon();
	void DropEquippedWeapon();
	void AttachActorToRightHand(AActor* ActorToAttach);
	void AttachActorToLeftHand(AActor* ActorToAttach);
	void AttachActorToBack1(AActor* ActorToAttach); // maybe need 2?
	void AttachActorToBack2(AActor* ActorToAttach);
	void PlayEquipWeaponSound(AWeapon* WeaponToEquip);
	void ShowAttachedGrenade(bool bShowGrenade);
	void EquipWeaponToRightHand(AWeapon* WeaponToEquip);
	void EquipWeaponToBack1(AWeapon* WeaponToEquip);
	void EquipWeaponToBack2(AWeapon* WeaponToEquip);
	void EquipFirstWeapon();
	void EquipSecondWeapon();
	void Reload();
	void ReloadEmptyWeapon();
	UFUNCTION(BlueprintCallable) // those function names confused
	void FinishReloading();

	void SwapWeapons();
	UFUNCTION(BlueprintCallable)
	void FinishSwap();
	UFUNCTION(BlueprintCallable)
	void FinishSwapAttachWeapons();
	void Fire(bool bPressed);
	void SetAiming(bool bIsAiming);

	
	// Grenade
	UFUNCTION(BlueprintCallable)
	void ThrowGrenadeFinished();
	UFUNCTION(BlueprintCallable)
	void ThrowGrenade();


	void Fire();
	void FireProjectileWeapon();
	void FireHitScanWeapon();
	void FireShotgun();
	



	
private:
	UPROPERTY()
	class APSLCharacter* Character;
	UPROPERTY()
	class AWeapon* EquippedWeapon;
	UPROPERTY()
	AWeapon* FirstWeapon;
	UPROPERTY()
	AWeapon* SecondWeapon;

	UPROPERTY()
	bool bAiming = false;


	UPROPERTY()
	ECombatState CombatState = ECombatState::ECS_EquipUnoccupied;

public:	
	//FORCEINLINE int32 GetGrenades() const {return Grenades;}
	bool ShouldSwapWeapons();
		
};
