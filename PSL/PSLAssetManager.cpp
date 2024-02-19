// Fill out your copyright notice in the Description page of Project Settings.


#include "PSLAssetManager.h"

#include "AbilitySystemGlobals.h"
#include "PSLAbilityGameplayTags.h"
#include "PSLMessageGameplayTags.h"

UPSLAssetManager& UPSLAssetManager::Get()
{
	check(GEngine);
	
	UPSLAssetManager* PSLAssetManager = Cast<UPSLAssetManager>(GEngine->AssetManager);
	return *PSLAssetManager;
}

void UPSLAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();
	FPSLAbilityGameplayTags::InitializeNativeGameplayTags();
	FPSLMessageGameplayTags::InitializeNativeGameplayTags();

	// This is required to use Target Data!
	UAbilitySystemGlobals::Get().InitGlobalData();
}