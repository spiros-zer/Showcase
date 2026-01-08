// Spyridon Zervos

#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"

namespace Ability
{
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(BasicAttack);
	
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Regen);

	namespace BladeSiphon
	{
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Damage);
		
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Cooldown);
	}
	
	namespace Combo
	{
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Change);
		
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Damage);
		
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(End);
	}
}

namespace GameplayCue
{
	namespace Hit
	{
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(CameraShake);
		
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Reaction);
		
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Combo);
		
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(BladeSiphon);
	}
}

namespace State
{
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Dead);
}

namespace UI
{
	namespace Layer
	{
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Gameplay);
		
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Popup);
	}
}
