// Copyright (c) 2024 Damian Nowakowski. All rights reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class ECFExampleTarget : TargetRules
{
	public ECFExampleTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
#if UE_5_0_OR_LATER
        DefaultBuildSettings = BuildSettingsVersion.Latest;
		IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
#endif
		ExtraModuleNames.AddRange( new string[] { "ECFExample" } );
	}
}
