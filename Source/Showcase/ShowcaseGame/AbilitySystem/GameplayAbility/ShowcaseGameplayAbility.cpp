// Spyridon Zervos


#include "ShowcaseGameplayAbility.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Showcase/ShowcaseGame/ShowcaseLogChannels.h"
#include "Showcase/ShowcaseGame/ShowcaseLogging.h"

TObjectPtr<UAnimInstance> UShowcaseGameplayAbility::GetOwnerAnimInstance() const
{
	const USkeletalMeshComponent* OwnerSkeletalMeshComponent = GetOwningComponentFromActorInfo();
	if (!IsValid(OwnerSkeletalMeshComponent))
	{
		SHOWCASE_ERROR(LogShowcaseAbilities, TEXT("Invalid owner."));
		
		return nullptr;
	}
	
	return OwnerSkeletalMeshComponent->GetAnimInstance();
}

void UShowcaseGameplayAbility::DealDamage(const TSubclassOf<UGameplayEffect> GameplayEffect, FGameplayEventData Data)
{
	const float Level = GetAbilityLevel(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo());

	const FHitResult HitResult = *Data.ContextHandle.GetHitResult();
	
	FGameplayEffectContextHandle EffectContextHandle = MakeEffectContext(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo());
	EffectContextHandle.AddHitResult(HitResult);

	const FGameplayEffectSpecHandle EffectSpecHandle = MakeOutgoingGameplayEffectSpec(GameplayEffect, Level);
	EffectSpecHandle.Data->SetContext(EffectContextHandle);
	
	SHOWCASE_VERBOSE(LogShowcaseAbilities, TEXT("Applying damage effect %s to %s."), *GameplayEffect->GetName(), *HitResult.GetActor()->GetName());
	
	ApplyGameplayEffectSpecToTarget(
			GetCurrentAbilitySpecHandle(), 
			CurrentActorInfo, 
			CurrentActivationInfo, 
			EffectSpecHandle, 
			UAbilitySystemBlueprintLibrary::AbilityTargetDataFromActor(HitResult.GetActor()));
}
