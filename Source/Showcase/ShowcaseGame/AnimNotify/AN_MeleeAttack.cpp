// Spyridon Zervos


#include "AN_MeleeAttack.h"

#include "Showcase/ShowcaseGame/Character/ShowcaseCharacter.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(AN_MeleeAttack)

void UAN_MeleeAttack::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);
	
	if (!IsValid(MeshComp)) return;
	
	AShowcaseCharacterBase* ShowcaseCharacterBase = MeshComp->GetOwner<AShowcaseCharacterBase>();
	if (!IsValid(ShowcaseCharacterBase)) return;
	if (!ShowcaseCharacterBase->IsLocallyControlled()) return;
	
	// Reset cached location validity.
	
	ShowcaseCharacterBase->Server_MeleeAttackNotifyEnd();
	
	bHasCachedLocations = false;
}

void UAN_MeleeAttack::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);
	
	if (!IsValid(MeshComp)) return;
	
	const APawn* Pawn = MeshComp->GetOwner<APawn>();
	if (!IsValid(Pawn)) return;
	if (!Pawn->IsLocallyControlled()) return;
	
	CalculateLocations(MeshComp);
}

void UAN_MeleeAttack::CalculateLocations(const USkeletalMeshComponent* MeshComp)
{
	if (!IsValid(MeshComp)) return;
	
	AShowcaseCharacterBase* ShowcaseCharacterBase = MeshComp->GetOwner<AShowcaseCharacterBase>();
	if (!IsValid(ShowcaseCharacterBase)) return;
	
	// Extract scan location.

	TArray<FVector_NetQuantize> TraceLocations;
	
	for (const FName& SocketName : TraceSocketNames)
	{
		TraceLocations.Add(MeshComp->GetSocketLocation(SocketName));
	}
	
	check(TraceLocations.Num() % 2 == 0);
	
	if (!bHasCachedLocations)
	{
		CachedTraceLocations = TraceLocations;
		
		bHasCachedLocations = true;
		
		return;
	}
	
	ShowcaseCharacterBase->Server_MeleeTraceSample(CachedTraceLocations, TraceLocations, TraceSocketNames);
	
	CachedTraceLocations = TraceLocations;
}
