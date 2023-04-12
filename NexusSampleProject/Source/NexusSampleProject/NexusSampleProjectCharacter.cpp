// Fill out your copyright notice in the Description page of Project Settings.

#include "NexusSampleProjectCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Materials/Material.h"
#include "EnhancedInputSubsystems.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "Engine/World.h"

ANexusSampleProjectCharacter::ANexusSampleProjectCharacter()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

// Input
void ANexusSampleProjectCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (APlayerController* PC = Cast<APlayerController>(Controller))
	{
		if (ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(PC->Player))
		{
			if (UEnhancedInputLocalPlayerSubsystem* InputSystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
			{
				if (InputMapping.ToSoftObjectPath().IsValid())
				{
					InputSystem->AddMappingContext(InputMapping.LoadSynchronous(), 100);
				}
			}

		}
	}

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		PauseInputBinding = &EnhancedInput->BindAction(PauseAction.LoadSynchronous(), ETriggerEvent::Triggered, this, &ANexusSampleProjectCharacter::Pause);
	}
}

void ANexusSampleProjectCharacter::Pause(const FInputActionInstance& Instance)
{
	if (IsValid(PauseMenuWidget))
	{
		PauseMenuWidget->RemoveFromParent();
		PauseMenuWidget = nullptr;

		if (IsValid(CreatorSupportWidget))
		{
			CreatorSupportWidget->RemoveFromParent();
			CreatorSupportWidget = nullptr;
		}

		if (IsValid(LinkAccountWidget))
		{
			LinkAccountWidget->RemoveFromParent();
			LinkAccountWidget = nullptr;
		}
	}
	else
	{
		ensure (IsValid(PauseMenuWidgetClass));
		PauseMenuWidget = CreateWidget<UPauseMenuUserWidget>(GetWorld(), PauseMenuWidgetClass);
		if (IsValid(PauseMenuWidget))
		{
			PauseMenuWidget->AddToViewport();
		}
	}
}

void ANexusSampleProjectCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
}
