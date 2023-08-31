// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PSL/PSLTypes/CombatState.h"
#include "PSL/Weapon/WeaponTypes.h"
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
	
	/*
	 * Weapon equip
	 */
	void EquipWeapon(class AWeapon* WeaponToEquip);
	void HolsterWeapon();
	void DropEquippedWeapon();
	void AttachActorToRightHand(AActor* ActorToAttach);
	void AttachActorToLeftHand(AActor* ActorToAttach);
	void AttachActorToBack1(AActor* ActorToAttach); // maybe need 2?
	void AttachActorToBack2(AActor* ActorToAttach);
	void PlayEquipWeaponSound(AWeapon* WeaponToEquip);
	void EquipWeaponToRightHand(AWeapon* WeaponToEquip);
	void EquipWeaponToBack1(AWeapon* WeaponToEquip);
	void EquipWeaponToBack2(AWeapon* WeaponToEquip);
	void EquipFirstWeapon();
	void EquipSecondWeapon();
	
	void SwapWeapons();
	UFUNCTION(BlueprintCallable)
	void FinishSwap();
	UFUNCTION(BlueprintCallable)
	void FinishSwapAttachWeapons();

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
	void ShowAttachedGrenade(bool bShowGrenade);
	UFUNCTION(BlueprintCallable)
	void ThrowGrenadeFinished();
	UFUNCTION(BlueprintCallable)
	void ThrowGrenade();
	UFUNCTION(BlueprintCallable)
	void LaunchGrenade();
	
	UPROPERTY(EditAnywhere) // Vis
	TSubclassOf<class AProjectileTossGrenade> EquippedGrenadeClass;
	UPROPERTY(EditAnywhere) // Vis
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
	UPROPERTY()
	AWeapon* FirstWeapon;
	UPROPERTY()
	AWeapon* SecondWeapon;

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
	
	
	ECombatState CombatState = ECombatState::ECS_Unoccupied;

public:	
	//FORCEINLINE int32 GetGrenades() const {return Grenades;}
	bool ShouldSwapWeapons();
		
};
