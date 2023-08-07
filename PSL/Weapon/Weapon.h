// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponTypes.h"
#include "PSL/PSLTypes/EquippedPoses.h"
#include "Weapon.generated.h"

UENUM(BlueprintType)
enum class EWeaponState : uint8
{
	EWS_Initial UMETA(DisplayName = "Initial State"),
	EWS_Equipped UMETA(DisplayName = "Equipped Using Now"),
	EWS_EquippedBack UMETA(DisplayName = "Equipped Back"),
	EWS_Dropped UMETA(DisplayName = "Dropped"),
	
	EWS_MAX UMETA(DisplayName = "DefaultMAX")
};

UENUM(BlueprintType)
enum class EFireType : uint8
{
	EFT_HitScan UMETA(DisplayName = "Hit Scan Weapon"),
	EFT_Projectile UMETA(DisplayName = "Projectile Weapon"),
	EFT_Shotgun UMETA(DisplayName = "Shotgun Weapon"),

	EFT_MAX UMETA(DisplayName = "DefaultMAX")
};

UCLASS()
class PSL_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	AWeapon();
	virtual void Tick(float DeltaTime) override;
	virtual void SetOwner(AActor* NewOwner) override;
	void SetHUDAmmo();
	void ShowPickupWidget(bool bShowWidget);
	void ShowStencilColor(int32 ColorStencilValue);
	virtual void Fire(const FVector& HitTarget);
	virtual void Dropped();
	void AddAmmo(int32 AmmoToAdd);
	FVector TraceEndWithScatter(const FVector& HitTarget);

	// Zoomed FOV while aiming
	UPROPERTY(EditAnywhere, Category = "Weapon Aim")
	float ZoomedFOV = 30.f;
	
	UPROPERTY(EditAnywhere, Category = "Weapon Aim")
	float ZoomInterpSpeed = 20.f;
	
	// Automatic Fire
	UPROPERTY(EditAnywhere, Category = "Weapon Properties")
	float FireDelay = 0.15f;
	
	UPROPERTY(EditAnywhere, Category = "Weapon Properties")
	bool bAutomatic = true;
	
	//Enable or disable custom depth
	void EnableCustomDepth(bool bEnable);


	UPROPERTY(EditAnywhere, Category = "Weapon FX")
	class USoundCue* EquipSound;
	
	UPROPERTY(EditAnywhere, Category = "Weapon Properties")
	EFireType FireType;

	UPROPERTY(EditAnywhere, Category = "Weapon Properties")
	float DropFactor = 200.f; // Throw impulse factor
	
	// Weapon Scatter
	UPROPERTY(EditAnywhere, Category="Weapon Scatter")
	bool bUseScatter = false;

protected:
	virtual void BeginPlay() override;
	virtual void OnWeaponStateSet();
	virtual void OnEquipped();
	virtual void OnDropped();
	virtual void OnEquippedBack();
	
	UFUNCTION()
	virtual void OnSphereOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);
	
	UFUNCTION()
	void OnSphereEndOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex
	);


	// Weapon Scatter
	UPROPERTY(EditAnywhere, Category = "Weapon Scatter")
	float DistanceToSphere = 800.f;
	
	UPROPERTY(EditAnywhere, Category = "Weapon Scatter")
	float SphereRadius = 75.f;

	// Weapon Properties
	UPROPERTY(EditAnywhere, Category = "Weapon Properties")
	float Damage = 20.f;
	
	UPROPERTY(EditAnywhere, Category = "Weapon Properties")
	float HeadShotDamage = 40.f;
	

	UPROPERTY()
	class APSLCharacter* PSLOwnerCharacter;
	UPROPERTY()
	class APSLPlayerController* PSLOwnerController;
	
private:
	UPROPERTY(VisibleAnywhere, Category = "Weapon Properties")
	USkeletalMeshComponent* WeaponMesh;
	
	UPROPERTY(VisibleAnywhere, Category = "Weapon Properties")
	class USphereComponent* AreaSphere;
	
	UPROPERTY(VisibleAnywhere, Category = "Weapon Properties")
	EWeaponState WeaponState;

	UPROPERTY(EditAnywhere, Category = "Weapon Type")
	EWeaponType WeaponType;

	UPROPERTY(EditAnywhere, Category = "Weapon Type")
	EEquippedPoseType EquippedPoseType;
	
	UPROPERTY(VisibleAnywhere, Category = "Weapon Properties")
	class UWidgetComponent* PickupWidget;
	
	UPROPERTY(EditAnywhere, Category = "Weapon FX")
	class UAnimationAsset* FireAnimation;

	UPROPERTY(EditAnywhere, Category = "Weapon Properties")
	TSubclassOf<class ACasing> CasingClass;

	UPROPERTY(EditAnywhere, Category = "Weapon Properties")
	int32 CurrentAmmo;

	UPROPERTY(EditAnywhere, Category = "Weapon Properties")
	int32 MagCapacity;
	
	void SpendRound();

	
public:
	void SetWeaponState(EWeaponState State);
	bool IsEmpty();
	bool IsFull();
	FORCEINLINE USphereComponent* GetAreaSphere() const { return AreaSphere; }
	FORCEINLINE USkeletalMeshComponent* GetWeaponMesh() const { return WeaponMesh; }
	FORCEINLINE UWidgetComponent* GetPickupWidget() const { return PickupWidget; }
	FORCEINLINE float GetZoomedFOV() const { return ZoomedFOV; }
	FORCEINLINE float GetZoomInterpSpeed() const { return ZoomInterpSpeed; }
	FORCEINLINE EWeaponType GetWeaponType() const { return WeaponType; }
	FORCEINLINE int32 GetAmmo() const { return CurrentAmmo; }
	FORCEINLINE int32 GetMagCapacity() const { return MagCapacity; }
	FORCEINLINE float GetDamage() const { return Damage; }
	FORCEINLINE float GetHeadShotDamage() const { return HeadShotDamage; }
	FORCEINLINE EEquippedPoseType GetEquippedPoseType() const { return EquippedPoseType; }
};
