// Spyridon Zervos

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "ShowcaseAnimeInstance.generated.h"

class AShowcaseCharacter;
class UCharacterMovementComponent;

/**
 * 
 */
UCLASS()
class SHOWCASE_API UShowcaseAnimeInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	
	virtual void NativeInitializeAnimation() override;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	
	UFUNCTION(BlueprintCallable, meta = (BlueprintThreadSafe))
	FORCEINLINE bool GetIsGrounded() const;
	
	UFUNCTION(BlueprintGetter, meta = (BlueprintThreadSafe))
	FORCEINLINE bool GetIsJumping() const;
	
	UFUNCTION(BlueprintCallable, meta = (BlueprintThreadSafe))
	FORCEINLINE float GetLookPitchOffset() const;
	
	UFUNCTION(BlueprintCallable, meta = (BlueprintThreadSafe))
	FORCEINLINE float GetLookYawOffset() const;
	
	UFUNCTION(BlueprintGetter, meta = (BlueprintThreadSafe))
	FORCEINLINE float GetSpeed() const;
	
	UFUNCTION(BlueprintCallable, meta = (BlueprintThreadSafe))
	FORCEINLINE bool IsMoving() const;
	
	UFUNCTION(BlueprintCallable, meta = (BlueprintThreadSafe))
	FORCEINLINE bool IsNotMoving() const;
	
private:
	
	UPROPERTY()
	TObjectPtr<AShowcaseCharacter> OwnerCharacter;
	
	UPROPERTY()
	TObjectPtr<UCharacterMovementComponent> OwnerMovementComponent;
	
	UPROPERTY(BlueprintGetter = GetIsJumping)
	bool bIsJumping = false;
	
	UPROPERTY(BlueprintGetter = GetSpeed)
	float Speed = 0;
	
	FRotator LookRotOffset;
};
