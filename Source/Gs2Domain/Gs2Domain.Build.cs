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
			"Gs2AdReward",
			"Gs2Auth",
			"Gs2Buff",
			"Gs2Chat",
			"Gs2Datastore",
			"Gs2Deploy",
			"Gs2Dictionary",
			"Gs2Distributor",
			"Gs2Enchant",
			"Gs2Enhance",
			"Gs2Exchange",
			"Gs2Experience",
			"Gs2Formation",
			"Gs2Friend",
			"Gs2Gateway",
			"Gs2Grade",
			"Gs2Guild",
			"Gs2Identifier",
			"Gs2Idle",
			"Gs2Inbox",
			"Gs2Inventory",
			"Gs2JobQueue",
			"Gs2Key",
			"Gs2Limit",
			"Gs2LoginReward",
			"Gs2Lock",
			"Gs2Lottery",
			"Gs2Matchmaking",
			"Gs2MegaField",
			"Gs2Mission",
			"Gs2Money",
			"Gs2Money2",
			"Gs2News",
			"Gs2Quest",
			"Gs2Ranking",
			"Gs2Ranking2",
			"Gs2Realtime",
			"Gs2Schedule",
			"Gs2Script",
			"Gs2SeasonRating",
			"Gs2SerialKey",
			"Gs2Showcase",
			"Gs2SkillTree",
			"Gs2Stamina",
			"Gs2StateMachine",
			"Gs2Version",
		});
		PublicDependencyModuleNames.AddRange(new string[] {
			"Core"
		});
	}
}
