// Copyright (c) 2024 Damian Nowakowski. All rights reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class ECFExampleEditorTarget : TargetRules
{
	public ECFExampleEditorTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
#if UE_5_0_OR_LATER
        DefaultBuildSettings = BuildSettingsVersion.Latest;
        IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
#endif
		ExtraModuleNames.AddRange( new string[] { "ECFExample" } );
	}
}
