// Spyridon Zervos

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AN_SendGameplayEvent.generated.h"

/**
 * 
 */
UCLASS()
class SHOWCASE_API UAN_SendGameplayEvent : public UAnimNotify
{
	GENERATED_BODY()
	
public:
	
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
	
protected:
	
	virtual FString GetNotifyName_Implementation() const override;
	
	UPROPERTY(EditAnywhere, Category = "GameplayAbility")
	FGameplayTag EventTag;
};
