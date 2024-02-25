// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Gs2SeasonRating : ModuleRules
{
	public Gs2SeasonRating(ReadOnlyTargetRules Target) : base(Target)
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
			"Gs2Experience",
		});
		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"Gs2Core"
		});
	}
}
