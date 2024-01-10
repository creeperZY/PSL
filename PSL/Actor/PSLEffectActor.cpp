// Fill out your copyright notice in the Description page of Project Settings.

// For learning purpose only, test set var in AS, actually we should use GE

#include "PSLEffectActor.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "PSL/AbilitySystem/PSLAttributeSet.h"

APSLEffectActor::APSLEffectActor()
{
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(Mesh);
	
	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	Sphere->SetupAttachment(GetRootComponent());
	
}

void APSLEffectActor::BeginPlay()
{
	Super::BeginPlay();

	Sphere->OnComponentBeginOverlap.AddDynamic(this, &APSLEffectActor::OnOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &APSLEffectActor::EndOverlap);
}

void APSLEffectActor::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//TODO Change this to apply a Gameplay Effect, For now, using const_cast as a hack!
	if (IAbilitySystemInterface* ASCInterface = Cast<IAbilitySystemInterface>(OtherActor))
	{
		const UPSLAttributeSet* PSLAttributeSet = Cast<UPSLAttributeSet>(ASCInterface->GetAbilitySystemComponent()->GetAttributeSet(UPSLAttributeSet::StaticClass()));
		UPSLAttributeSet* MutablePSLAttributeSet = const_cast<UPSLAttributeSet*>(PSLAttributeSet);
		MutablePSLAttributeSet->SetHealth(PSLAttributeSet->GetHealth() + 25.f);
		Destroy();
	}
}

void APSLEffectActor::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

void APSLEffectActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

