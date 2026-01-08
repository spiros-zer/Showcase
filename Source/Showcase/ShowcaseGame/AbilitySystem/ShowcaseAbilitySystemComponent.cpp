// Spyridon Zervos


#include "ShowcaseAbilitySystemComponent.h"

#include "ShowcaseAttributeSet.h"
#include "Showcase/ShowcaseGame/ShowcaseLogChannels.h"
#include "Showcase/ShowcaseGame/ShowcaseLogging.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(ShowcaseAbilitySystemComponent)

UShowcaseAbilitySystemComponent::UShowcaseAbilitySystemComponent()
{
	GetGameplayAttributeValueChangeDelegate(UShowcaseAttributeSet::GetHealthAttribute()).AddUObject(this, &ThisClass::HandleHealthUpdated);
}

void UShowcaseAbilitySystemComponent::ApplyInitialEffects()
{
	if (!GetOwner()->HasAuthority()) return;
	
	for (const TSubclassOf<UGameplayEffect>& EffectClass : InitialEffects)
	{
		ApplyGameplayEffect(EffectClass);
	}
	
	SHOWCASE_LOG(LogShowcase, TEXT("Applied initial effects."));
}

void UShowcaseAbilitySystemComponent::ApplyFullStatEffect()
{
	ApplyGameplayEffect(FullStatEffect);
}

void UShowcaseAbilitySystemComponent::ApplyRegenEffect()
{
	ApplyGameplayEffect(RegenEffect);
}

void UShowcaseAbilitySystemComponent::HandleHealthUpdated(const FOnAttributeChangeData& OnAttributeChangeData)
{
	const AActor* Owner = GetOwner();
	if (!IsValid(Owner))
	{
		SHOWCASE_ERROR(LogShowcaseAbilities, TEXT("Invalid Owner."));
		
		return;
	}
	if (!Owner->HasAuthority()) return;
	
	if (OnAttributeChangeData.NewValue <= 0)
	{
		check(DeathEffect);
		
		SHOWCASE_LOG(LogShowcaseAbilities, TEXT("Applying death effect."));
		
		ApplyGameplayEffect(DeathEffect);
	}
}

void UShowcaseAbilitySystemComponent::ApplyGameplayEffect(TSubclassOf<UGameplayEffect> GameplayEffect, int Level)
{
	// Server-side.
	
	const AActor* Owner = GetOwner();
	if (!IsValid(Owner))
	{
		SHOWCASE_ERROR(LogShowcaseAbilities, TEXT("Invalid Owner."));
		
		return;
	}
	if (!Owner->HasAuthority()) return;

	const FGameplayEffectSpecHandle EffectSpecHandle = MakeOutgoingSpec(GameplayEffect, Level, MakeEffectContext());
		
	ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
}

void UShowcaseAbilitySystemComponent::GiveInitialAbilities()
{
	// Server-side.
	
	if (!GetOwner()->HasAuthority()) return;
	
	// Giving abilities. These are given with level 0 to indicate they are not yet learned.
	
	for (const TPair<EShowcaseAbilityInputID, TSubclassOf<UGameplayAbility>>& AbilityPair : Abilities)
	{
		GiveAbility(FGameplayAbilitySpec(AbilityPair.Value, 0, static_cast<int32>(AbilityPair.Key), nullptr));
	}
	
	// Giving innate abilities.
	
	for (const TPair<EShowcaseAbilityInputID, TSubclassOf<UGameplayAbility>>& AbilityPair : InnateAbilities)
	{
		GiveAbility(FGameplayAbilitySpec(AbilityPair.Value, 1, static_cast<int32>(AbilityPair.Key), nullptr));
	}
	
	SHOWCASE_LOG(LogShowcase, TEXT("Applied initial abilities."));
}

const TMap<EShowcaseAbilityInputID, TSubclassOf<UGameplayAbility>>& UShowcaseAbilitySystemComponent::GetAbilities() const
{
	return Abilities;
}
