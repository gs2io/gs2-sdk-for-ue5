// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Gs2Showcase : ModuleRules
{
	public Gs2Showcase(ReadOnlyTargetRules Target) : base(Target)
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
			"Gs2",
			"Gs2Auth",
			"Gs2Distributor",
		});
	}
}
