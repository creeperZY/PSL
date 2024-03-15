// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PropertiesComponent.h"
#include "PSL/PSLTypes/CombatState.h"
#include "PSL/Weapon/ProjectileTossGrenade.h"
#include "PSL/Weapon/WeaponTypes.h"
#include "CombatComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_ThreeParams(FAmmoPickupDelegate, const FGameplayTagContainer&, const TMap<EWeaponType, float>&);
DECLARE_MULTICAST_DELEGATE_ThreeParams(FGrenadePickupDelegate, const FGameplayTagContainer&, const TMap<EGrenadeType, float>&);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PSL_API UCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCombatComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	friend class APSLCharacter;
	friend class UPropertiesComponent;
	

	void BindCallbacksToDependencies();
	FAmmoPickupDelegate AmmoPickupDelegate;
	FGrenadePickupDelegate GrenadePickupDelegate;

protected:
	virtual void BeginPlay() override;
	
	/*
	 * Weapon equip
	 */
	void PickupWeapon(class AWeapon* WeaponToEquip);
	void HolsterWeapon();
	void DropEquippedWeapon();
	void AttachActorToRightHand(AActor* ActorToAttach);
	void AttachActorToLeftHand(AActor* ActorToAttach);
	void AttachActorToBack1(AActor* ActorToAttach);
	void AttachActorToBack2(AActor* ActorToAttach);
	void AttachActorToPelvis1(AActor* ActorToAttach);
	void AttachActorToPelvis2(AActor* ActorToAttach);
	void PlayEquipWeaponSound(AWeapon* WeaponToEquip);
	void EquipWeaponToRightHand(AWeapon* WeaponToEquip);
	void EquipWeaponToSlot1(AWeapon* WeaponToEquip);
	void EquipWeaponToSlot2(AWeapon* WeaponToEquip);
	void EquipFirstWeapon();
	void EquipSecondWeapon();
	
	void EquipWeapon(AWeapon* WeaponToEquip);
	UFUNCTION(BlueprintCallable)
	void FinishEquip();
	UFUNCTION(BlueprintCallable)
	void FinishSwapAttachWeapons();

	void UnequipWeapon(AWeapon* WeaponToUnequip);
	UFUNCTION(BlueprintCallable)
	void FinishUnequipWeapon();

	UFUNCTION(BlueprintCallable)
	void PlayReloadEjectSound();
	UFUNCTION(BlueprintCallable)
	void PlayReloadInsertSound();
	UFUNCTION(BlueprintCallable)
	void PlayReloadSliderSound();
	UFUNCTION(BlueprintCallable)
	void PlayReloadSliderAnimation();

	
	void SetAiming(bool bIsAiming);

	
	/*
	 * Fire
	 */
	void FireButtonPressed(bool bPressed);
	void Fire();
	void FireProjectileWeapon();
	void FireHitScanWeapon();
	void FireShotgun();
	void Reload();
	void ReloadEmptyWeapon();
	UFUNCTION(BlueprintCallable) // those function names confused
	void FinishReloading();
	void TraceUnderCrosshairs(FHitResult& TraceHitResult);

	
	/*
	 * Grenade
	 */
	void ThrowGrenade();
	void ShowAttachedGrenade(bool bShowGrenade);
	UFUNCTION(BlueprintCallable)
	void LaunchGrenade();
	float CalcThrowGrenadeMontagePlayRate();
	UFUNCTION(BlueprintCallable)
	void ThrowGrenadeFinished();
	
	
	/*
	 * Melee Attack
	 */
	void MeleeAttack();
	UFUNCTION(BlueprintCallable)
	void MeleeAttackConfirm();
	UFUNCTION(BlueprintCallable)
	void MeleeAttackFinished();


	/*
	 * Sprinting
	 */
	void SprintButtonPressed(bool bPressed);
	
public:
	UPROPERTY(EditAnywhere) // Vis
	EGrenadeType EquippedGrenadeType;
	UPROPERTY(EditAnywhere) // Vis //Can auto switch to grenade type > 0
	int32 EquippedGrenades = 4;

	UPROPERTY(EditAnywhere) // Vis
	TMap<EGrenadeType, int32> CarriedGrenadesMap;
	UPROPERTY(EditAnywhere)
	TMap<EGrenadeType, TSubclassOf<AProjectileTossGrenade>> GrenadeClassMap;

	UPROPERTY(EditAnywhere) // Vis
	TMap<EWeaponType, int32> CarriedAmmoMap;
	
private:
	UPROPERTY()
	class APSLCharacter* Character;
	UPROPERTY()
	class AWeapon* EquippedWeapon;
	UPROPERTY(EditAnywhere) // should be a pistol
	TSubclassOf<AWeapon> DefaultWeaponClass;
	UPROPERTY()
	AWeapon* FirstWeapon;
	UPROPERTY()
	AWeapon* SecondWeapon;
	UPROPERTY()
	AWeapon* TempWeapon;

	FVector TraceEnd;
	FVector HitTarget;
	
	/*
	 * Aiming (FOV set up in character)
	*/
	bool bAiming = false;

	
	
	/*
	* Automatic fire
	*/
	bool bFireButtonPressed;
	FTimerHandle FireTimer;
	bool bTimeUpCanFire = true;
	void StartFireTimer();
	void FireTimerFinished();
	bool CanFire();
	void RecoilRecovery(float DeltaTime);


	/*
	 * Sprinting
	 */
	bool bSprinting = false;
	
	
	ECombatState CombatState = ECombatState::ECS_Unoccupied;

public:	
	//FORCEINLINE int32 GetGrenades() const {return Grenades;}
	bool ShouldSwapWeapons();
		
};
