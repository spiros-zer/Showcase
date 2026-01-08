// Spyridon Zervos


#include "ShowcaseAnimeInstance.h"

#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Showcase/ShowcaseGame/Character/ShowcaseCharacter.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(ShowcaseAnimeInstance)

void UShowcaseAnimeInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	
	OwnerCharacter = Cast<AShowcaseCharacter>(TryGetPawnOwner());
	if (!IsValid(OwnerCharacter)) return;
	
	OwnerMovementComponent = OwnerCharacter->GetCharacterMovement();
	check(OwnerMovementComponent);
}

void UShowcaseAnimeInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	
	if (!IsValid(OwnerCharacter) || !IsValid(OwnerMovementComponent)) return;
	
	Speed = OwnerCharacter->GetVelocity().Length();

	bIsJumping = OwnerMovementComponent->IsFalling();

	const FRotator ControlRot = OwnerCharacter->GetBaseAimRotation();
	
	LookRotOffset = UKismetMathLibrary::NormalizedDeltaRotator(ControlRot, OwnerCharacter->GetActorRotation());

}

bool UShowcaseAnimeInstance::GetIsGrounded() const
{
	return !bIsJumping;
}

bool UShowcaseAnimeInstance::GetIsJumping() const
{
	return bIsJumping;
}

float UShowcaseAnimeInstance::GetLookPitchOffset() const
{
	return LookRotOffset.Pitch;
}

float UShowcaseAnimeInstance::GetLookYawOffset() const
{
	return LookRotOffset.Yaw;
}

bool UShowcaseAnimeInstance::IsMoving() const
{
	return Speed != 0.f;
}

bool UShowcaseAnimeInstance::IsNotMoving() const
{
	return Speed == 0.f;
}

float UShowcaseAnimeInstance::GetSpeed() const
{
	return Speed;
}
