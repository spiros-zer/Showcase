// Spyridon Zervos

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/Object.h"
#include "ShowcaseLayerInterface.generated.h"

class UCommonActivatableWidget;

/**
 * 
 */
UINTERFACE()
class SHOWCASE_API UShowcaseLayerInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class IShowcaseLayerInterface
{
	GENERATED_IINTERFACE_BODY()

public:
	
	virtual UCommonActivatableWidget* PushWidgetToLayer(FGameplayTag LayerTag, TSoftClassPtr<UCommonActivatableWidget> ActivatableWidgetClass) const = 0;
};
