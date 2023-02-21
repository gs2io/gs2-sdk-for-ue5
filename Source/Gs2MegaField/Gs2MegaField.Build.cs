// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Gs2MegaField : ModuleRules
{
	public Gs2MegaField(ReadOnlyTargetRules Target) : base(Target)
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
