// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PSLPickupActor.h"
#include "PickupGrenade.generated.h"

enum class EGrenadeType : uint8;
/**
 * 
 */
UCLASS()
class PSL_API APickupGrenade : public APSLPickupActor
{
	GENERATED_BODY()
public:

protected:
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	
private:
	UPROPERTY(EditAnywhere, Category="Pickup")
	TMap<EGrenadeType, float> GrenadeNumMap;
};
