// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityComponent.h"

#include "PSL/PSLGameplayTags.h"
#include "PSL/EasyMacros.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PSL/Character/PSLCharacter.h"


UAbilityComponent::UAbilityComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void UAbilityComponent::BeginPlay()
{
	Super::BeginPlay();
	
	AbilityTagContainer.AddTag(GameplayTags.A_Soldier_LV1);
	AbilityTagContainer.AddTag(GameplayTags.B_Medic_LV1);
	int32 Size = AbilityTagContainer.Num();
	PRINT_ONE_VAR("size: %d\n", Size)

	if (AbilityTagContainer.HasTagExact(GameplayTags.A_Soldier_LV1))
	{
		PRINT_STR("A_Soldier_LV1\n");
	}
	if (AbilityTagContainer.HasTagExact(GameplayTags.B_Medic_LV1))
	{
		PRINT_STR("B_Medic_LV1\n");
	}
	if (!AbilityTagContainer.HasTagExact(GameplayTags.B_Medic_LV2))
	{
		PRINT_STR("NO HAS\n");
	}
	if (Character == nullptr) return;
	//Character->GetCharacterMovement()->JumpZVelocity = JumpZVelocity;
	//Character->GetCharacterMovement()->MaxWalkSpeed = UnequippedWalkSpeed;
	//Character->GetCharacterMovement()->MaxWalkSpeedCrouched = UnequippedWalkSpeedCrouched;
}


void UAbilityComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

