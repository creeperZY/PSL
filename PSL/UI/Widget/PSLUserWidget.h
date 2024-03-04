// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PSLUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class PSL_API UPSLUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetWidgetController(UObject* InWidgetController);
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UObject> WidgetController;

	UFUNCTION(BlueprintCallable)
	void SetUpperWidget(UPSLUserWidget* InWidget);
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UPSLUserWidget> UpperWidget;

	UPROPERTY(BlueprintReadOnly)
	TArray<UPSLUserWidget*> SubWidgets;

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void WidgetControllerSet();

	UFUNCTION(BlueprintImplementableEvent)
	void UpperWidgetSet();
	
	UFUNCTION(BlueprintImplementableEvent)
	void SetAsUpperWidgetBy(UPSLUserWidget* InWidget);
	
	UFUNCTION(BlueprintCallable)
	void RefreshSubWidgetsArray();
	
};
