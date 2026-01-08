// Spyridon Zervos


#include "ShowcaseHotbarWidget.h"

#include "Abilities/GameplayAbility.h"
#include "Showcase/ShowcaseGame/UserInterface/Foundation/ShowcaseHotkey.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(ShowcaseHotbarWidget)

void UShowcaseHotbarWidget::ConfigureAbilities(const TMap<EShowcaseAbilityInputID, TSubclassOf<UGameplayAbility>>& Abilities)
{
	OnEntryWidgetGenerated().AddUObject(this, &ThisClass::HotkeyGenerated);
	
	for (const TTuple<EShowcaseAbilityInputID, TSubclassOf<UGameplayAbility>>& AbilityPair : Abilities)
	{
		AddItem(AbilityPair.Value.GetDefaultObject());
	}
}

const FAbilityUIData* UShowcaseHotbarWidget::GetAbilityUIData(const TSubclassOf<UGameplayAbility>& AbilityClass) const
{
	check(IsValid(AbilityUIDataTable));
	
	for (auto& AbilityUIDataPair : AbilityUIDataTable->GetRowMap())
	{
		const FAbilityUIData* AbilityUIData = AbilityUIDataTable->FindRow<FAbilityUIData>(AbilityUIDataPair.Key, TEXT("Retrieving ability UI data."));
		if (!AbilityUIData) continue;
		return AbilityUIData;
	}
	
	return nullptr;
}

void UShowcaseHotbarWidget::HotkeyGenerated(UUserWidget& UserWidget)
{
	UShowcaseHotkey* Hotkey = Cast<UShowcaseHotkey>(&UserWidget);
	checkf(Hotkey, TEXT("Only UShowcaseHotkey are allowed in this type of list view."));
	Hotkey->ConfigureWithWidgetData(GetAbilityUIData(Hotkey->GetListItem<>()->GetClass()));
}
