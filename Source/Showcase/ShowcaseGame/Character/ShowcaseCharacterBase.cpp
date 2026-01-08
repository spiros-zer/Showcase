// Spyridon Zervos


#include "ShowcaseCharacterBase.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Showcase/ShowcaseGame/AbilitySystem/ShowcaseAbilitySystemComponent.h"
#include "Showcase/ShowcaseGame/AbilitySystem/ShowcaseAttributeSet.h"
#include  "Showcase/ShowcaseGame/AbilitySystem/ShowcaseTags.h"
#include "Showcase/ShowcaseGame/ShowcaseLogChannels.h"
#include "Showcase/ShowcaseGame/ShowcaseLogging.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(ShowcaseCharacterBase)

AShowcaseCharacterBase::AShowcaseCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;
	
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	ShowcaseAbilitySystemComponent = CreateDefaultSubobject<UShowcaseAbilitySystemComponent>(TEXT("ShowcaseAbilitySystemComponent"));
	
	ShowcaseAttributeSet = CreateDefaultSubobject<UShowcaseAttributeSet>(TEXT("ShowcaseAttributeSet"));
}

void AShowcaseCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
	BindToAbilitySystemComponent();
}

void AShowcaseCharacterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	// Server-side init for AIControllers.
	
	if (NewController && !NewController->IsPlayerController())
	{
		InitServerSide();
		
		SHOWCASE_LOG(LogShowcase, TEXT("Initialized ability actor info for server AI."));
	}
}

void AShowcaseCharacterBase::InitClientSide()
{
	ShowcaseAbilitySystemComponent->InitAbilityActorInfo(this, this);
	
	SHOWCASE_LOG(LogShowcase, TEXT("Initialized ability actor info for client."));
}

void AShowcaseCharacterBase::InitServerSide()
{
	ShowcaseAbilitySystemComponent->InitAbilityActorInfo(this, this);
	
	SHOWCASE_LOG(LogShowcase, TEXT("Initialized ability actor info for server."));
	
	ShowcaseAbilitySystemComponent->ApplyInitialEffects();
	ShowcaseAbilitySystemComponent->GiveInitialAbilities();
}

UAbilitySystemComponent* AShowcaseCharacterBase::GetAbilitySystemComponent() const
{
	return ShowcaseAbilitySystemComponent;
}

void AShowcaseCharacterBase::Server_MeleeTraceSample_Implementation(const TArray<FVector_NetQuantize>& CachedTraceLocations, const TArray<FVector_NetQuantize>& TraceLocations, const TArray<FName>& TraceSocketNames)
{
	const UWorld* World = GetWorld();
	if (!World) return;
	
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectType;
	ObjectType.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));
	
	// Ignore self.
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(this);

	for (int32 Index = 0; Index < TraceSocketNames.Num(); Index = Index + 2)
	{
		TArray<FHitResult> HitResults;
	
		const FVector SwordVector = TraceLocations[Index + 1] - TraceLocations[Index];
		const FVector SwordDir = SwordVector.GetSafeNormal();
		const float SwordLength = SwordVector.Size();
		const FQuat BoxRotation = SwordDir.ToOrientationQuat();
		constexpr float BladeThickness = 3.f; // Z
		constexpr float BladeWidth = 6.f; // Y
		const FVector BoxHalfExtent(SwordLength * 0.5f, BladeWidth * 0.5f, BladeThickness * 0.5f);
		const FVector BoxCenter = (TraceLocations[Index] + TraceLocations[Index + 1]) * 0.5f;
		const FVector PreviousBoxCenter = (CachedTraceLocations[Index] + CachedTraceLocations[Index + 1]) * 0.5f;

		
		UKismetSystemLibrary::BoxTraceMultiForObjects(
			GetWorld(),
			PreviousBoxCenter,
			BoxCenter,
			BoxHalfExtent,
			BoxRotation.Rotator(),
			ObjectType,
			false,
			ActorsToIgnore,
			EDrawDebugTrace::ForDuration,
			HitResults,
			true
		);
		
		for (const FHitResult& HitResult : HitResults)
		{
			AActor* HitActor = HitResult.GetActor();
			if (!HitActor) continue;

			if (AlreadyHitActors.Contains(HitActor)) continue;
			AlreadyHitActors.Add(HitActor);

			UAbilitySystemComponent* Asc = GetAbilitySystemComponent();
			if (!Asc) continue;

			FGameplayEffectContextHandle ContextHandle = Asc->MakeEffectContext();
			ContextHandle.AddHitResult(HitResult);

			FGameplayEventData Payload;
			Payload.Target = HitActor;
			Payload.ContextHandle = ContextHandle;
			Payload.Instigator = this;

			UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(this, Ability::Combo::Damage, Payload);
		}
	}
}

bool AShowcaseCharacterBase::Server_MeleeTraceSample_Validate(const TArray<FVector_NetQuantize>& CachedTraceLocations, const TArray<FVector_NetQuantize>& TraceLocations, const TArray<FName>& TraceSocketNames)
{
	// Calculate difference in socket distance between server and client received.
	
	for (int32 Index = 0; Index < TraceSocketNames.Num(); Index = Index + 2)
	{
		// Calculate original data.
		
		const FVector StartLocation = GetMesh()->GetSocketLocation(TraceSocketNames[Index]);

		const FVector EndLocation = GetMesh()->GetSocketLocation(TraceSocketNames[Index + 1]);
		
		const double OriginalDistance = FVector::Dist(StartLocation, EndLocation);
		
		// Calculate relative error for cached data.
		
		const double CalculatedCachedDistance = FVector::Dist(CachedTraceLocations[Index], CachedTraceLocations[Index + 1]);
		
		const double RelativeErrorCached = FMath::Abs(OriginalDistance - CalculatedCachedDistance) / OriginalDistance;
		
		if (RelativeErrorCached > 0.05f)
		{
			SHOWCASE_ERROR(LogShowcase, TEXT("Cached relative error exceeds quota (%f)."), RelativeErrorCached);
			
			return false;
		}
		
		// Calculate relative error for data.
		
		const double CalculatedDistance = FVector::Dist(TraceLocations[Index], TraceLocations[Index + 1]);
		
		const double RelativeError = FMath::Abs(OriginalDistance - CalculatedDistance) / OriginalDistance;
		
		if (RelativeError > 0.05f)
		{
			SHOWCASE_ERROR(LogShowcase, TEXT("Relative error exceeds quota (%f)."), RelativeError);
			
			return false;
		}
	}
	
	return true;
}

void AShowcaseCharacterBase::Server_MeleeAttackNotifyEnd_Implementation()
{
	AlreadyHitActors.Empty();
}

bool AShowcaseCharacterBase::Server_MeleeAttackNotifyEnd_Validate()
{
	return true;
}

const TMap<EShowcaseAbilityInputID, TSubclassOf<UGameplayAbility>>& AShowcaseCharacterBase::GetAbilities() const
{
	return ShowcaseAbilitySystemComponent->GetAbilities();
}

void AShowcaseCharacterBase::OnDeath()
{
	checkNoEntry();
}

void AShowcaseCharacterBase::OnRespawn()
{
	checkNoEntry();
}

void AShowcaseCharacterBase::BindToAbilitySystemComponent()
{
	if (!IsValid(ShowcaseAbilitySystemComponent))
	{
		SHOWCASE_ERROR(LogShowcase, TEXT("Invalid Ability System Component."));
		
		return;
	}
	
	ShowcaseAbilitySystemComponent->RegisterGameplayTagEvent(State::Dead).AddUObject(this, &ThisClass::DeathTagUpdated);
}

void AShowcaseCharacterBase::DeathTagUpdated(FGameplayTag GameplayTag, int NewCount)
{
	if (NewCount != 0)
	{
		SHOWCASE_LOG(LogShowcase, TEXT("Character %s died."), *GetName());
		
		StartDeathSequence();
	}
	else
	{
		SHOWCASE_LOG(LogShowcase, TEXT("Character %s respawning."), *GetName());
		
		Respawn();
	}
}

void AShowcaseCharacterBase::StartDeathSequence()
{
	OnDeath();
	
	PlayDeathAnimation();
	
	GetCharacterMovement()->SetMovementMode(MOVE_None);
	
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AShowcaseCharacterBase::PlayDeathAnimation()
{
	check(DeathMontage);
	
	SHOWCASE_VERBOSE(LogShowcase, TEXT("Playing death animation montage."));
	
	PlayAnimMontage(DeathMontage);
}

void AShowcaseCharacterBase::Respawn()
{
	OnRespawn();
	
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	
	GetCharacterMovement()->SetMovementMode(MOVE_Walking);
	
	// Auto blend out is disabled for the death anim montage, stop it manually here.
	
	GetMesh()->GetAnimInstance()->StopAllMontages(0.f);
	
	if (!IsValid(ShowcaseAbilitySystemComponent))
	{
		SHOWCASE_ERROR(LogShowcase, TEXT("Invalid Ability System Component."));
		
		return;
	}
	ShowcaseAbilitySystemComponent->ApplyFullStatEffect();
}
