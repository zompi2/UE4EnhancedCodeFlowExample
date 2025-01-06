// Copyright (c) 2024 Damian Nowakowski. All rights reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class ECFExampleTarget : TargetRules
{
	public ECFExampleTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.Latest;
		DefaultWarningLevel = WarningLevel.Error;
	    ShadowVariableWarningLevel = WarningLevel.Error;
		// IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
        ExtraModuleNames.AddRange( new string[] { "ECFExample" } );
	}
}
