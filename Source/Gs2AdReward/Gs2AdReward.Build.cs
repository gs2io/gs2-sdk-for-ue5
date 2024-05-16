// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Gs2AdReward : ModuleRules
{
	public Gs2AdReward(ReadOnlyTargetRules Target) : base(Target)
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
			"Gs2Distributor",
			"Gs2JobQueue",
		});
		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"Gs2Core",
		});
	}
}
