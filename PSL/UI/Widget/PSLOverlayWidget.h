// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PSLUserWidget.h"
#include "PSLOverlayWidget.generated.h"

/**
 * 
 */
UCLASS()
class PSL_API UPSLOverlayWidget : public UPSLUserWidget
{
	GENERATED_BODY()


public:
	UPROPERTY(meta = (BindWidget))
	class UVerticalBox* CharacterStateVerticalBox;

};
