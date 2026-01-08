// Spyridon Zervos

#pragma once

#include "CoreMinimal.h"
#include "ShowcaseGameplayAbility.h"
#include "GA_BladeSiphon.generated.h"

/**
 * 
 */
UCLASS()
class SHOWCASE_API UGA_BladeSiphon : public UShowcaseGameplayAbility
{
	GENERATED_BODY()
	
public:
	
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	
protected:
	
	UPROPERTY(EditDefaultsOnly, Category = "AnimMontage")
	TObjectPtr<UAnimMontage> BladeSiphonMontage;
	
	/** 
	 * Default gameplay effect to use if none is found.
	 */
	UPROPERTY(EditDefaultsOnly, Category = "GameplayEffect")
	TSubclassOf<UGameplayEffect> BladeSiphonDamageEffect;
	
private:
	
	UFUNCTION()
	void DealBladeSiphonDamage(FGameplayEventData Data);
};
