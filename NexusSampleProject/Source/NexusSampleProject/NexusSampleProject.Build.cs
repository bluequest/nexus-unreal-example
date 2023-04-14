// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class NexusSampleProject : ModuleRules
{
	public NexusSampleProject(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] 
		{ 
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore", 
			"HeadMountedDisplay", 
			"NavigationSystem", 
			"AIModule", 
			"Niagara", 
			"EnhancedInput", 
			"ApplicationCore" 
		});
    }
}
