// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileTossGrenade.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "PSL/PSL.h"

#if WITH_EDITOR
AProjectileTossGrenade::AProjectileTossGrenade()
{
	GetCollisionBox()->SetCollisionResponseToChannel(ECC_SkeletalMesh, ECollisionResponse::ECR_Ignore);
	GetCollisionBox()->SetCollisionResponseToChannel(ECC_Weapon, ECollisionResponse::ECR_Ignore);
}

void AProjectileTossGrenade::PostEditChangeProperty(FPropertyChangedEvent& Event)
{
	Super::PostEditChangeProperty(Event);
	
	FName PropertyName = Event.Property != nullptr ? Event.Property->GetFName() : NAME_None;
	if (PropertyName == GET_MEMBER_NAME_CHECKED(AProjectileTossGrenade, InitialSpeed))
	{
		if (ProjectileMovementComponent)
		{
			ProjectileMovementComponent->InitialSpeed = InitialSpeed;
			ProjectileMovementComponent->MaxSpeed = InitialSpeed;
		}
	}
	
}
#endif


void AProjectileTossGrenade::ExplodeDamage()
{
	Super::ExplodeDamage();
}
