// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupAmmo.h"

#include "PSL/EasyMacros.h"
#include "PSL/Character/PSLCharacter.h"
#include "PSL/PSLComponents/CombatComponent.h"

void APickupAmmo::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnSphereOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	APSLCharacter* PSLCharacter = Cast<APSLCharacter>(OtherActor);
	if (PSLCharacter)
	{
		PRINT_STR("on sphere overlap")
		PSLCharacter->GetCombat()->AmmoPickupDelegate.Broadcast(PickupGameplayTagContainer, AmmoNumMap);

		for (auto& Pair : AmmoNumMap)
		{
			auto& CarriedAmmoMap = PSLCharacter->GetCombat()->CarriedAmmoMap;
			if (!CarriedAmmoMap.Contains(Pair.Key))
			{
				CarriedAmmoMap.Add(Pair.Key, Pair.Value);
			}
			else
			{
				CarriedAmmoMap[Pair.Key] += Pair.Value;
			}
		}
		
		Destroy();
	}
}
