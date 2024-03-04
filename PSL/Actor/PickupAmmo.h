// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PSLPickupActor.h"
#include "PSLPickupActor.h"
#include "PickupAmmo.generated.h"

enum class EWeaponType : uint8;
/**
 * 
 */
UCLASS()
class PSL_API APickupAmmo : public APSLPickupActor
{
	GENERATED_BODY()
public:

protected:
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	
private:
	UPROPERTY(EditAnywhere, Category="Pickup")
	TMap<EWeaponType, float> AmmoNumMap;
};
