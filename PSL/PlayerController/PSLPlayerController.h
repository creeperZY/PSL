// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PSLPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PSL_API APSLPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	APSLPlayerController();
protected:
	virtual void BeginPlay() override;
};
