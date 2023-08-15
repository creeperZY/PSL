// Fill out your copyright notice in the Description page of Project Settings.


#include "PSLPlayerController.h"

APSLPlayerController::APSLPlayerController()
{
	
}

void APSLPlayerController::BeginPlay()
{
	Super::BeginPlay();
	PlayerCameraManager->ViewPitchMin = -85.f;
	PlayerCameraManager->ViewPitchMax = 85.f;
}
