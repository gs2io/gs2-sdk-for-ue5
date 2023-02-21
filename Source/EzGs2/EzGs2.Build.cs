// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class EzGs2 : ModuleRules
{
	public EzGs2(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicDependencyModuleNames.AddRange(new [] {
			"Core",
			"CoreUObject",
			"Engine",
			"HTTP",
			"WebSockets",
			"Json",
			"JsonUtilities",
		});
		
		PrivateDependencyModuleNames.AddRange(Gs2Plugin.GetGs2ModuleNames());
	}
}
