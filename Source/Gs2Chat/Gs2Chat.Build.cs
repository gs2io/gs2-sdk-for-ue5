// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Gs2Chat : ModuleRules
{
	public Gs2Chat(ReadOnlyTargetRules Target) : base(Target)
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
