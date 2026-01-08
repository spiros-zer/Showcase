// Spyridon Zervos

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Character.h"
#include "Showcase/ShowcaseGame/AbilitySystem/ShowcaseGameplayAbilityTypes.h"
#include "ShowcaseCharacterBase.generated.h"

class UGameplayAbility;
class UShowcaseAbilitySystemComponent;
class UShowcaseAttributeSet;

UCLASS()
class SHOWCASE_API AShowcaseCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	
	AShowcaseCharacterBase();
	
	virtual void BeginPlay() override;
	
	virtual void PossessedBy(AController* NewController) override;
	
	void InitClientSide();
	
	void InitServerSide();
	
	// IAbilitySystemInterface
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
	UFUNCTION(Server, Unreliable, WithValidation)
	void Server_MeleeTraceSample(const TArray<FVector_NetQuantize>& CachedTraceLocations, const TArray<FVector_NetQuantize>& TraceLocations, const TArray<FName>& TraceSocketNames);
	
	UFUNCTION(Server, Reliable, WithValidation)
	void Server_MeleeAttackNotifyEnd();

	const TMap<EShowcaseAbilityInputID, TSubclassOf<UGameplayAbility>>& GetAbilities() const;
	
protected:
	
	virtual void OnDeath();
	
	virtual void OnRespawn();
	
	UPROPERTY(EditDefaultsOnly, Category = "AnimMontage")
	TObjectPtr<UAnimMontage> DeathMontage;

private:
	
	/** 
	 * Binds to ShowcaseAbilitySystemComponent's delegates.
	 */
	void BindToAbilitySystemComponent();
	
	/** 
	 * Called when the State::Dead tag (count) is updated.
	 */
	void DeathTagUpdated(FGameplayTag GameplayTag, int NewCount);
	
	void Respawn();
	
	void PlayDeathAnimation();
	
	void StartDeathSequence();
	
	UPROPERTY()
	TArray<TObjectPtr<AActor>> AlreadyHitActors;
	
	UPROPERTY(VisibleDefaultsOnly, Category = "AbilitySystem")
	TObjectPtr<UShowcaseAbilitySystemComponent> ShowcaseAbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UShowcaseAttributeSet> ShowcaseAttributeSet;
};
