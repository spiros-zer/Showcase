// Spyridon Zervos


#include "ShowcaseHotkey.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "CommonLazyImage.h"
#include "CommonTextBlock.h"
#include "Abilities/GameplayAbility.h"
#include "Showcase/ShowcaseGame/AbilitySystem/ShowcaseAbilitySystemComponent.h"
#include "Showcase/ShowcaseGame/AbilitySystem/Util/ShowcaseAbilitySystemStatics.h"
#include "Showcase/ShowcaseGame/Character/ShowcaseCharacter.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(ShowcaseHotkey)

void UShowcaseHotkey::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);
	
	AbilityCDO = Cast<UGameplayAbility>(ListItemObject);
	check(AbilityCDO);

	// Setting ability cost.
	
	const float CostForAbility = UShowcaseAbilitySystemStatics::GetStaticCostForAbility(AbilityCDO);

	Cost->SetText(FText::AsNumber(CostForAbility));
	
	// Setting ability keybind.
	
	AShowcaseCharacter* ShowcaseOwningCharacter = GetOwningPlayerPawn<AShowcaseCharacter>();
	check(ShowcaseOwningCharacter);
	
	UAbilitySystemComponent* OwnerAsc = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(ShowcaseOwningCharacter);

	const UShowcaseAbilitySystemComponent* ShowcaseAsc = Cast<UShowcaseAbilitySystemComponent>(OwnerAsc);
	check(IsValid(ShowcaseAsc));
	
	const EShowcaseAbilityInputID AbilityInputID = *ShowcaseAsc->GetAbilities().FindKey(AbilityCDO->GetClass());
	
	const UInputAction* AbilityInputAction = *ShowcaseOwningCharacter->GetGameplayAbilityInputActions().Find(AbilityInputID);
	
	const FText KeyDisplayText = UShowcaseAbilitySystemStatics::GetPrimaryKeyDisplayText(GetOwningPlayer(), AbilityInputAction);
	
	if (KeyDisplayText.IsEmpty())
	{
		KeyDisplay->SetVisibility(ESlateVisibility::Collapsed);
	}
	
	// TODO handle unbound case.
	
	KeyDisplay->SetText(KeyDisplayText);
}

void UShowcaseHotkey::ConfigureWithWidgetData(const FAbilityUIData* AbilityUIData)
{
	Image->SetMaterialTextureParamName(ImageMaterialParamName);
	Image->SetBrushFromLazyTexture(AbilityUIData->AbilityTexture);
}

void UShowcaseHotkey::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	UAbilitySystemComponent* OwnerAsc = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetOwningPlayerPawn());
	check(IsValid(OwnerAsc));
	OwnerAsc->AbilityCommittedCallbacks.AddUObject(this, &ThisClass::HandleAbilityCommitted);
	
	FractionFormattingOptions.MaximumFractionalDigits = 1;
	
	DecimalFormattingOptions.MaximumFractionalDigits = 0;
}

void UShowcaseHotkey::NativeConstruct()
{
	Super::NativeConstruct();
	
	CooldownRemaining->SetVisibility(ESlateVisibility::Collapsed);
	
	Image->GetDynamicMaterial()->SetScalarParameterValue(PercentParamName, 1);
}

void UShowcaseHotkey::HandleAbilityCommitted(UGameplayAbility* InAbility)
{
	// Filter unrelated abilities.
	
	if (InAbility->GetClass()->GetDefaultObject() != AbilityCDO) return;
	
	float CooldownRemainingForAbility = 0;
	float CooldownDurationForAbility = 0;
	
	// Since the ability is instanced, these will return valid.
	InAbility->GetCooldownTimeRemainingAndDuration(InAbility->GetCurrentAbilitySpecHandle(), InAbility->GetCurrentActorInfo(), CooldownRemainingForAbility, CooldownDurationForAbility);
	
	StartCountdown(CooldownRemainingForAbility, CooldownDurationForAbility);
}

void UShowcaseHotkey::StartCountdown(float InCooldownRemaining, float InCooldownDuration)
{
	const UWorld* World = GetWorld();
	if (!IsValid(World)) return;
	
	CachedCooldownDuration = InCooldownDuration;
	
	CachedCooldownRemaining = InCooldownRemaining;
	
	const FNumberFormattingOptions FormattingOptionsToUse = CachedCooldownRemaining > 1 ? DecimalFormattingOptions : FractionFormattingOptions;
	
	CooldownRemaining->SetText(FText::AsNumber(InCooldownRemaining, &FormattingOptionsToUse));
	CooldownRemaining->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	
	World->GetTimerManager().SetTimer(CooldownTimerHandle, this, &ThisClass::UpdateCooldown, Rate, true);
}

void UShowcaseHotkey::UpdateCooldown()
{
	CachedCooldownRemaining -= Rate;
	
	if (CachedCooldownRemaining <= 0)
	{
		// Cooldown ended.
		
		CooldownRemaining->SetVisibility(ESlateVisibility::Collapsed);
		
		Image->GetDynamicMaterial()->SetScalarParameterValue(PercentParamName, 1);
		
		const UWorld* World = GetWorld();
		if (!IsValid(World)) return;
		
		World->GetTimerManager().ClearTimer(CooldownTimerHandle);
		
		return;
	}

	const FNumberFormattingOptions FormattingOptionsToUse = CachedCooldownRemaining > 1 ? DecimalFormattingOptions : FractionFormattingOptions;
	
	CooldownRemaining->SetText(FText::AsNumber(CachedCooldownRemaining, &FormattingOptionsToUse));
	
	Image->GetDynamicMaterial()->SetScalarParameterValue(PercentParamName, 1 - CachedCooldownRemaining / CachedCooldownDuration);
}
