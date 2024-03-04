// Copyright (c) 2024 Damian Nowakowski. All rights reserved.

using UnrealBuildTool;

public class ECFExample : ModuleRules
{
	public ECFExample(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        CppStandard = CppStandardVersion.Default;

        PublicDependencyModuleNames.AddRange(new string[] { 
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore",
			"UMG",
			"EnhancedCodeFlow"
		});
	}
}
