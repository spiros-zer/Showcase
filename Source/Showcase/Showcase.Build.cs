// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Showcase : ModuleRules
{
	public Showcase(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core", 
			"CoreUObject", 
			"Engine",
			"EnhancedInput",
			"InputCore", 
		});
		
		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"CommonUI",
			"GameplayAbilities",
			"GameplayTags",
			"GameplayTasks",
			"Slate", 
			"SlateCore",
			"UMG",
		});
	}
}
