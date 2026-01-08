// Spyridon Zervos

#pragma once

#include "CoreMinimal.h"
#include "ShowcaseGameplayAbility.h"
#include "GA_Combo.generated.h"

/**
 * 
 */
UCLASS()
class SHOWCASE_API UGA_Combo : public UShowcaseGameplayAbility
{
	GENERATED_BODY()
	
public:
	
	UGA_Combo();

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	
protected:
	
	UPROPERTY(EditDefaultsOnly, Category = "AnimMontage")
	TObjectPtr<UAnimMontage> ComboMontage;
	
	/** 
	 * Maps the combo names as defined by their anim montage sections to gameplay effects.
	 */
	UPROPERTY(EditDefaultsOnly, Category = "GameplayEffect")
	TMap<FName, TSubclassOf<UGameplayEffect>> DamageEffectMap;
	
	/** 
	 * Default gameplay effect to use if none is found.
	 */
	UPROPERTY(EditDefaultsOnly, Category = "GameplayEffect")
	TSubclassOf<UGameplayEffect> DefaultDamageEffect;
	
private:
	
	UFUNCTION()
	void ComboChangedEventReceived(FGameplayEventData Payload);
	
	UFUNCTION()
	void ComboEndedEventReceived(FGameplayEventData Payload);

	UFUNCTION()
	void DealComboDamage(FGameplayEventData Data);
	
	UFUNCTION()
	void HandleInputPressed(float TimeWaited);
	
	void TryCommitCombo();
	
	void SetupWaitComboInputPress();
	
	TSubclassOf<UGameplayEffect> GetDamageEffectForCurrentCombo();
	
	FName NextComboName;
};
