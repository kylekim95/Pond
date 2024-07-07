// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Pond : ModuleRules
{
	public Pond(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "UMG", "HTTP", "Json", "JsonUtilities" });
		PrivateDependencyModuleNames.AddRange(new string[] { "Water" });

		if(Target.bBuildEditor){
			PrivateDependencyModuleNames.Add("EditorSubsystem");
		}
	}
}
