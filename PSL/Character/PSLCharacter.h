// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "LegacyCameraShake.h"
#include "Components/TimelineComponent.h"
#include "PSLCharacterBase.h"
#include "PSL/AbilitySystem/PSLAbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "PSL/PSLTypes/EquippedPoses.h"
#include "PSL/PSLTypes/TurningInPlace.h"
#include "PSL/PSLTypes/CombatState.h"
#include "PSL/PSLTypes/SkillTreeNode.h"
#include "PSLCharacter.generated.h"


UCLASS(config=Game)
class APSLCharacter : public APSLCharacterBase
{
	GENERATED_BODY()

public:
	APSLCharacter();
	virtual void PossessedBy(AController* NewController) override;
	virtual void InitAbilityActorInfo() override;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bUseMocapAnimations = false;

public:
	void PlayFireMontage(bool bAiming);
	void PlayReloadMontage();
	void PlayElimMontage();
	void PlayThrowGrenadeMontage();
	void PlayEquipMontage(AWeapon* WeaponToEquip);
	void PlayUnequipMontage(AWeapon* WeaponToUnequip);
	void PlayMeleeAttackMontage();
	void PlaySwapMontage(AWeapon* WeaponToEquip); // Mocap
	
protected:
	/** Called for movement input */
	void Move(const FInputActionValue& Value);
	/** Called for looking input */
	void Look(const FInputActionValue& Value);
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void PostInitializeComponents() override;

	virtual void Jump() override;
	void EquipButtonPressed();
	void EquipFirstButtonPressed();
	void EquipSecondButtonPressed();
	void DropButtonPressed();
	void CrouchButtonPressed();
	void AimButtonPressed();
	void AimButtonReleased();
	void FireButtonPressed();
	void FireButtonReleased();
	void GrenadeButtonPressed();
	void GrenadeButtonCanceled();
	void GrenadeButtonCompleted();
	void MeleeAttackButtonPressed();
	void ReloadButtonPressed();
	void SprintButtonPressed();
	void SprintButtonReleased();

private:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	// To add mapping context
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* InputMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* EquipAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* DropAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* EquipFirstAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* EquipSecondAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* CrouchAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* FireAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* AimAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* GrenadeAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MeleeAttackAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* ReloadAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* SprintAction;
	
	UPROPERTY()
	class AWeapon* OverlappingWeapon;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UCombatComponent* Combat;

	UPROPERTY(VisibleAnywhere)
	class UPropertiesComponent* Properties;

	UPROPERTY(VisibleAnywhere)
	class UBuildComponent* Build;

	UPROPERTY(VisibleAnywhere)
	class USkillComponent* Skill;
	
	UPROPERTY(VisibleAnywhere)
	class UPostProcessComponent* PostProcess;
	
	/*
	 * Animation montages
	 */
	UPROPERTY(EditAnywhere, Category = "Combat Montage")
	class UAnimMontage* FireWeaponMontage;

	UPROPERTY(EditAnywhere, Category = "Combat Montage")
	class UAnimMontage* ReloadMontage;
	
	UPROPERTY(EditAnywhere, Category = "Combat Montage")
	class UAnimMontage* HitReactMontage;

	UPROPERTY(EditAnywhere, Category = "Combat Montage")
	class UAnimMontage* ElimMontage;

	UPROPERTY(EditAnywhere, Category = "Combat Montage")
	class UAnimMontage* ThrowGrenadeMontage;
	
	UPROPERTY(EditAnywhere, Category = "Combat Montage")
	class UAnimMontage* EquipMontage;

	UPROPERTY(EditAnywhere, Category = "Combat Montage")
	class UAnimMontage* UnequipMontage;
	
	UPROPERTY(EditAnywhere, Category = "Combat Montage")
	class UAnimMontage* MeleeAttackMontage;
	
	UPROPERTY(EditAnywhere, Category = "Combat Montage")
	class UAnimMontage* SwapWeaponMontage;

	/*
	 * Render X-ray on screen
	 */
	void SetShowXRayWhenCharacterOccluded();
	
	
	
	/*
	 * Grenade
	 */
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* AttachedGrenade;

	
	/*
	 * FOV
	 */
	UPROPERTY(EditAnywhere, Category="Game Camera")
	float UnequippedFOV = 90.f; //This option is not in using. Set FOV in blueprint
	UPROPERTY(EditAnywhere, Category="Game Camera")
	float EquippedFOV = 75.f;
	UPROPERTY(EditAnywhere, Category="Game Camera")
	float EquippedSprintFOV = 90.f;
	UPROPERTY(EditAnywhere, Category="Game Camera") 
	float AimFOV = 60.f; //This option is not in using. Use Weapon FOV
	float CurrentFOV = 90.f;
	
	UPROPERTY(EditAnywhere, Category="Game Camera")
	float UnequippedTargetArmLength = 320.f;
	UPROPERTY(EditAnywhere, Category="Game Camera")
	float EquippedTargetArmLength = 320.f;
	UPROPERTY(EditAnywhere, Category="Game Camera")
	float EquippedSprintTargetArmLength = 320.f;
	float CurrentTargetArmLength = 320.f;
	
	UPROPERTY(EditAnywhere, Category="Game Camera")
	FVector UnequippedSocketOffset = FVector(0.f, 40.f, -60.f);
	UPROPERTY(EditAnywhere, Category="Game Camera")
	FVector EquippedSocketOffset = FVector(0.f, 65.f, -60.f);
	UPROPERTY(EditAnywhere, Category="Game Camera")
	FVector EquippedSprintSocketOffset = FVector(0.f, 65.f, -60.f);
	FVector CurrentSocketOffset = FVector(0.f, 40.f, -60.f);

	UPROPERTY(EditAnywhere, Category="Game Camera")
	float InterpSpeed = 10.f;
	void InterpCameraFOV(float DeltaSeconds);
	UPROPERTY(EditAnywhere, Category="Game Camera")
	float CameraThreshold = 200.f;
	void HideCharacterIfCameraClose();

	
	/*
	 * Turn in place and AO_Yaw
	 */
	float AO_Yaw;
	float InterpAO_Yaw;
	float AO_Pitch;
	FRotator StartingAimRotation;
	ETurningInPlace TurningInPlace;
	void TurnInPlace(float DeltaTime);
	float CalculateSpeed();
	void AimOffset(float DeltaTime);
	
	
	
	/*
	 * Turn before equip weapon 
	 */
	FRotator StartingRotation;
	FRotator AimRotation;
	bool bTurnFinished = false;
	FTimeline TurnBeforeEquipTimeline;
	UPROPERTY(EditAnywhere, Category="Game Camera")
	UCurveFloat* TurnCurve;
	void SetTurnDelegate();
	UFUNCTION()
	void TurnProgress(float Alpha);
	UFUNCTION()
	void OnTurnFinished();
	void TurnBeforeEquip();
	


	
public:
	/*
	 * Camera Shake
	 */
	UPROPERTY(EditAnywhere, Category="Camera Shake")
	TSubclassOf<UCameraShakeBase> MeleeAttackCameraShake;

	void TurnFromSprinting() { TurnBeforeEquip(); }

	/*
	 * Skill Tree
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FSkillInfo> SkillInfosArray;
	UPROPERTY()
	USkillTreeManager* SkillTreeManager;
	
public:
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	FORCEINLINE UCombatComponent* GetCombat() const { return Combat; }
	ECombatState GetCombatState() const;
	FORCEINLINE UPropertiesComponent* GetProperties() const { return Properties; }
	FORCEINLINE UBuildComponent* GetBuild() const { return Build; }
	FORCEINLINE USkillComponent* GetSkill() const { return Skill; }
	FORCEINLINE void SetOverlappingWeapon(AWeapon* Weapon) { OverlappingWeapon = Weapon; }
	FORCEINLINE UStaticMeshComponent* GetAttachedGrenade() const { return AttachedGrenade; }
	FORCEINLINE ETurningInPlace GetTurningInPlace() const { return TurningInPlace; }
	FORCEINLINE float GetAO_Yaw() const { return AO_Yaw; }
	FORCEINLINE float GetAO_Pitch() const { return AO_Pitch; }
	FVector GetHitTarget() const;
	bool IsWeaponEquipped();
	EEquippedPoseType GetEquippedPoseType();
	bool IsAiming() const;
	bool IsSprinting() const;
	bool IsNearWall() const;
	bool CanSprint() const;

	AWeapon* GetEquippedWeapon();
};