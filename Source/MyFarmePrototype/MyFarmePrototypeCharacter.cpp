// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyFarmePrototypeCharacter.h"
#include "MyFarmePrototypePlayerController.h"
#include "Interactable.h"
#include "InventoryItem.h"
#include "AbilitySystemComponent.h"
#include "GASInstallPlayerState.h" 
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Materials/Material.h"
#include "Engine/World.h"

AMyFarmePrototypeCharacter::AMyFarmePrototypeCharacter()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Create the collection sphere
	CollectionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollectionSphere"));
	CollectionSphere->SetupAttachment(RootComponent);
	CollectionSphere->SetSphereRadius(200.f);

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

void AMyFarmePrototypeCharacter::Tick(float Deltatime)
{
	Super::Tick(Deltatime);

	CheckForInteractables();
}
UAbilitySystemComponent* AMyFarmePrototypeCharacter::GetAbilitySystemComponent()const
{
	if (const AGASInstallPlayerState* GASInstallPlayerState = GetPlayerState<AGASInstallPlayerState>())
	{
		return GASInstallPlayerState->GetAbilitySystemComponent();
	}
	return nullptr;
}
void AMyFarmePrototypeCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (const AGASInstallPlayerState* AGASInstallPlayerStateState = NewController->GetPlayerState<AGASInstallPlayerState>())
	{
		AGASInstallPlayerStateState->GetAbilitySystemComponent()->SetAvatarActor(this);
	}
}
void AMyFarmePrototypeCharacter::UnPossessed()
{
	Super::UnPossessed();

	if (const AGASInstallPlayerState* AGASInstallPlayerStateState = GetPlayerState<AGASInstallPlayerState>())
	{
		AGASInstallPlayerStateState->GetAbilitySystemComponent()->SetAvatarActor(nullptr);
	}
}
void AMyFarmePrototypeCharacter::CheckForInteractables()
{
	// Create a LineTrace to check for a hit
	FHitResult HitResult;

	int32 Range = 500;
	FVector StartTrace = TopDownCameraComponent->GetComponentLocation();
	FVector EndTrace = (TopDownCameraComponent->GetForwardVector() * Range) + StartTrace;

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);

	AMyFarmePrototypePlayerController* IController = Cast<AMyFarmePrototypePlayerController>(GetController());

	if (IController)
	{
		// Check if something is hit
		if (GetWorld()->LineTraceSingleByChannel(HitResult, StartTrace, EndTrace, ECC_Visibility, QueryParams))
		{
			// Cast the actor to AInteractable
			AInteractable* Interactable = Cast<AInteractable>(HitResult.GetActor());
			// If the cast is successful
			if (Interactable)
			{
				IController->CurrentInteractable = Interactable;
				return;
			}
		}

		IController->CurrentInteractable = nullptr;
	}
}