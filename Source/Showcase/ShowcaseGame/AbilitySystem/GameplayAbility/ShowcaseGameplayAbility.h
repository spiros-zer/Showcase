// Spyridon Zervos

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "UObject/Object.h"
#include "ShowcaseGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class SHOWCASE_API UShowcaseGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
	
protected:
	
	TObjectPtr<UAnimInstance> GetOwnerAnimInstance() const;
	
	UFUNCTION()
	virtual void DealDamage(const TSubclassOf<UGameplayEffect> GameplayEffect, FGameplayEventData Data);
};
