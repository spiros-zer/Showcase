// Spyridon Zervos

#pragma once

#include "CoreMinimal.h"
#include "ShowcaseCharacterBase.h"
#include "Showcase/ShowcaseGame/AbilitySystem/ShowcaseGameplayAbilityTypes.h"
#include "ShowcaseCharacter.generated.h"

struct FInputActionValue;
class UCameraComponent;
class UInputAction;
class UInputMappingContext;
class USpringArmComponent;

UCLASS()
class SHOWCASE_API AShowcaseCharacter : public AShowcaseCharacterBase
{
	GENERATED_BODY()

public:
	
	AShowcaseCharacter();
	
	virtual void PawnClientRestart() override;
	
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	
	const TMap<EShowcaseAbilityInputID, TObjectPtr<UInputAction>>& GetGameplayAbilityInputActions() const;
	
protected:
	
	virtual void OnDeath() override;
	
	virtual void OnRespawn() override;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TMap<EShowcaseAbilityInputID, TObjectPtr<UInputAction>> GameplayAbilityInputActions;
	
	UPROPERTY(VisibleDefaultsOnly, Category = "View")
	TObjectPtr<UCameraComponent> ViewCamera;
	
	UPROPERTY(VisibleDefaultsOnly, Category = "View")
	TObjectPtr<USpringArmComponent> CameraBoom;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> InputActionDrawWeapon;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> InputActionJump;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> InputActionLook;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> InputActionMove;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputMappingContext> GameplayInputMappingContext;
	
private:
	
	void HandleAbilityInput(const FInputActionValue& InputActionValue, EShowcaseAbilityInputID InputID);
	
	void HandleLookInput(const FInputActionValue& InputActionValue);
	
	void HandleMoveInput(const FInputActionValue& InputActionValue);
};
