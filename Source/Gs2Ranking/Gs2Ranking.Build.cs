// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Gs2Ranking : ModuleRules
{
	public Gs2Ranking(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PrivateDependencyModuleNames.AddRange(new [] {
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
		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"Gs2Core"
		});
	}
}
