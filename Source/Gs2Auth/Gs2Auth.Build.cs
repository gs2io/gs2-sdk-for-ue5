// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Gs2Auth : ModuleRules
{
	public Gs2Auth(ReadOnlyTargetRules Target) : base(Target)
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
			"Gs2Core"
		});
		
		PublicIncludePathModuleNames.AddRange(new [] {
			"Gs2Domain",
			"Core",
			"Gs2Core"
		});
	}
}
