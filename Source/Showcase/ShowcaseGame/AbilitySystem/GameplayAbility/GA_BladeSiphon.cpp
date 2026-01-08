// Spyridon Zervos


#include "GA_BladeSiphon.h"

#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "Showcase/ShowcaseGame/AbilitySystem/ShowcaseTags.h"

class UAbilityTask_WaitGameplayEvent;

void UGA_BladeSiphon::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
	if (!K2_CommitAbility())
	{
		K2_EndAbility();
		
		return;
	}
	
	if (HasAuthorityOrPredictionKey(ActorInfo, &ActivationInfo))
	{
		UAbilityTask_PlayMontageAndWait* PlayComboMontageTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, NAME_None, BladeSiphonMontage);
		PlayComboMontageTask->OnBlendOut.AddUniqueDynamic(this, &ThisClass::K2_EndAbility);	
		PlayComboMontageTask->OnCancelled.AddUniqueDynamic(this, &ThisClass::K2_EndAbility);
		PlayComboMontageTask->OnCompleted.AddUniqueDynamic(this, &ThisClass::K2_EndAbility);
		PlayComboMontageTask->OnInterrupted.AddUniqueDynamic(this, &ThisClass::K2_EndAbility);
		PlayComboMontageTask->ReadyForActivation();
	}
	
	if (K2_HasAuthority())
	{
		UAbilityTask_WaitGameplayEvent* WaitTargetEventTask = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, Ability::Combo::Damage);
		WaitTargetEventTask->EventReceived.AddUniqueDynamic(this, &ThisClass::DealBladeSiphonDamage);
		WaitTargetEventTask->ReadyForActivation();
	}
}

void UGA_BladeSiphon::DealBladeSiphonDamage(FGameplayEventData Data)
{
	DealDamage(BladeSiphonDamageEffect, Data);
}
