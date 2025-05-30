using UnrealBuildTool;

public class SoundHolderEditor: ModuleRules
{
    public SoundHolderEditor(ReadOnlyTargetRules Target) : base(Target)
    {

	    PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
		    new string[]
		    {
			    "Core",
		    }
	    );

        PrivateDependencyModuleNames.AddRange(
            new string[] 
        {
            "CoreUObject",
            "Engine",

            "Slate",
            "SlateCore",
            "InputCore",
            "EditorFramework",
            "EditorStyle",
            "UnrealEd",
            "LevelEditor",
            "InteractiveToolsFramework",
            "EditorInteractiveToolsFramework",
            "UMGEditor",
            "UMG",
            "Blutility",
            "MetasoundEngine"
        }
        );
    }
}
