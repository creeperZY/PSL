// Fill out your copyright notice in the Description page of Project Settings.

#include "Weapon.h"

#include "Casing.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Kismet/KismetMathLibrary.h"
#include "Net/UnrealNetwork.h"
#include "PSL/Character/PSLCharacter.h"
#include "PSL/EasyMacros.h"
#include "PSL/PlayerController/PSLPlayerController.h"

// Sets default values
AWeapon::AWeapon()
{
	PrimaryActorTick.bCanEverTick = false;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	SetRootComponent(WeaponMesh);

	WeaponMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	WeaponMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	AreaSphere = CreateDefaultSubobject<USphereComponent>(TEXT("AreaSphere"));
	AreaSphere->SetupAttachment(RootComponent);
	AreaSphere->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	AreaSphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	PickupWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("PickupWidget"));
	PickupWidget->SetupAttachment(RootComponent);

	EnableCustomDepth(true);
	ShowStencilColor(0);
}

void AWeapon::BeginPlay()
{
	Super::BeginPlay();

	AreaSphere->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	AreaSphere->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	AreaSphere->OnComponentBeginOverlap.AddDynamic(this, &AWeapon::OnSphereOverlap);
	AreaSphere->OnComponentEndOverlap.AddDynamic(this, &AWeapon::OnSphereEndOverlap);
	
	OnDropped();
	
	ShowPickupWidget(false);

}

void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWeapon::SetOwner(AActor* NewOwner)
{
	Super::SetOwner(NewOwner);
	PSLOwnerCharacter = PSLOwnerCharacter == nullptr ? Cast<APSLCharacter>(NewOwner) : PSLOwnerCharacter;
	if (PSLOwnerCharacter)
	{
		PSLOwnerController = PSLOwnerController == nullptr ? Cast<APSLPlayerController>(PSLOwnerCharacter->Controller) : PSLOwnerController; 
	}
}

void AWeapon::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APSLCharacter* PSLCharacter = Cast<APSLCharacter>(OtherActor);
	if (PSLCharacter)
	{
		PSLCharacter->SetOverlappingWeapon(this);
		ShowPickupWidget(true);
		ShowStencilColor(1);
	}
}

void AWeapon::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	APSLCharacter* PSLCharacter = Cast<APSLCharacter>(OtherActor);
	if (PSLCharacter)
	{
		PSLCharacter->SetOverlappingWeapon(nullptr);
		ShowPickupWidget(false);
		ShowStencilColor(0);
	}
}

void AWeapon::ShowPickupWidget(bool bShowWidget)
{
	if (PickupWidget)
	{
		PickupWidget->SetVisibility(bShowWidget);
	}
}

void AWeapon::ShowStencilColor(int32 ColorStencilValue)
{
	/*
	 * 0 No Outline
	 * 1 2 3 colors
	 * 255 xray
	 */
	if (WeaponMesh)
	{
		WeaponMesh->SetCustomDepthStencilValue(ColorStencilValue);
		WeaponMesh->MarkRenderStateDirty();
	}
}


void AWeapon::SetHUDAmmo()
{
	// I WANT THIS IS A DELEGATE SO maybe a new name
}

void AWeapon::SpendRound()
{
	CurrentAmmo = FMath::Clamp(CurrentAmmo - 1, 0, MagCapacity);
	SetHUDAmmo();
}



void AWeapon::SetWeaponState(EWeaponState State)
{
	WeaponState = State;
	OnWeaponStateSet();
}


void AWeapon::OnWeaponStateSet()
{
	switch (WeaponState)
	{
	case EWeaponState::EWS_Equipped:
		OnEquipped();
		break;
	case EWeaponState::EWS_EquippedBack:
		OnEquippedBack();
		break;
	case EWeaponState::EWS_Dropped:
		OnDropped();
		break;
	}
}


void AWeapon::OnEquipped()
{
	ShowPickupWidget(false);
	AreaSphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	WeaponMesh->SetSimulatePhysics(false);
	WeaponMesh->SetEnableGravity(false);
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	if (WeaponType == EWeaponType::EWT_SubmachineGun)
	{
		WeaponMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		WeaponMesh->SetEnableGravity(true);
		WeaponMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	}

	ShowStencilColor(255);
	PSLOwnerCharacter = PSLOwnerCharacter == nullptr ? Cast<APSLCharacter>(GetOwner()) : PSLOwnerCharacter;
	if (PSLOwnerCharacter)
	{
		PSLOwnerController = PSLOwnerController == nullptr ? Cast<APSLPlayerController>(PSLOwnerCharacter->Controller) : PSLOwnerController; 
	}
}

void AWeapon::OnEquippedBack()
{
	ShowPickupWidget(false);
	AreaSphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	WeaponMesh->SetSimulatePhysics(false);
	WeaponMesh->SetEnableGravity(false);
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	if (WeaponType == EWeaponType::EWT_SubmachineGun)
	{
		WeaponMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		WeaponMesh->SetEnableGravity(true);
		WeaponMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	}

	ShowStencilColor(255);
	PSLOwnerCharacter = PSLOwnerCharacter == nullptr ? Cast<APSLCharacter>(GetOwner()) : PSLOwnerCharacter;
	if (PSLOwnerCharacter)
	{
		PSLOwnerController = PSLOwnerController == nullptr ? Cast<APSLPlayerController>(PSLOwnerCharacter->Controller) : PSLOwnerController; 
	}
}

void AWeapon::OnDropped()
{
	AreaSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	WeaponMesh->SetSimulatePhysics(true);
	WeaponMesh->SetEnableGravity(true);
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	WeaponMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	WeaponMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);//for drop weapon
	WeaponMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);//for drop weapon
		
	ShowStencilColor(0);
	PSLOwnerCharacter = PSLOwnerCharacter == nullptr ? Cast<APSLCharacter>(GetOwner()) : PSLOwnerCharacter;
	if (PSLOwnerCharacter)
	{
		PSLOwnerController = PSLOwnerController == nullptr ? Cast<APSLPlayerController>(PSLOwnerCharacter->Controller) : PSLOwnerController; 
	}
}


void AWeapon::Fire(const FVector& HitTarget)
{
	if (FireAnimation)
	{
		WeaponMesh->PlayAnimation(FireAnimation, false);
	}
	if (CasingClass)
	{
		const USkeletalMeshSocket* AmmoEjectSocket = WeaponMesh->GetSocketByName(FName("AmmoEject"));
		if (AmmoEjectSocket)
		{
			FTransform SocketTransform = AmmoEjectSocket->GetSocketTransform(WeaponMesh);
			
			UWorld* World = GetWorld();
			if (World)
			{
				World->SpawnActor<ACasing>(CasingClass, SocketTransform.GetLocation(), SocketTransform.GetRotation().Rotator());
			}
		}
	}
	SpendRound();	
}


FVector AWeapon::TraceEndWithScatter(const FVector& HitTarget)
{
	const USkeletalMeshSocket* MuzzleFlashSocket = GetWeaponMesh()->GetSocketByName("MuzzleFlash");
	if(MuzzleFlashSocket == nullptr) return FVector();
	const FTransform SocketTransform = MuzzleFlashSocket->GetSocketTransform(GetWeaponMesh());
	const FVector TraceStart = SocketTransform.GetLocation();
	

	const FVector ToTargetNormalized = (HitTarget - TraceStart).GetSafeNormal();
	const FVector SphereCenter = TraceStart + ToTargetNormalized * DistanceToSphere;
	const FVector RandVec = UKismetMathLibrary::RandomUnitVector() * FMath::FRandRange(0.f, SphereRadius);
	const FVector EndLoc = SphereCenter + RandVec;
	const FVector ToEndLoc = EndLoc - TraceStart;

	/*
	DrawDebugSphere(GetWorld(), SphereCenter, SphereRadius, 12, FColor::Red, true);
	DrawDebugSphere(GetWorld(), EndLoc, 4.f, 12, FColor::Orange, true);
	DrawDebugLine(GetWorld(), TraceStart, FVector(TraceStart + ToEndLoc * TRACE_LENGTH / ToEndLoc.Size()), FColor::Cyan, true);
	*/
	
	return FVector(TraceStart + ToEndLoc * TRACE_LENGTH / ToEndLoc.Size());
}

void AWeapon::EnableCustomDepth(bool bEnable)
{
	if (WeaponMesh)
	{
		WeaponMesh->SetRenderCustomDepth(bEnable);
	}
}

void AWeapon::Dropped()
{
	SetWeaponState(EWeaponState::EWS_Dropped);
	FDetachmentTransformRules DetachRules(EDetachmentRule::KeepWorld, true);
	WeaponMesh->DetachFromComponent(DetachRules);
	SetOwner(nullptr);
	PSLOwnerCharacter = nullptr;
	PSLOwnerController = nullptr;
}

void AWeapon::AddAmmo(int32 AmmoToAdd)
{
	CurrentAmmo = FMath::Clamp(CurrentAmmo + AmmoToAdd, 0, MagCapacity);
	SetHUDAmmo();
}


bool AWeapon::IsEmpty()
{
	return CurrentAmmo <= 0;
}

bool AWeapon::IsFull()
{
	return CurrentAmmo == MagCapacity;
}
