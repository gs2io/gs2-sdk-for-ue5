// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Gs2JobQueue : ModuleRules
{
	public Gs2JobQueue(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PrivateDependencyModuleNames.AddRange(new[]
		{
			"Core",
			"CoreUObject",
			"Engine",
			"HTTP",
			"WebSockets",
			"Json",
			"JsonUtilities",
			"Gs2Core",
			"Gs2Auth",
		});
		if (Target.Platform == UnrealTargetPlatform.Win64)
		{
			PrivateDependencyModuleNames.Add("Gs2Distributor");
		}

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"Gs2Core",
		});
	}
}
