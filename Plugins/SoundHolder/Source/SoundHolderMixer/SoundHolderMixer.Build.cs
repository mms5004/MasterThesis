using UnrealBuildTool;

public class SoundHolderMixer: ModuleRules
{
    public SoundHolderMixer(ReadOnlyTargetRules Target) : base(Target)
    {
        PrivateDependencyModuleNames.AddRange(new string[] {"Core", "CoreUObject", "Engine", "DeveloperSettings", "StructUtils" });
    }
}
