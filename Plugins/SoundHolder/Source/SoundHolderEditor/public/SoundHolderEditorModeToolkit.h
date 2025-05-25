

#pragma once

#include "CoreMinimal.h"
#include "Toolkits/BaseToolkit.h"
#include "SoundHolderEditorMode.h"

/*	FModeToolkit creates a basic UI panel for InteractiveTools to
	be initialized, add a DetailsView to show properties of the active tool.
*/
class SOUNDHOLDEREDITOR_API FSoundHolderEditorModeToolkit : public FModeToolkit
{
public:
	FSoundHolderEditorModeToolkit();

	/** FModeToolkit interface */
	virtual void Init(const TSharedPtr<IToolkitHost>& InitToolkitHost, TWeakObjectPtr<UEdMode> InOwningMode) override;
	virtual void GetToolPaletteNames(TArray<FName>& PaletteNames) const override;

	/** IToolkit interface */
	virtual FName GetToolkitFName() const override;
	virtual FText GetBaseToolkitName() const override;	
};
