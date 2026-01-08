// Spyridon Zervos


#include "ShowcaseTags.h"

namespace Ability
{
	UE_DEFINE_GAMEPLAY_TAG(BasicAttack, "Ability.BasicAttack");
	
	UE_DEFINE_GAMEPLAY_TAG(Regen, "Ability.Regen");

	namespace BladeSiphon
	{
		UE_DEFINE_GAMEPLAY_TAG(Damage, "Ability.BladeSiphon.Damage");
		
		UE_DEFINE_GAMEPLAY_TAG(Cooldown, "Ability.BladeSiphon.Cooldown");
	}
	
	namespace Combo
	{
		UE_DEFINE_GAMEPLAY_TAG(Change, "Ability.Combo.Change");
		
		UE_DEFINE_GAMEPLAY_TAG(Damage, "Ability.Combo.Damage");
		
		UE_DEFINE_GAMEPLAY_TAG(End, "Ability.Combo.End");
	}
}

namespace GameplayCue
{
	namespace Hit
	{
		UE_DEFINE_GAMEPLAY_TAG(CameraShake, "GameplayCue.Hit.CameraShake");
		
		UE_DEFINE_GAMEPLAY_TAG(Reaction, "GameplayCue.Hit.Reaction");
		
		UE_DEFINE_GAMEPLAY_TAG(Combo, "GameplayCue.Hit.Combo");
		
		UE_DEFINE_GAMEPLAY_TAG(BladeSiphon, "GameplayCue.Hit.BladeSiphon");
	}
}

namespace State
{
	UE_DEFINE_GAMEPLAY_TAG(Dead, "State.Dead");
}

namespace UI
{
	namespace Layer
	{
		UE_DEFINE_GAMEPLAY_TAG(Gameplay, "UI.Layer.Gameplay");
		
		UE_DEFINE_GAMEPLAY_TAG(Popup, "UI.Layer.Popup");
	}
}
