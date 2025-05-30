#include "SoundHolderMixerModule.h"
#include "Modules/ModuleManager.h"

#include "MetasoundFrontendRegistries.h"

#if WITH_EDITOR
#include "ISettingsModule.h"
#include "SubsystemSettings.h"
#define LOCTEXT_NAMESPACE "FameModule"
#endif

IMPLEMENT_MODULE(FSoundHolderMixer, SoundHolderMixer);

void FSoundHolderMixer::StartupModule()
{
	FMetasoundFrontendRegistryContainer::Get()->RegisterPendingNodes();
#if WITH_EDITOR
    if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
    {
        SettingsModule->RegisterSettings("Project", "Plugins", "Sound Holder Mixer Subsystem",
            LOCTEXT("RuntimeSettingsName", "Sound Holder"),
            LOCTEXT("RuntimeSettingsDescription", "Custom Subsystem settings"),
            GetMutableDefault<UBlueprintSubsystemSettings>()
        );
    }
#endif
}

void FSoundHolderMixer::ShutdownModule()
{
#if WITH_EDITOR
    if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
    {
        SettingsModule->UnregisterSettings("Project", "Game", "Subsystems");
    }
#endif
}
