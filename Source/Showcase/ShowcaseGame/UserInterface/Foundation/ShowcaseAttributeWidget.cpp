// Spyridon Zervos


#include "ShowcaseAttributeWidget.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Showcase/ShowcaseGame/ShowcaseLogChannels.h"
#include "Showcase/ShowcaseGame/ShowcaseLogging.h"

void UShowcaseAttributeWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	SetAndBoundToGameplayAttribute();
}

void UShowcaseAttributeWidget::HandleAttributeChanged(const FOnAttributeChangeData& OnAttributeChangeData)
{
	BP_HandleAttributeChanged(OnAttributeChangeData.NewValue);
}

void UShowcaseAttributeWidget::HandleMaxAttributeChanged(const FOnAttributeChangeData& OnMaxAttributeChangeData)
{
	BP_HandleMaxAttributeChanged(OnMaxAttributeChangeData.NewValue);
}

void UShowcaseAttributeWidget::SetAndBoundToGameplayAttribute()
{
	check(GetOwningPlayerPawn());
	UAbilitySystemComponent* AbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetOwningPlayerPawn());
	if (!IsValid(AbilitySystemComponent))
	{
		SHOWCASE_ERROR(LogShowcaseUI, TEXT("Invalid ability system component."));
		
		SetVisibility(ESlateVisibility::Collapsed);
		
		return;
	}
	
	bool bFound = false;
	
	const float Value = AbilitySystemComponent->GetGameplayAttributeValue(Attribute, bFound);
	
	if (!bFound)
	{
		SHOWCASE_ERROR(LogShowcaseUI, TEXT("Attribute not found."));
		
		SetVisibility(ESlateVisibility::Collapsed);
		
		return;
	}
	
	BP_HandleAttributeChanged(Value);
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attribute).AddUObject(this, &ThisClass::HandleAttributeChanged);
	
	const float MaxValue = AbilitySystemComponent->GetGameplayAttributeValue(MaxAttribute, bFound);
	
	if (!bFound)
	{
		SHOWCASE_ERROR(LogShowcaseUI, TEXT("Max attribute not found."));
		
		SetVisibility(ESlateVisibility::Collapsed);
		
		return;
	}
	
	BP_HandleMaxAttributeChanged(MaxValue);
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(MaxAttribute).AddUObject(this, &ThisClass::HandleMaxAttributeChanged);
}
