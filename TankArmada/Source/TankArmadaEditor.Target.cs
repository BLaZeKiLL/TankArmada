// Property of D4L4L

using UnrealBuildTool;
using System.Collections.Generic;

public class TankArmadaEditorTarget : TargetRules
{
	public TankArmadaEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;

		ExtraModuleNames.AddRange( new string[] { "TankArmada" } );
	}
}
