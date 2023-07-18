// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityComponent.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "PSL/Character/PSLCharacter.h"

UAbilityComponent::UAbilityComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}


void UAbilityComponent::BeginPlay()
{
	Super::BeginPlay();

	if (Character == nullptr) return;
	Character->GetCharacterMovement()->JumpZVelocity = JumpZVelocity;
	Character->GetCharacterMovement()->MaxWalkSpeed = UnequippedWalkSpeed;
	Character->GetCharacterMovement()->MaxWalkSpeedCrouched = UnequippedWalkSpeedCrouched;
}


void UAbilityComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

