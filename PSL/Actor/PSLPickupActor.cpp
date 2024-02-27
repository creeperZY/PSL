// Fill out your copyright notice in the Description page of Project Settings.


#include "PSLPickupActor.h"

#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PSL/PSL.h"
#include "PSL/Character/PSLCharacter.h"
#include "PSL/PlayerController/PSLPlayerController.h"

// Sets default values
APSLPickupActor::APSLPickupActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickupMesh"));
	SetRootComponent(PickupMesh);
	
	PickupMesh->SetCollisionObjectType(ECC_PickupActor);
	PickupMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	PickupMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	PickupMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);//for drop weapon
	PickupMesh->SetCollisionResponseToChannel(ECC_SkeletalMesh, ECollisionResponse::ECR_Ignore);//for drop weapon
	PickupMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);//for drop weapon

	AreaSphere = CreateDefaultSubobject<USphereComponent>(TEXT("AreaSphere"));
	AreaSphere->SetupAttachment(RootComponent);
	AreaSphere->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	AreaSphere->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	AreaSphere->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	AreaSphere->SetCollisionResponseToChannel(ECC_SkeletalMesh, ECollisionResponse::ECR_Overlap);

	EnableCustomDepth(true);
	ShowStencilColor(0);

	
}

void APSLPickupActor::EnableCustomDepth(bool bEnable)
{
	PickupMesh->SetRenderCustomDepth(bEnable);
}

void APSLPickupActor::ShowStencilColor(int32 ColorStencilValue)
{
	/*
	 * 0 No Outline
	 * 1 2 3 colors
	 * 255 xray
	 */
	if (PickupMesh)
	{
		PickupMesh->SetCustomDepthStencilValue(ColorStencilValue);
		PickupMesh->MarkRenderStateDirty();
	}
}

// Called when the game starts or when spawned
void APSLPickupActor::BeginPlay()
{
	Super::BeginPlay();

	AreaSphere->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	AreaSphere->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	AreaSphere->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	AreaSphere->SetCollisionResponseToChannel(ECC_SkeletalMesh, ECollisionResponse::ECR_Overlap);
	AreaSphere->OnComponentBeginOverlap.AddDynamic(this, &APSLPickupActor::OnSphereOverlap);
	AreaSphere->OnComponentEndOverlap.AddDynamic(this, &APSLPickupActor::OnSphereEndOverlap);


	PickupMesh->SetSimulatePhysics(true);
	PickupMesh->SetEnableGravity(true);
	PickupMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	PickupMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	PickupMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);//for drop weapon
	PickupMesh->SetCollisionResponseToChannel(ECC_SkeletalMesh, ECollisionResponse::ECR_Ignore);//for drop weapon
	PickupMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);//for drop weapon
		
	ShowStencilColor(0);
}


// Called every frame
void APSLPickupActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



void APSLPickupActor::Destroyed()
{
	Super::Destroyed();
	
}

void APSLPickupActor::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

}

void APSLPickupActor::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	
}
