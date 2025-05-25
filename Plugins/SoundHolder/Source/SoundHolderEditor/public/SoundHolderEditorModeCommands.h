

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"

//contains info of all commands in this custom editor mode.
class SOUNDHOLDEREDITOR_API FSoundHolderEditorModeCommands : public TCommands<FSoundHolderEditorModeCommands>
{
public:
	FSoundHolderEditorModeCommands();

	virtual void RegisterCommands() override;
	static TMap<FName, TArray<TSharedPtr<FUICommandInfo>>> GetCommands();

	TSharedPtr<FUICommandInfo> ShowGizmos;
	TSharedPtr<FUICommandInfo> GenerateSoundInLevel;

protected:
	TMap<FName, TArray<TSharedPtr<FUICommandInfo>>> Commands;	
};