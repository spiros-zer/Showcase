// Spyridon Zervos

#pragma once

#include "CoreMinimal.h"
#include "ShowcaseGameplayAbilityTypes.generated.h"

UENUM(BlueprintType)
enum class EShowcaseAbilityInputID : uint8
{
	None				UMETA(DisplayName = "None"),
	BasicAttack			UMETA(DisplayName = "Basic Attack"),
	AbilityOne			UMETA(DisplayName = "Ability One"),
	AbilityTwo			UMETA(DisplayName = "Ability Two")
};