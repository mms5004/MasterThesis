#include "SoundHolderEditorModule.h"
#include "Modules/ModuleManager.h"
#include "SoundHolderEditorModeCommands.h"

#define LOCTEXT_NAMESPACE "SoundHolderModule"

void FSoundHolderEditor::StartupModule()
{
	FSoundHolderEditorModeCommands::Register();
}

void FSoundHolderEditor::ShutdownModule()
{
	FSoundHolderEditorModeCommands::Unregister();
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FSoundHolderEditor, SoundHolderEditor);