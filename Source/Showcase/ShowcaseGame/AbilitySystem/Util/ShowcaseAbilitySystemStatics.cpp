// Spyridon Zervos


#include "ShowcaseAbilitySystemStatics.h"

#include "EnhancedInputSubsystems.h"
#include "Abilities/GameplayAbility.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Showcase/ShowcaseGame/ShowcaseLogChannels.h"
#include "Showcase/ShowcaseGame/ShowcaseLogging.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(ShowcaseAbilitySystemStatics)

float UShowcaseAbilitySystemStatics::GetStaticCooldownDurationForAbility(const UGameplayAbility* Ability)
{
	if (!IsValid(Ability))
	{
		SHOWCASE_ERROR_STATIC(LogShowcaseAbilities, TEXT("Invalid ability."));
		
		return -1.f;
	}
	
	const UGameplayEffect* CooldownEffect = Ability->GetCooldownGameplayEffect();
	if (!IsValid(CooldownEffect))
	{
		SHOWCASE_VERBOSE_STATIC(LogShowcaseAbilities, TEXT("Given ability has no cooldown."));
		
		return -1.f;
	}
	
	float CooldownDuration = 0.f;
	
	CooldownEffect->DurationMagnitude.GetStaticMagnitudeIfPossible(1, CooldownDuration);
	
	return CooldownDuration;
}

float UShowcaseAbilitySystemStatics::GetStaticCostForAbility(const UGameplayAbility* Ability)
{
	if (!IsValid(Ability))
	{
		SHOWCASE_ERROR_STATIC(LogShowcaseAbilities, TEXT("Invalid Ability."));
		
		return -1.f;
	}
	
	const UGameplayEffect* CostEffect = Ability->GetCostGameplayEffect();
	if (!IsValid(CostEffect))
	{
		SHOWCASE_VERBOSE_STATIC(LogShowcaseAbilities, TEXT("Given ability has no cost."));
		
		return -1.f;
	}
	
	if (CostEffect->Modifiers.IsEmpty())
	{
		SHOWCASE_VERBOSE_STATIC(LogShowcaseAbilities, TEXT("Cost modifiers don't alter anything."));
		
		return -1.f;
	}
	
	float Cost = 0.f;
	
	// TODO support multiple costs
	
	CostEffect->Modifiers[0].ModifierMagnitude.GetStaticMagnitudeIfPossible(1, Cost);
	
	return FMath::Abs(Cost);
}

FText UShowcaseAbilitySystemStatics::GetPrimaryKeyDisplayText(APlayerController* PlayerController, const UInputAction* Action)
{
	if (!IsValid(PlayerController) || !IsValid(Action))
	{
		SHOWCASE_ERROR_STATIC(LogShowcase, TEXT("Invalid input parameters."));
		
		return FText::GetEmpty();	
	}

	ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer();
	if (!IsValid(LocalPlayer))
	{
		SHOWCASE_ERROR_STATIC(LogShowcase, TEXT("Invalid Local Player."));
		
		return FText::GetEmpty();
	}
	
	UEnhancedInputLocalPlayerSubsystem* EnhancedInputSubsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	if (!IsValid(EnhancedInputSubsystem))
	{
		SHOWCASE_ERROR_STATIC(LogShowcase, TEXT("Invalid Enhanced Input Subsystem."));
		
		return FText::GetEmpty();
	}
	
	// What is currently mapped.
	
	const TArray<FKey> Keys = EnhancedInputSubsystem->QueryKeysMappedToAction(Action);
	
	if (Keys.Num() == 0)
	{
		return FText::FromString(TEXT("Unbound"));
	}
	
	return Keys[0].GetDisplayName();
}
