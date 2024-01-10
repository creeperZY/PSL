// Fill out your copyright notice in the Description page of Project Settings.


#include "PSLUserWidget.h"

void UPSLUserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	WidgetControllerSet();
}
