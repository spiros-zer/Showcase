// Spyridon Zervos

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ShowcaseAbilitySystemStatics.generated.h"

class UInputAction;
class UGameplayAbility;
/**
 * 
 */
UCLASS()
class SHOWCASE_API UShowcaseAbilitySystemStatics : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	
	static FText GetPrimaryKeyDisplayText(APlayerController* PC, const UInputAction* Action);
	
	static float GetStaticCooldownDurationForAbility(const UGameplayAbility* Ability);
	
	static float GetStaticCostForAbility(const UGameplayAbility* Ability);
};
