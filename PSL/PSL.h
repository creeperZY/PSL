// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

// Custom object channels
#define ECC_SkeletalMesh ECollisionChannel::ECC_GameTraceChannel1
#define ECC_Weapon ECollisionChannel::ECC_GameTraceChannel2
#define ECC_PickupActor ECollisionChannel::ECC_GameTraceChannel5

// Custom trace channels
#define ECC_TracePickUp ECollisionChannel::ECC_GameTraceChannel3 // No Use
#define ECC_TraceMelee ECollisionChannel::ECC_GameTraceChannel4