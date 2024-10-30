// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class VRFINALTESTING : ModuleRules
{
	public VRFINALTESTING(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
    "Core",
    "CoreUObject",
    "Engine",
    "InputCore",
    "EnhancedInput",
    "BlueprintAssist",
    "HTTP",
    "Json",
    "HeadMountedDisplay", // For VR and Motion Controller Components         
        });
	}
}
