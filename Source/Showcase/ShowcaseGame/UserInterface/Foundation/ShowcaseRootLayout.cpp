// Spyridon Zervos


#include "ShowcaseRootLayout.h"

#include "CommonActivatableWidget.h"
#include "GameplayTagContainer.h"
#include "Showcase/ShowcaseGame/ShowcaseLogChannels.h"
#include "Showcase/ShowcaseGame/ShowcaseLogging.h"
#include "Widgets/CommonActivatableWidgetContainer.h"

UCommonActivatableWidget* UShowcaseRootLayout::PushWidgetToLayer(const FGameplayTag LayerTag, const TSoftClassPtr<UCommonActivatableWidget> ActivatableWidgetClass)
{
	if (ActivatableWidgetClass.IsNull())
	{
		SHOWCASE_ERROR(LogShowcaseUI, TEXT("Invalid widget class."));
		
		return nullptr;
	}
	
	UClass* LoadedClass = ActivatableWidgetClass.LoadSynchronous();
	if (!IsValid(LoadedClass))
	{
		SHOWCASE_ERROR(LogShowcaseUI, TEXT("Widget class failed to load: %s"), *ActivatableWidgetClass.ToSoftObjectPath().ToString());
		
		return nullptr;
	}
	
	UCommonActivatableWidgetStack* Layer = *LayerMap.Find(LayerTag);
	check(Layer);
	
	UCommonActivatableWidget* AddedWidget = Layer->AddWidget(LoadedClass);
	check(AddedWidget);
	
	return AddedWidget;
}

void UShowcaseRootLayout::RegisterLayer(const FGameplayTag LayerTag, UCommonActivatableWidgetStack* Layer)
{
	if (!IsValid(Layer))
	{
		SHOWCASE_ERROR(LogShowcaseUI, TEXT("Invalid layer."));
		
		return;
	}
	
	LayerMap.Add(LayerTag, Layer);
}
