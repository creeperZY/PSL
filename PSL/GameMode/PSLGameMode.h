// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "PSLGameMode.generated.h"

UCLASS(minimalapi)
class APSLGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	APSLGameMode();
	
protected:
	virtual void Tick(float DeltaSeconds) override;
};



