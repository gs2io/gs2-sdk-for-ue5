// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Gs2Distributor : ModuleRules
{
	public Gs2Distributor(ReadOnlyTargetRules Target) : base(Target)
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
				"Gs2JobQueue"
			}
		);
	}
}
