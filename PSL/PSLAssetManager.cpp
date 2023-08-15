// Fill out your copyright notice in the Description page of Project Settings.


#include "PSLAssetManager.h"

#include "AbilitySystemGlobals.h"
#include "PSLGameplayTags.h"

UPSLAssetManager& UPSLAssetManager::Get()
{
	check(GEngine);
	
	UPSLAssetManager* AuraAssetManager = Cast<UPSLAssetManager>(GEngine->AssetManager);
	return *AuraAssetManager;
}

void UPSLAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();
	FPSLGameplayTags::InitializeNativeGameplayTags();

	// This is required to use Target Data!
	UAbilitySystemGlobals::Get().InitGlobalData();
}