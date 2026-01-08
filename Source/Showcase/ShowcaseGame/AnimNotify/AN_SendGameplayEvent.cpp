// Spyridon Zervos


#include "AN_SendGameplayEvent.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "GameplayTagsManager.h"
#include "Showcase/ShowcaseGame/ShowcaseLogChannels.h"
#include "Showcase/ShowcaseGame/ShowcaseLogging.h"

void UAN_SendGameplayEvent::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
	
	if (!IsValid(MeshComp))
	{
		SHOWCASE_ERROR(LogShowcaseAnimation, TEXT("Invalid MeshComp."));
		
		return;
	}
	
	AActor* Owner = MeshComp->GetOwner();
	
	if (!IsValid(Owner))
	{
		SHOWCASE_ERROR(LogShowcaseAnimation, TEXT("Invalid Owner."));
		
		return;
	}
	
	const UAbilitySystemComponent* Asc = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Owner);
	if (!IsValid(Asc)) return;
	
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(Owner, EventTag, FGameplayEventData());
}

FString UAN_SendGameplayEvent::GetNotifyName_Implementation() const
{
	if (!EventTag.IsValid())
	{
		return "None";
	}
	
	// Split Tag into parts and return the last part since that contains the info we need.
	
	TArray<FName> TagNames;
	
	UGameplayTagsManager::Get().SplitGameplayTagFName(EventTag, TagNames);
	
	return TagNames.Last().ToString();
}
