// Fill out your copyright notice in the Description page of Project Settings.


#include "PSLUserWidget.h"

void UPSLUserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	WidgetControllerSet();
}

void UPSLUserWidget::SetUpperWidget(UPSLUserWidget* InWidget)
{
	if (!InWidget || InWidget == this) return;
	UpperWidget = InWidget;
	UpperWidget->SubWidgets.AddUnique(this);
	UpperWidget->RefreshSubWidgetsArray();
	UpperWidget->SetAsUpperWidgetBy(this);
	RefreshSubWidgetsArray();
	UpperWidgetSet();
}

void UPSLUserWidget::RefreshSubWidgetsArray()
{
	TArray<UPSLUserWidget*> SubWidgetsToRemove;
	for (auto& Widget : SubWidgets)
	{
		if (Widget == nullptr)
		{
			SubWidgetsToRemove.AddUnique(Widget);
		}
	}

	for (auto& WidgetToRemove : SubWidgetsToRemove)
	{
		if (SubWidgets.Contains(WidgetToRemove))
		{
			SubWidgets.Remove(WidgetToRemove);
		}
	}
}
