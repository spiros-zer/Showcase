// Spyridon Zervos

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "ShowcaseGameplayAbilityTypes.h"
#include "ShowcaseAbilitySystemComponent.generated.h"


UCLASS(meta=(BlueprintSpawnableComponent))
class SHOWCASE_API UShowcaseAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:

	UShowcaseAbilitySystemComponent();
	
	void ApplyInitialEffects();
	
	void ApplyFullStatEffect();
	
	void ApplyRegenEffect();
	
	/** 
	 * Gives both innate and learned abilities to the ASC.
	 */
	void GiveInitialAbilities();
	
	const TMap<EShowcaseAbilityInputID, TSubclassOf<UGameplayAbility>>& GetAbilities() const;
	
protected:
	
	UPROPERTY(EditDefaultsOnly, Category = "GameplayEffect")
	TArray<TSubclassOf<UGameplayEffect>> InitialEffects;

	UPROPERTY(EditDefaultsOnly, Category = "GameplayEffect")
	TSubclassOf<UGameplayEffect> DeathEffect;
	
	UPROPERTY(EditDefaultsOnly, Category = "GameplayEffect")
	TSubclassOf<UGameplayEffect> FullStatEffect;
	
	UPROPERTY(EditDefaultsOnly, Category = "GameplayEffect")
	TSubclassOf<UGameplayEffect> RegenEffect;
	
	/** 
	 * Unique abilities the character has to learn to perform. Mapped to an enum for activation through the enhanced input.
	 */
	UPROPERTY(EditDefaultsOnly, Category = "GameplayAbility")
	TMap<EShowcaseAbilityInputID, TSubclassOf<UGameplayAbility>> Abilities;
	
	/** 
	 * Abilities learnt by default. Mapped to an enum for activation through the enhanced input.
	 */
	UPROPERTY(EditDefaultsOnly, Category = "GameplayAbility")
	TMap<EShowcaseAbilityInputID, TSubclassOf<UGameplayAbility>> InnateAbilities;
	
private:
	
	void ApplyGameplayEffect(TSubclassOf<UGameplayEffect> GameplayEffect, int Level = 1);
	
	void HandleHealthUpdated(const FOnAttributeChangeData& OnAttributeChangeData);
};
