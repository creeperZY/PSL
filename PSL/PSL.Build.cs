// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class PSL : ModuleRules
{
	public PSL(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "Niagara", "HeadMountedDisplay", "EnhancedInput", "UMG", "GameplayAbilities" });
		PrivateDependencyModuleNames.AddRange(new string[] { "GameplayTags", "GameplayTasks" });
	}
}
