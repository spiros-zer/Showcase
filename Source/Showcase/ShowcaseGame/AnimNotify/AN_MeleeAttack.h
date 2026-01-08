// Spyridon Zervos

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "AN_MeleeAttack.generated.h"

/**
 * 
 */
UCLASS()
class SHOWCASE_API UAN_MeleeAttack : public UAnimNotifyState
{
	GENERATED_BODY()
	
public:
	
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
	
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference) override;

protected:
	
	/** 
	 * Sockets for hit tracing.
	 */
	UPROPERTY(EditAnywhere, Category = "HitTrace")
	TArray<FName> TraceSocketNames;
	
private:
	
	void CalculateLocations(const USkeletalMeshComponent* MeshComp);
	
	/** 
	 * Whether CachedTraceLocations has valid data for this iteration.
	 */
	bool bHasCachedLocations = false;
	
	/** 
	 * Locations of previous sockets.
	 */
	TArray<FVector_NetQuantize> CachedTraceLocations;
};
