// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileTossGrenade.h"
#include "GameFramework/ProjectileMovementComponent.h"

#if WITH_EDITOR
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
