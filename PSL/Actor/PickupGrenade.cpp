// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupGrenade.h"

#include "PSL/EasyMacros.h"
#include "PSL/Character/PSLCharacter.h"
#include "PSL/PlayerController/PSLPlayerController.h"
#include "PSL/PSLComponents/CombatComponent.h"

void APickupGrenade::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                     UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnSphereOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	
	APSLCharacter* PSLCharacter = Cast<APSLCharacter>(OtherActor);
	if (PSLCharacter)
	{
		PRINT_STR("on sphere overlap")
		PSLCharacter->GetCombat()->GrenadePickupDelegate.Broadcast(PickupGameplayTagContainer, GrenadeNumMap);

		for (auto& Pair : GrenadeNumMap)
		{
			auto& CarriedGrenadesMap = PSLCharacter->GetCombat()->CarriedGrenadesMap;
			if (!CarriedGrenadesMap.Contains(Pair.Key))
			{
				CarriedGrenadesMap.Add(Pair.Key, Pair.Value);
			}
			else
			{
				CarriedGrenadesMap[Pair.Key] += Pair.Value;
			}
		}
		
		Destroy();
	}
}
