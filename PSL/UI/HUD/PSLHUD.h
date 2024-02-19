// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "PSLHUD.generated.h"

class UPSLOverlayWidget;
class APSLGameMode;
class APSLCharacterBase;
struct FWidgetControllerParams;
class UOverlayWidgetController;
class UPSLUserWidget;
/**
 * 
 */
UCLASS()
class PSL_API APSLHUD : public AHUD
{
	GENERATED_BODY()

public:
	friend class APSLGameMode;

	
	UPROPERTY()
	TObjectPtr<UPSLOverlayWidget> OverlayWidget;

	UOverlayWidgetController* GetOverlayWidgetController(ACharacter* Character,
		UAbilitySystemComponent* ASC,
		UAttributeSet* AS);

	void InitOverlay(
		ACharacter* Character,
		UAbilitySystemComponent* ASC,
		UAttributeSet* AS);

	void AddToCharacterWidgetControllerMap(ACharacter* Character, UAbilitySystemComponent* ASC, UAttributeSet* AS);
protected:
	
	
private:
	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess = "true"))
	TMap<ACharacter*, UPSLWidgetController*> CharacterWidgetControllerMap;

	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess = "true"))
	TMap<ACharacter*, UPSLUserWidget*> CharacterUserWidgetMap;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UPSLUserWidget> OverlayWidgetClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UPSLUserWidget> CharacterStateWidgetClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;
};
