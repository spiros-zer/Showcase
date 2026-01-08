// Spyridon Zervos

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "Showcase/ShowcaseGame/AbilitySystem/ShowcaseGameplayAbilityTypes.h"
#include "ShowcaseGameplayWidget.generated.h"

class UShowcaseHotbarWidget;
class UGameplayAbility;
class UHorizontalBox;
class UAbilitySystemComponent;
class UShowcaseHotkey;
/**
 * 
 */
UCLASS()
class SHOWCASE_API UShowcaseGameplayWidget : public UCommonActivatableWidget
{
	GENERATED_BODY()
	
public:
	
	void ConfigureAbilities(const TMap<EShowcaseAbilityInputID, TSubclassOf<UGameplayAbility>>& Abilities);
	
protected:
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UShowcaseHotbarWidget> Hotbar;
	
	virtual void NativeOnActivated() override;
};
