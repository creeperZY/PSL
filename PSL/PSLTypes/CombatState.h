﻿#pragma once

UENUM()
enum class ECombatState : uint8
{
    ECS_Unequipped UMETA(DisplayName = "Unequipped"),	
	ECS_EquipUnoccupied UMETA(DisplayName = "Equip and Unoccupid"),
	ECS_Reloading UMETA(DisplayName = "Reloading"),
	ECS_ThrowingGrenade UMETA(DisplayName = "Throwing Grenade"),
	ECS_SwappingWeapons UMETA(DisplayName = "Swapping Weapons"),
	//maybe i want a melee
	
	ECS_MAX UMETA(DisplayName = "DefaultMAX")
};