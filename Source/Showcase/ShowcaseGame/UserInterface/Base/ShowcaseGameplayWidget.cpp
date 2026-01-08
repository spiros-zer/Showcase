// Spyridon Zervos


#include "ShowcaseGameplayWidget.h"

#include "ShowcaseHotbarWidget.h"

void UShowcaseGameplayWidget::ConfigureAbilities(const TMap<EShowcaseAbilityInputID, TSubclassOf<UGameplayAbility>>& Abilities)
{
	Hotbar->ConfigureAbilities(Abilities);
}

void UShowcaseGameplayWidget::NativeOnActivated()
{
	Super::NativeOnActivated();
	
}
