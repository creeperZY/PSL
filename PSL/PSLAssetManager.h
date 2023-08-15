// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "PSLAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class PSL_API UPSLAssetManager : public UAssetManager
{
	GENERATED_BODY()
public:

	static UPSLAssetManager& Get();

protected:

	virtual void StartInitialLoading() override;
};
