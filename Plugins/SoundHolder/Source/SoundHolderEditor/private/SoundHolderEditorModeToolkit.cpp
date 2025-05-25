

#include "SoundHolderEditorModeToolkit.h"

#include "Modules/ModuleManager.h"
#include "PropertyEditorModule.h"
#include "IDetailsView.h"
#include "EditorModeManager.h"

#define LOCTEXT_NAMESPACE "SoundHolderEditorModeToolkit"

FSoundHolderEditorModeToolkit::FSoundHolderEditorModeToolkit()
{
}

void FSoundHolderEditorModeToolkit::Init(const TSharedPtr<IToolkitHost>& InitToolkitHost, TWeakObjectPtr<UEdMode> InOwningMode)
{
	FModeToolkit::Init(InitToolkitHost, InOwningMode);
}

void FSoundHolderEditorModeToolkit::GetToolPaletteNames(TArray<FName>& PaletteNames) const
{
	PaletteNames.Add(NAME_Default);
}


FName FSoundHolderEditorModeToolkit::GetToolkitFName() const
{
	return FName("SoundHolderEditorMode");
}

FText FSoundHolderEditorModeToolkit::GetBaseToolkitName() const
{
	return LOCTEXT("DisplayName", "SoundHolderEditorMode Toolkit");
}

#undef LOCTEXT_NAMESPACE