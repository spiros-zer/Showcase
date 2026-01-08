// Spyridon Zervos


#include "ShowcasePlayerController.h"

#include "Blueprint/UserWidget.h"
#include "Showcase/ShowcaseGame/ShowcaseLogChannels.h"
#include "Showcase/ShowcaseGame/ShowcaseLogging.h"
#include "Showcase/ShowcaseGame/AbilitySystem/ShowcaseTags.h"
#include "Showcase/ShowcaseGame/Character/ShowcaseCharacter.h"
#include "Showcase/ShowcaseGame/UserInterface/Base/ShowcaseGameplayWidget.h"
#include "Showcase/ShowcaseGame/UserInterface/Foundation/ShowcaseRootLayout.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(ShowcasePlayerController)

void AShowcasePlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	
	ShowcaseCharacter = Cast<AShowcaseCharacter>(InPawn);
	if (!IsValid(ShowcaseCharacter))
	{
		SHOWCASE_ERROR(LogShowcase, TEXT("Invalid Player Character."));
		
		return;
	}
	ShowcaseCharacter->InitServerSide();
}

void AShowcasePlayerController::AcknowledgePossession(APawn* InPawn)
{
	Super::AcknowledgePossession(InPawn);
	
	ShowcaseCharacter = Cast<AShowcaseCharacter>(InPawn);
	if (!IsValid(ShowcaseCharacter))
	{
		SHOWCASE_ERROR(LogShowcase, TEXT("Invalid Player Character."));
		
		return;
	}
	ShowcaseCharacter->InitClientSide();
	
	CreateRootLayout();
	
	PushGameplayWidget();
}

UCommonActivatableWidget* AShowcasePlayerController::PushWidgetToLayer(const FGameplayTag LayerTag, const TSoftClassPtr<UCommonActivatableWidget> ActivatableWidgetClass) const
{
	check(RootLayout);
	
	return RootLayout->PushWidgetToLayer(LayerTag, ActivatableWidgetClass);
}

void AShowcasePlayerController::CreateRootLayout()
{
	RootLayout = CreateWidget<UShowcaseRootLayout>(this, RootLayoutClass.LoadSynchronous());
	check(RootLayout);
	RootLayout->AddToViewport();
	
	SHOWCASE_VERBOSE(LogShowcaseUI, TEXT("Root Layout created and added to viewport."));
}

void AShowcasePlayerController::PushGameplayWidget()
{
	GameplayWidget = Cast<UShowcaseGameplayWidget>(PushWidgetToLayer(UI::Layer::Gameplay, GameplayWidgetClass));
	check(GameplayWidget);
	GameplayWidget->ConfigureAbilities(ShowcaseCharacter->GetAbilities());
}
