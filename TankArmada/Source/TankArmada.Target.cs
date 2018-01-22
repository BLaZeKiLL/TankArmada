// Property of D4L4L

using UnrealBuildTool;
using System.Collections.Generic;

public class TankArmadaTarget : TargetRules
{
	public TankArmadaTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;

		ExtraModuleNames.AddRange( new string[] { "TankArmada" } );
	}
}
