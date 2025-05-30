#include "SoundHolderMixerModule.h"
#include "Modules/ModuleManager.h"

#include "MetasoundFrontendRegistries.h"

IMPLEMENT_MODULE(FSoundHolderMixer, SoundHolderMixer);

void FSoundHolderMixer::StartupModule()
{
	FMetasoundFrontendRegistryContainer::Get()->RegisterPendingNodes();
}

void FSoundHolderMixer::ShutdownModule()
{
}
