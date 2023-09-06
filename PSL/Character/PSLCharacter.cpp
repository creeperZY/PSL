// Copyright Epic Games, Inc. All Rights Reserved.

#include "PSLCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/PostProcessComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "PSL/PSLComponents/CombatComponent.h"
#include "PSL/Weapon/Weapon.h"
#include "PSL/EasyMacros.h"
#include "PSL/PSLComponents/AbilityComponent.h"
#include "Components/PrimitiveComponent.h"
#include "PSL/PlayerController/PSLPlayerController.h"
#include "PSL/Weapon/ProjectileTossGrenade.h"


//////////////////////////////////////////////////////////////////////////
// APSLCharacter

APSLCharacter::APSLCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 850.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->NavAgentProps.bCanCrouch = true;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetMesh());
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller
	CameraBoom->bEnableCameraLag = true;
	CameraBoom->CameraLagSpeed = 16.f;

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)

	Combat = CreateDefaultSubobject<UCombatComponent>(TEXT("CombatComponent"));
	Ability = CreateDefaultSubobject<UAbilityComponent>(TEXT("AbilityComponent"));
	PostProcess = CreateDefaultSubobject<UPostProcessComponent>(TEXT("PostProcessComponent"));

	TurningInPlace = ETurningInPlace::ETIP_NotTurning;

	AttachedGrenade = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Attached Grenade"));
	AttachedGrenade->SetupAttachment(GetMesh(), FName("LeftHandSocketGrenade"));
	AttachedGrenade->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}


void APSLCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	//APSLGameMode* GameModeRef = Cast<APSLGameMode>(GetWorld()->GetAuthGameMode());
	//check(GameModeRef);

}

void APSLCharacter::PlayFireMontage(bool bAiming)
{
	if(Combat == nullptr || Combat->EquippedWeapon == nullptr) return;

	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance && FireWeaponMontage)
	{
		AnimInstance->Montage_Play(FireWeaponMontage);
		FName SectionName;
		
		switch (Combat->EquippedWeapon->GetEquippedPoseType())
		{
		case EEquippedPoseType::EEPT_RiflePose:
			SectionName = bAiming ? FName("RifleAim") : FName("RifleHip");
			break;
		case EEquippedPoseType::EEPT_PistolPose:
			SectionName = bAiming ? FName("PistolAim") : FName("PistolHip");
			break;
		}

		AnimInstance->Montage_JumpToSection(SectionName);
	}
}

void APSLCharacter::PlayReloadMontage()
{
}

void APSLCharacter::PlayElimMontage()
{
}

void APSLCharacter::PlayThrowGrenadeMontage()
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance && ThrowGrenadeMontage)
	{
		AnimInstance->Montage_Play(ThrowGrenadeMontage);
	}
}

void APSLCharacter::PlaySwapMontage()
{
}

void APSLCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputMappingContext, 0);
		}
	}
	
	SetShowXRayWhenCharacterOccluded();
	SetTurnDelegate();

}

void APSLCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (TurnBeforeEquipTimeline.IsPlaying())
	{
		TurnBeforeEquipTimeline.TickTimeline(DeltaSeconds);
	}
	
	AimOffset(DeltaSeconds);
	InterpCameraFOV(DeltaSeconds);
	HideCharacterIfCameraClose();
	
}

void APSLCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	if (Combat)
	{
		Combat->Character = this;
	}
	if (Ability)
	{
		Ability->Character = this;
	}
}

//////////////////////////////////////////////////////////////////////////
// Input

void APSLCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &APSLCharacter::Jump);
		//EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APSLCharacter::Move);
		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APSLCharacter::Look);

		EnhancedInputComponent->BindAction(EquipAction, ETriggerEvent::Triggered, this, &APSLCharacter::EquipButtonPressed);

		EnhancedInputComponent->BindAction(DropAction, ETriggerEvent::Triggered, this, &APSLCharacter::DropButtonPressed);

		EnhancedInputComponent->BindAction(EquipFirstAction, ETriggerEvent::Triggered, this, &APSLCharacter::EquipFirstButtonPressed);

		EnhancedInputComponent->BindAction(EquipSecondAction, ETriggerEvent::Triggered, this, &APSLCharacter::EquipSecondButtonPressed);

		EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Triggered, this, &APSLCharacter::CrouchButtonPressed);

		EnhancedInputComponent->BindAction(AimAction, ETriggerEvent::Triggered, this, &APSLCharacter::AimButtonPressed);
		EnhancedInputComponent->BindAction(AimAction, ETriggerEvent::Completed, this, &APSLCharacter::AimButtonReleased);

		EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Triggered, this, &APSLCharacter::FireButtonPressed);
		EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Completed, this, &APSLCharacter::FireButtonReleased);

		EnhancedInputComponent->BindAction(GrenadeAction, ETriggerEvent::Triggered, this, &APSLCharacter::GrenadeButtonPressed);
		EnhancedInputComponent->BindAction(GrenadeAction, ETriggerEvent::Canceled, this, &APSLCharacter::GrenadeButtonCanceled);
		EnhancedInputComponent->BindAction(GrenadeAction, ETriggerEvent::Completed, this, &APSLCharacter::GrenadeButtonCompleted);
	}

}

void APSLCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void APSLCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void APSLCharacter::Jump()
{
	if (bIsCrouched)
	{
		UnCrouch();
	}
	else
	{
		Super::Jump();
	}
}


void APSLCharacter::EquipButtonPressed()
{
	if (GetCharacterMovement()->IsFalling()) return;
	if (Combat && OverlappingWeapon)
	{
		TurnBeforeEquip();
		Combat->EquipWeapon(OverlappingWeapon);
	}
}

void APSLCharacter::EquipFirstButtonPressed()
{
	if (GetCharacterMovement()->IsFalling()) return;
	if (Combat && Combat->FirstWeapon)
	{
		TurnBeforeEquip();
		Combat->EquipFirstWeapon();
	}
}

void APSLCharacter::EquipSecondButtonPressed()
{
	if (GetCharacterMovement()->IsFalling()) return;
	if (Combat && Combat->SecondWeapon)
	{
		TurnBeforeEquip();
		Combat->EquipSecondWeapon();
	}
}


void APSLCharacter::DropButtonPressed()
{
	if (Combat)
	{
		Combat->DropEquippedWeapon();
	}
}

void APSLCharacter::CrouchButtonPressed()
{
	if (bIsCrouched)
	{
		UnCrouch();
	}
	else
	{
		Crouch();
	}
}

void APSLCharacter::AimButtonPressed()
{
	if (Combat)
	{
		Combat->SetAiming(true);
	}
}

void APSLCharacter::AimButtonReleased()
{
	if (Combat)
	{
		Combat->SetAiming(false);
	}
}

void APSLCharacter::FireButtonPressed()
{
	if (Combat)
	{
		Combat->FireButtonPressed(true);
	}
}

void APSLCharacter::FireButtonReleased()
{
	if (Combat)
	{
		Combat->FireButtonPressed(false);
	}
}

void APSLCharacter::GrenadeButtonPressed()
{
	PRINT_STR("SHOW GRENADE SWITCH UI OR SWITCH GRENADE TYPE?");
	//this func run twice
}

void APSLCharacter::GrenadeButtonCanceled()
{
	if (Combat)
	{
		Combat->ThrowGrenade();
	}
}

void APSLCharacter::GrenadeButtonCompleted()
{
	PRINT_STR("CLOSE UI");
}


void APSLCharacter::InterpCameraFOV(float DeltaSeconds)
{
	if (IsWeaponEquipped())
	{
		CurrentFOV = FMath::FInterpTo(CurrentFOV, EquippedFOV, DeltaSeconds, InterpSpeed);
		CurrentSocketOffset = FMath::VInterpTo(CurrentSocketOffset, EquippedSocketOffset, DeltaSeconds, InterpSpeed);
		CurrentTargetArmLength = FMath::FInterpTo(CurrentTargetArmLength, EquippedTargetArmLength, DeltaSeconds, InterpSpeed);
		if (IsAiming())
		{
			AimFOV = GetEquippedWeapon()->GetZoomedFOV();
			CurrentFOV = FMath::FInterpTo(CurrentFOV, AimFOV, DeltaSeconds, InterpSpeed);
		}
		else
		{
			CurrentFOV = FMath::FInterpTo(CurrentFOV, EquippedFOV, DeltaSeconds, InterpSpeed);
		}
	}
	else
	{
		CurrentFOV = FMath::FInterpTo(CurrentFOV, UnequippedFOV, DeltaSeconds, InterpSpeed);
		CurrentSocketOffset = FMath::VInterpTo(CurrentSocketOffset, UnequippedSocketOffset, DeltaSeconds, InterpSpeed);
		CurrentTargetArmLength = FMath::FInterpTo(CurrentTargetArmLength, UnequippedTargetArmLength, DeltaSeconds, InterpSpeed);
	}
	FollowCamera->FieldOfView = CurrentFOV;
	CameraBoom->SocketOffset = CurrentSocketOffset;
	CameraBoom->TargetArmLength = CurrentTargetArmLength;
}


void APSLCharacter::HideCharacterIfCameraClose()
{
	/*bool bShouldHide = (FollowCamera->GetComponentLocation() - GetActorLocation()).Size() < CameraThreshold;
	GetMesh()->SetVisibility(!bShouldHide);
	if(Combat && Combat->EquippedWeapon && Combat->EquippedWeapon->GetWeaponMesh())
	{
		Combat->EquippedWeapon->GetWeaponMesh()->bOwnerNoSee = bShouldHide; 
	}
	if(Combat && Combat->FirstWeapon && Combat->FirstWeapon->GetWeaponMesh())
	{
		Combat->FirstWeapon->GetWeaponMesh()->bOwnerNoSee = bShouldHide; 
	}
	if(Combat && Combat->SecondWeapon && Combat->SecondWeapon->GetWeaponMesh())
	{
		Combat->SecondWeapon->GetWeaponMesh()->bOwnerNoSee = bShouldHide; 
	}
	if (AttachedGrenade)
	{
		AttachedGrenade->bOwnerNoSee = bShouldHide;
	}*/
}

float APSLCharacter::CalculateSpeed()
{
	FVector Velocity = GetVelocity();
	Velocity.Z = 0.f;
	return Velocity.Size();
}

void APSLCharacter::AimOffset(float DeltaTime)
{
	if (Combat && Combat->EquippedWeapon == nullptr) return;
	if (!bTurnFinished) return;
	float Speed = CalculateSpeed();
	bool bIsInAir = GetCharacterMovement()->IsFalling();
	//if (bIsInAir)
	//{
		//AO_Pitch = FMath::FInterpTo(AO_Pitch, 0.f, DeltaTime, 15.f);
		//return;
	//}
	if (Speed == 0.f && !bIsInAir) // standing still, not jumping
	{
		FRotator CurrentAimRotation = FRotator(0.f, GetBaseAimRotation().Yaw, 0.f);
		FRotator DeltaAimRotation = UKismetMathLibrary::NormalizedDeltaRotator(CurrentAimRotation, StartingAimRotation);
		AO_Yaw = DeltaAimRotation.Yaw;

		if (Combat->CombatState == ECombatState::ECS_ThrowingGrenade)
		{
			if (AO_Yaw > 45.f) TurningInPlace = ETurningInPlace::ETIP_Right;
			if (AO_Yaw < -45.f) TurningInPlace = ETurningInPlace::ETIP_Left;
			if (FMath::Abs(AO_Yaw) < 15.f) TurningInPlace = ETurningInPlace::ETIP_NotTurning;
		}
		
		if (TurningInPlace == ETurningInPlace::ETIP_NotTurning)
		{
			InterpAO_Yaw = AO_Yaw;
		}
		bUseControllerRotationYaw = true;
		TurnInPlace(DeltaTime);
	}
	// throwing grenades or melee
	if (Speed > 0.f || bIsInAir) // running, or jumping
	{
        StartingAimRotation = FRotator(0.f, GetBaseAimRotation().Yaw, 0.f);
        AO_Yaw = FMath::FInterpTo(AO_Yaw, 0.f, DeltaTime, 15.f);
		//AO_Yaw = 0.f;
		bUseControllerRotationYaw = true;
        TurningInPlace = ETurningInPlace::ETIP_NotTurning;
	}
	AO_Pitch = FMath::FInterpTo(AO_Pitch, GetBaseAimRotation().Pitch, DeltaTime, 15.f);
	//AO_Pitch = GetBaseAimRotation().Pitch;
}

void APSLCharacter::TurnInPlace(float DeltaTime)
{
	if (AO_Yaw > 85.f)	//90.f?
	{
		TurningInPlace = ETurningInPlace::ETIP_Right;
	}
	else if (AO_Yaw < -85.f)
	{
		TurningInPlace = ETurningInPlace::ETIP_Left;
	}
	if (TurningInPlace != ETurningInPlace::ETIP_NotTurning)
	{
		InterpAO_Yaw = FMath::FInterpTo(InterpAO_Yaw, 0.f, DeltaTime, 4.f);
		AO_Yaw = InterpAO_Yaw;
		if (FMath::Abs(AO_Yaw) < 15.f)
		{
			TurningInPlace = ETurningInPlace::ETIP_NotTurning;
			StartingAimRotation = FRotator(0.f, GetBaseAimRotation().Yaw, 0.f);
		}
	}
}

void APSLCharacter::SetTurnDelegate()
{
	FOnTimelineFloat TurnTrack;
	FOnTimelineEvent TurnTrackFinished;
	TurnTrack.BindDynamic(this, &APSLCharacter::TurnProgress);
	TurnTrackFinished.BindDynamic(this, &APSLCharacter::OnTurnFinished);
	TurnBeforeEquipTimeline.AddInterpFloat(TurnCurve, TurnTrack);
	TurnBeforeEquipTimeline.SetTimelineFinishedFunc(TurnTrackFinished);
}


void APSLCharacter::TurnBeforeEquip()
{
	if (bUseControllerRotationYaw) return;
	if (TurnCurve == nullptr) return;
	
	bTurnFinished = false;
	StartingRotation = GetActorRotation();
	AimRotation = StartingRotation;
	AimRotation.Yaw = GetBaseAimRotation().Yaw;
	TurnBeforeEquipTimeline.PlayFromStart();
}

void APSLCharacter::TurnProgress(float Alpha)
{
	FRotator TurnRotation = FMath::Lerp(StartingRotation, AimRotation, Alpha);
	if (GetEquippedWeapon()) SetActorRotation(TurnRotation);
}

void APSLCharacter::OnTurnFinished()
{
	bTurnFinished = true;
	if (GetEquippedWeapon())
	{
		bUseControllerRotationYaw = true;
		GetCharacterMovement()->bOrientRotationToMovement = false;
	}
	else
	{
		bUseControllerRotationYaw = false;
		GetCharacterMovement()->bOrientRotationToMovement = true;
	}
}


void APSLCharacter::SetShowXRayWhenCharacterOccluded()
{
	APSLPlayerController* PSLController = Cast<APSLPlayerController>(GetController());
	if(PSLController)
	{
		GetMesh()->SetRenderCustomDepth(true);
		GetMesh()->SetCustomDepthStencilValue(0);
		GetMesh()->MarkRenderStateDirty();
		if (Combat && Combat->FirstWeapon)
		{
			Combat->FirstWeapon->ShowStencilColor(0);
		}
		if (Combat && Combat->SecondWeapon)
		{
			Combat->SecondWeapon->ShowStencilColor(0);
		}
	}
	else
	{
		GetMesh()->SetRenderCustomDepth(true);
		GetMesh()->SetCustomDepthStencilValue(255);
		GetMesh()->MarkRenderStateDirty();
		if (Combat && Combat->FirstWeapon)
		{
			Combat->FirstWeapon->ShowStencilColor(255);
		}
		if (Combat && Combat->SecondWeapon)
		{
			Combat->SecondWeapon->ShowStencilColor(255);
		}
	}
}

ECombatState APSLCharacter::GetCombatState() const
{
	if(Combat == nullptr) return ECombatState::ECS_MAX;
	return Combat->CombatState;
}

FVector APSLCharacter::GetHitTarget() const
{
	if(Combat == nullptr) return FVector();
	//return Combat->HitTarget;
	return Combat->TraceEnd;//xxx
}

bool APSLCharacter::IsWeaponEquipped()
{
	return (Combat && Combat->EquippedWeapon);
}

EEquippedPoseType APSLCharacter::GetEquippedPoseType()
{
	if (Combat && Combat->EquippedWeapon)
		return Combat->EquippedWeapon->GetEquippedPoseType();
	return EEquippedPoseType::EEPT_PistolPose;
	
}

bool APSLCharacter::IsAiming()
{
	return (Combat && Combat->bAiming);
}

AWeapon* APSLCharacter::GetEquippedWeapon()
{
	if (Combat == nullptr) return nullptr;
	return Combat->EquippedWeapon;
}

