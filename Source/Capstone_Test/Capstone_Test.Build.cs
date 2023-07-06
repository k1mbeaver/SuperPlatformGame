// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Capstone_Test : ModuleRules
{
	public Capstone_Test(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "Json", "JsonUtilities", "UMG", "NavigationSystem", "AIModule", "GameplayTasks", "SlateCore", "Slate", "Niagara" });
	}
}
