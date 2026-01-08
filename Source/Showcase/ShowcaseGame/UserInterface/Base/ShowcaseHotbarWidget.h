// Spyridon Zervos

#pragma once

#include "CoreMinimal.h"
#include "Components/ListView.h"
#include "Showcase/ShowcaseGame/AbilitySystem/ShowcaseGameplayAbilityTypes.h"
#include "ShowcaseHotbarWidget.generated.h"

struct FAbilityUIData;
class UGameplayAbility;

/**
 * 
 */
UCLASS()
class SHOWCASE_API UShowcaseHotbarWidget : public UListView
{
	GENERATED_BODY()
	
public:

	void ConfigureAbilities(const TMap<EShowcaseAbilityInputID, TSubclassOf<UGameplayAbility>>& Abilities);
	
protected:
	
	UPROPERTY(EditAnywhere, Category = "AbilityUIData")
	TObjectPtr<UDataTable> AbilityUIDataTable;
	
private:
	
	const FAbilityUIData* GetAbilityUIData(const TSubclassOf<UGameplayAbility>& AbilityClass) const;
	
	void HotkeyGenerated(UUserWidget& UserWidget);
};
