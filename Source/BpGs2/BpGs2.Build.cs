using UnrealBuildTool;

public class BpGs2 : ModuleRules
{
    public BpGs2(ReadOnlyTargetRules Target) : base(Target)
    {
	    PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
				"Core",
				"CoreUObject",
				"Engine",
				"HTTP",
				"WebSockets",
				"Json",
				"JsonUtilities",
            }
        );
        PrivateDependencyModuleNames.AddRange(Gs2Plugin.GetGs2ModuleNames());
		PrivateDependencyModuleNames.AddRange(Gs2Plugin.GetEzGs2ModuleNames());
    }
}