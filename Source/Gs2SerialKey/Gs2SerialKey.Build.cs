// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Gs2SerialKey : ModuleRules
{
	public Gs2SerialKey(ReadOnlyTargetRules Target) : base(Target)
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
		});
	}
}
