// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Actor.h"
#include "PSLPickupActor.generated.h"

UCLASS()
class PSL_API APSLPickupActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APSLPickupActor();

	void EnableCustomDepth(bool bEnable);
	void ShowStencilColor(int32 ColorStencilValue);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Destroyed() override;

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
	virtual void OnSphereEndOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex
	);
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
protected:
	UPROPERTY(EditAnywhere, Category="Pickup")
	FGameplayTagContainer PickupGameplayTagContainer;

	UPROPERTY()
	AActor* LastPickupActor = nullptr;
	
private:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* PickupMesh;

	UPROPERTY(VisibleAnywhere)
	class USphereComponent* AreaSphere;




};
