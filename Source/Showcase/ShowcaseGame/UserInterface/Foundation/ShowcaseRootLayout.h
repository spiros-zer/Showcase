// Spyridon Zervos

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "GameplayTagContainer.h"

#include "ShowcaseRootLayout.generated.h"

class UCommonActivatableWidget;
class UCommonActivatableWidgetStack;

/**
 * 
 */
UCLASS()
class SHOWCASE_API UShowcaseRootLayout : public UCommonUserWidget
{
	GENERATED_BODY()
	
public:
	
	UCommonActivatableWidget* PushWidgetToLayer(FGameplayTag LayerTag, TSoftClassPtr<UCommonActivatableWidget> ActivatableWidgetClass);
	
protected:
	
	UFUNCTION(BlueprintCallable)
	void RegisterLayer(FGameplayTag LayerTag, UCommonActivatableWidgetStack* Layer);
	
private:
	
	/** 
	 * Map holding the UI layers and their owning tags.
	 */
	UPROPERTY()
	TMap<FGameplayTag, TObjectPtr<UCommonActivatableWidgetStack>> LayerMap;
};
