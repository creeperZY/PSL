// Fill out your copyright notice in the Description page of Project Settings.


#include "PSLCharacterBase.h"
#include "AbilitySystemComponent.h"

#include "PSL/PSL.h"

// Sets default values
APSLCharacterBase::APSLCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetMesh()->SetCollisionObjectType(ECC_SkeletalMesh);

}

UAbilitySystemComponent* APSLCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}


// Called when the game starts or when spawned
void APSLCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}


void APSLCharacterBase::InitAbilityActorInfo()
{
}



void APSLCharacterBase::InitializeBasicAttributes() const
{
	check(IsValid(GetAbilitySystemComponent()));
	check(DefaultBasicAttribute);
	const FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	const FGameplayEffectSpecHandle SpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(DefaultBasicAttribute, 1.f, ContextHandle);
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), GetAbilitySystemComponent());
}

// Called every frame
void APSLCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APSLCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

