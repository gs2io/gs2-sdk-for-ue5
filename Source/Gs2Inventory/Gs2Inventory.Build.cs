// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Gs2Inventory : ModuleRules
{
	public Gs2Inventory(ReadOnlyTargetRules Target) : base(Target)
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
			"Gs2JobQueue"
		});
	}
}
