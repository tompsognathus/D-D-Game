// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class CharSheet : ModuleRules
{
	public CharSheet(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "UMG", "HeadMountedDisplay", "NavigationSystem", "AIModule", "Niagara", "EnhancedInput", "SlateCore" });
        PrivateDependencyModuleNames.AddRange(new string[] { "DlgSystem" });

    }
}
