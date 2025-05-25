

#include "SoundHolderEditorModeCommands.h"
#include "EditorStyleSet.h"

#define LOCTEXT_NAMESPACE "SoundHolderEditorModeCommands"

FSoundHolderEditorModeCommands::FSoundHolderEditorModeCommands()
	: TCommands<FSoundHolderEditorModeCommands>("SoundHolderEditorMode",
		NSLOCTEXT("SoundHolderEditorMode", "SoundHolderEditorModeCommands", "SoundHolder Editor Mode"),
		NAME_None,
		FEditorStyle::GetStyleSetName())
{
}

void FSoundHolderEditorModeCommands::RegisterCommands()
{
	TArray <TSharedPtr<FUICommandInfo>>& ToolCommands = Commands.FindOrAdd(NAME_Default);

	UI_COMMAND(ShowGizmos, "Visualize sound sources", "Show audio sources placed in level", EUserInterfaceActionType::ToggleButton, FInputChord());
	ToolCommands.Add(ShowGizmos);

	UI_COMMAND(GenerateSoundInLevel, "Place sound sources", "Based on data assets, place audio sources", EUserInterfaceActionType::Button, FInputChord());
	ToolCommands.Add(GenerateSoundInLevel);
}

TMap<FName, TArray<TSharedPtr<FUICommandInfo>>> FSoundHolderEditorModeCommands::GetCommands()
{
	return FSoundHolderEditorModeCommands::Get().Commands;
}

#undef LOCTEXT_NAMESPACE