// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Gs2Domain : ModuleRules
{
	public Gs2Domain(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PrivateDependencyModuleNames.AddRange(new[] {
			"Core",
			"CoreUObject",
			"Engine",
			"HTTP",
			"WebSockets",
			"Json",
			"JsonUtilities",
			"Gs2Core",
			"Gs2Account",
			"Gs2Auth",
			"Gs2Chat",
			"Gs2Datastore",
			"Gs2Dictionary",
			"Gs2Distributor",
			"Gs2Enhance",
			"Gs2Exchange",
			"Gs2Experience",
			"Gs2Formation",
			"Gs2Friend",
			"Gs2Gateway",
			"Gs2Identifier",
			"Gs2Inbox",
			"Gs2Inventory",
			"Gs2JobQueue",
			"Gs2Key",
			"Gs2Limit",
			"Gs2Lock",
			"Gs2Lottery",
			"Gs2Matchmaking",
			"Gs2MegaField",
			"Gs2Mission",
			"Gs2Money",
			"Gs2News",
			"Gs2Quest",
			"Gs2Ranking",
			"Gs2Realtime",
			"Gs2Schedule",
			"Gs2Script",
			"Gs2SerialKey",
			"Gs2Showcase",
			"Gs2Stamina",
			"Gs2Version",
		});
	}
}
