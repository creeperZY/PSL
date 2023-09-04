// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class PSL_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	AProjectile();
	virtual void Destroyed() override;
	
	UPROPERTY(EditAnywhere)
	float InitialSpeed = 15000.f;

	// Only set this for Grenades and Rockets. Set only in Weapon.
	UPROPERTY(VisibleAnywhere)
	float Damage = 20.f;

	// Doesn't matter for Grenades and Rockets. Set only in Weapon.
	UPROPERTY(VisibleAnywhere)
	float HeadShotDamage = 40.f;
	
protected:
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;
	void StartDestoryTimer();
	void DestoryTimerFinished();
	void SpawnTrailSystem();
	virtual void ExplodeDamage();

	UFUNCTION()
	virtual void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
	UPROPERTY(EditAnywhere)
	class UParticleSystem* ImpactParticles;

	UPROPERTY(EditAnywhere)
	class USoundCue* ImpactSound;

	UPROPERTY(EditAnywhere)
	class UBoxComponent* CollisionBox;

	UPROPERTY(EditAnywhere)
	class UNiagaraSystem* TrailSystem;

	UPROPERTY()
	class UNiagaraComponent* TrailSystemComponent;
	
	UPROPERTY(VisibleAnywhere)
	class UProjectileMovementComponent* ProjectileMovementComponent;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* ProjectileMesh;

	UPROPERTY(EditAnywhere)
	float DamageInnerRadius = 200.f;
	
	UPROPERTY(EditAnywhere)
	float DamageOuterRadius = 500.f;

	UPROPERTY(EditAnywhere)
	class UParticleSystem* Tracer;

	UPROPERTY()
	class UParticleSystemComponent* TracerComponent;
	
private:	
	FTimerHandle DestoryTimer;

	UPROPERTY(EditAnywhere)
	float DestoryTime = 3.f;

public:
	FORCEINLINE UStaticMeshComponent* GetProjectileMesh() const { return ProjectileMesh; }

};
