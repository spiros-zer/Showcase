// Spyridon Zervos


#include "ShowcaseCharacter.h"

#include "AbilitySystemComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Showcase/ShowcaseGame/ShowcaseLogChannels.h"
#include "Showcase/ShowcaseGame/ShowcaseLogging.h"
#include "Showcase/ShowcaseGame/AbilitySystem/ShowcaseAbilitySystemComponent.h"
#include "Showcase/ShowcaseGame/AbilitySystem/ShowcaseTags.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(ShowcaseCharacter)

AShowcaseCharacter::AShowcaseCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bUsePawnControlRotation = true;
	
	ViewCamera = CreateDefaultSubobject<UCameraComponent>("ViewCamera");
	ViewCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	
	bUseControllerRotationYaw = false;
	
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 720.f, 0.f);
}

void AShowcaseCharacter::PawnClientRestart()
{
	Super::PawnClientRestart();

	const APlayerController* OwningPlayerController = GetController<APlayerController>();
	if (!IsValid(OwningPlayerController))
	{
		SHOWCASE_ERROR(LogShowcase, TEXT("Invalid Player Controller."));
		
		return;
	}
	
	UEnhancedInputLocalPlayerSubsystem* InputSubsystem = OwningPlayerController->GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	if (!IsValid(InputSubsystem))
	{
		SHOWCASE_ERROR(LogShowcase, TEXT("Invalid Input Subsystem."));
		
		return;
	}
	InputSubsystem->RemoveMappingContext(GameplayInputMappingContext);
	InputSubsystem->AddMappingContext(GameplayInputMappingContext, 0);
}

void AShowcaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (!IsValid(EnhancedInputComponent))
	{
		SHOWCASE_ERROR(LogShowcase, TEXT("Invalid Enhanced Input Component."));
	}
	EnhancedInputComponent->BindAction(InputActionJump, ETriggerEvent::Started, this, &ThisClass::Jump);
	EnhancedInputComponent->BindAction(InputActionLook, ETriggerEvent::Triggered, this, &ThisClass::HandleLookInput);
	EnhancedInputComponent->BindAction(InputActionMove, ETriggerEvent::Triggered, this, &ThisClass::HandleMoveInput);

	for (const TPair<EShowcaseAbilityInputID, TObjectPtr<UInputAction>>& InputActionPair : GameplayAbilityInputActions)
	{
		EnhancedInputComponent->BindAction(InputActionPair.Value, ETriggerEvent::Started, this, &ThisClass::HandleAbilityInput, InputActionPair.Key);
	}
}

const TMap<EShowcaseAbilityInputID, TObjectPtr<UInputAction>>& AShowcaseCharacter::GetGameplayAbilityInputActions() const
{
	return GameplayAbilityInputActions;
}

void AShowcaseCharacter::OnDeath()
{
	APlayerController* PlayerController = GetController<APlayerController>();
	if (!IsValid(PlayerController)) return;
	PlayerController->DisableInput(PlayerController);
	
	FGameplayTagContainer TagsToRemove;
	TagsToRemove.AddTag(Ability::Regen);
	GetAbilitySystemComponent()->RemoveActiveEffectsWithGrantedTags(TagsToRemove);
}

void AShowcaseCharacter::OnRespawn()
{
	APlayerController* PlayerController = GetController<APlayerController>();
	if (!IsValid(PlayerController))
	{
		SHOWCASE_ERROR(LogShowcase, TEXT("Invalid Player Controller."));
		
		return;
	}
	PlayerController->EnableInput(PlayerController);
	
	UShowcaseAbilitySystemComponent* ShowcaseAsc = Cast<UShowcaseAbilitySystemComponent>(GetAbilitySystemComponent());
	check(ShowcaseAsc);
	ShowcaseAsc->ApplyRegenEffect();
}

void AShowcaseCharacter::HandleAbilityInput(const FInputActionValue& InputActionValue, EShowcaseAbilityInputID InputID)
{
	const bool bIsPressed = InputActionValue.Get<bool>();
	if (bIsPressed)
	{
		GetAbilitySystemComponent()->AbilityLocalInputPressed(static_cast<uint32>(InputID));
	}
	else
	{
		GetAbilitySystemComponent()->AbilityLocalInputReleased(static_cast<uint32>(InputID));
	}
}

void AShowcaseCharacter::HandleLookInput(const FInputActionValue& InputActionValue)
{
	const FVector2D InputValue = InputActionValue.Get<FVector2D>();
	
	AddControllerPitchInput(-InputValue.Y);
	
	AddControllerYawInput(InputValue.X);
}

void AShowcaseCharacter::HandleMoveInput(const FInputActionValue& InputActionValue)
{
	// Normalize input values.
	
	FVector2D InputValue = InputActionValue.Get<FVector2D>();
	InputValue.Normalize();
	
	// Set the right direction vector.
	
	const FVector LookRightVector = ViewCamera->GetRightVector();
	
	// Set the up direction vector.
	
	const FVector LookUpVector = FVector::CrossProduct(LookRightVector, FVector::UpVector);
	
	AddMovementInput(LookUpVector * InputValue.Y + LookRightVector * InputValue.X);
}
