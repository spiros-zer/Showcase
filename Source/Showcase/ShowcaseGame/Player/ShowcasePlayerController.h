// Spyridon Zervos

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/PlayerController.h"
#include "Showcase/ShowcaseGame/UserInterface/ShowcaseLayerInterface.h"
#include "ShowcasePlayerController.generated.h"

class UShowcaseGameplayWidget;
class AShowcaseCharacter;
class UCommonUserWidget;
class UShowcaseRootLayout;

/**
 * 
 */
UCLASS()
class SHOWCASE_API AShowcasePlayerController : public APlayerController, public IShowcaseLayerInterface
{
	GENERATED_BODY()
	
public:
	
	virtual void OnPossess(APawn* InPawn) override;
	
	virtual void AcknowledgePossession(APawn* InPawn) override;
	
	virtual UCommonActivatableWidget* PushWidgetToLayer(FGameplayTag LayerTag, TSoftClassPtr<UCommonActivatableWidget> ActivatableWidgetClass) const override;
	
protected:
	
	/** 
	 * The class for the gameplay widget showing player vitals etc.
	 */
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSoftClassPtr<UShowcaseGameplayWidget> GameplayWidgetClass;
	
	/** 
	 * The class for the layout of the user interface.
	 */
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSoftClassPtr<UShowcaseRootLayout> RootLayoutClass;
	
private:
	
	/** 
	 * Creates the RootLayout and adds it to the viewport.
	 */
	void CreateRootLayout();
	
	void PushGameplayWidget();
	
	UPROPERTY()
	TObjectPtr<AShowcaseCharacter> ShowcaseCharacter;
	
	UPROPERTY()
	TObjectPtr<UShowcaseGameplayWidget> GameplayWidget;
	
	UPROPERTY()
	TObjectPtr<UShowcaseRootLayout> RootLayout;
};
