// Spyridon Zervos

#pragma once

#include "CoreMinimal.h"
#include "CommonButtonBase.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "ShowcaseHotkey.generated.h"

class UCommonLazyImage;
class UGameplayAbility;

USTRUCT(BlueprintType)
struct FAbilityUIData : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSubclassOf<UGameplayAbility> AbilityClass;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FName AbilityName;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSoftObjectPtr<UTexture2D> AbilityTexture;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FText AbilityDescription;
};

class UCommonTextBlock;
class UImage;

/**
 * 
 */
UCLASS()
class SHOWCASE_API UShowcaseHotkey : public UCommonButtonBase, public IUserObjectListEntry
{
	GENERATED_BODY()
	
public:
	
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;
	
	void ConfigureWithWidgetData(const FAbilityUIData* AbilityUIData);

protected:

	virtual void NativeOnInitialized() override;
	
	virtual void NativeConstruct() override;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCommonLazyImage> Image;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCommonTextBlock> CooldownRemaining;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCommonTextBlock> Cost;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCommonTextBlock> KeyDisplay;

	UPROPERTY(EditDefaultsOnly, Category = "Cosmetic")
	FName ImageMaterialParamName = FName(TEXT("AbilityImage"));
	
	UPROPERTY(EditDefaultsOnly, Category = "Cosmetic")
	FName PercentParamName = FName(TEXT("Percent"));
	
	/** 
	 * The rate with which the CooldownRemaining text is updated.
	 */
	UPROPERTY(EditDefaultsOnly, Category = "Cosmetic")
	float Rate = 0.1f;
	
private:
	
	/** 
	 * Called when an ability (any) is committed.
	 * @param InAbility The instanced ability.
	 */
	void HandleAbilityCommitted(UGameplayAbility* InAbility);

	void StartCountdown(float InCooldownRemaining, float InCooldownDuration);
	
	void UpdateCooldown();
	
	float CachedCooldownDuration = 0;
	
	float CachedCooldownRemaining = 0;
	
	FFormatNamedArguments CooldownArguments;
	
	FNumberFormattingOptions DecimalFormattingOptions;
	
	FNumberFormattingOptions FractionFormattingOptions;
	
	FTimerHandle CooldownTimerHandle;
	
	UPROPERTY()
	TObjectPtr<UGameplayAbility> AbilityCDO;
};
