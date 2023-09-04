#pragma once

#define TRACE_LENGTH 80000.f

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	EWT_AssaultRifle556 UMETA(DisplayName = "Assault Rifle 5.56"),
	EWT_AssaultRifle762 UMETA(DisplayName = "Assault Rifle 7.62"),
	EWT_RocketLauncher UMETA(DisplayName = "Rocket Launcher"),
	EWT_Pistol UMETA(DisplayName = "Pistol"),
	EWT_SubmachineGun UMETA(DisplayName = "Submachine Gun"),
	EWT_Shotgun UMETA(DisplayName = "Shotgun"),
	EWT_SniperRifle UMETA(DisplayName = "Sniper Rifle"),
	EWT_GrenadeLauncher UMETA(DisplayName = "Grenade Launcher"),
	EWT_Flag UMETA(DisplayName = "Flag"),
	EWT_MeleeWeapon UMETA(DisplayName = "Melee Weapon"),

	EWT_MAX UMETA(DisplayName = "DefaultMAX")
};

UENUM(BlueprintType)
enum class EGrenadeType : uint8
{
	EWT_None UMETA(DisplayName = "None"),
	EWT_GrenadeFrag UMETA(DisplayName = "Grenade Frag"),
	EWT_GrenadeFire UMETA(DisplayName = "Grenade Fire"),
	EWT_GrenadeImpact UMETA(DisplayName = "Grenade Impact"),
	EWT_GrenadeScanner UMETA(DisplayName = "Grenade Scanner"),
	EWT_GrenadeSlow UMETA(DisplayName = "Grenade Slow"),
	EWT_GrenadeBlackhole UMETA(DisplayName = "Grenade Blackhole"),

	EWT_MAX UMETA(DisplayName = "DefaultMAX")
};