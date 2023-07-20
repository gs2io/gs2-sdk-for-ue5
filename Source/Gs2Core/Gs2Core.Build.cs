// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Gs2Core : ModuleRules
{
	public Gs2Core(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PrivateDependencyModuleNames.AddRange(new []
		{
			"Core",
			"CoreUObject",
			"Engine",
			"HTTP",
			"WebSockets",
			"Json",
			"JsonUtilities",
		});

		if (Target.Type == TargetType.Editor)
		{
			PrivateDependencyModuleNames.Add("EditorFramework");
			PrivateDependencyModuleNames.Add("UnrealEd");
		}
		
		PublicIncludePathModuleNames.AddRange(new []
		{
			"Gs2Account",
			"Gs2Auth",
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

		PrivateIncludePathModuleNames.AddRange(new []
		{
			"Gs2Auth",
			"Gs2Distributor",
		});
	}
}

public class Gs2Plugin
{
	public static string[] GetGs2DependencyModuleNames()
	{
		return new string[]
		{
			"Core",
			"CoreUObject",
			"Engine",
			"HTTP",
			"WebSockets",
			"Json",
			"JsonUtilities",
		};
	}

	public static string[] GetGs2ModuleNames()
	{
		return new string[]
		{
			"Gs2Core",
			"Gs2Account",
			"Gs2Auth",
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
			"Gs2Domain",
		};
	}
	
	public static string[] GetEzGs2ModuleNames()
	{
		return new string[]
		{
			"EzGs2",
		};
	}
	
	public static string[] GetGs2BlueprintModuleNames()
	{
		return new string[]
		{
			"BpGs2",
		};
	}
	
	public static void AddGs2Modules(ModuleRules Rules, ReadOnlyTargetRules Target)
	{
		Rules.PrivateDependencyModuleNames.AddRange(GetGs2ModuleNames());
	}
	
	public static void AddEzGs2Modules(ModuleRules Rules, ReadOnlyTargetRules Target)
	{
		Rules.PrivateDependencyModuleNames.AddRange(GetEzGs2ModuleNames());
	}
	
	public static void AddGs2BlueprintModules(ModuleRules Rules, ReadOnlyTargetRules Target)
	{
		Rules.PrivateDependencyModuleNames.AddRange(GetGs2BlueprintModuleNames());
	}
	
	public static void PrepareGs2(ModuleRules Rules, ReadOnlyTargetRules Target)
	{
		AddGs2Modules(Rules, Target);
		AddEzGs2Modules(Rules, Target);
		AddGs2BlueprintModules(Rules, Target);
	}
}