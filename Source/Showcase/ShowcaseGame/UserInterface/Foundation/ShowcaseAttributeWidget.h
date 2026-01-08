// Spyridon Zervos

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "GameplayEffectTypes.h"
#include "Blueprint/UserWidget.h"
#include "ShowcaseAttributeWidget.generated.h"

class UAbilitySystemComponent;

/**
 * 
 */
UCLASS()
class SHOWCASE_API UShowcaseAttributeWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	
	virtual void NativeOnInitialized() override;

	/** 
	 * Called when Attribute changes.
	 */
	UFUNCTION(BlueprintImplementableEvent)
	void BP_HandleAttributeChanged(float AttributeValue);
	
	/** 
	 * Called when MaxAttribute changes.
	 */
	UFUNCTION(BlueprintImplementableEvent)
	void BP_HandleMaxAttributeChanged(float MaxAttributeValue);
	
	/** 
	 * Attribute to bind to.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attribute")
	FGameplayAttribute Attribute;
	
	/** 
	 * Max attribute to bind to.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attribute")
	FGameplayAttribute MaxAttribute;
	
private:
	
	void HandleAttributeChanged(const FOnAttributeChangeData& OnAttributeChangeData);
	
	void HandleMaxAttributeChanged(const FOnAttributeChangeData& OnMaxAttributeChangeData);
	
	void SetAndBoundToGameplayAttribute();
};
