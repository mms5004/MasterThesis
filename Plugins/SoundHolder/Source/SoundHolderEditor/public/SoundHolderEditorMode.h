

#pragma once

#include "CoreMinimal.h"
#include "Tools/UEdMode.h" //Use the InteractiveTools framework
#include "SoundHolderEditorMode.generated.h"

UCLASS()
class SOUNDHOLDEREDITOR_API USoundHolderEditorMode : public UEdMode
{
	GENERATED_BODY()
	
public:	
	const static FEditorModeID EM_EditorModeEditorModeId;

	static FString ShowGizmos;
	static FString GenerateSoundInLevel;

	USoundHolderEditorMode();
	virtual ~USoundHolderEditorMode();

	/** UEdMode interface */
	virtual void Enter() override;
	virtual void ActorSelectionChangeNotify() override;
	virtual void CreateToolkit() override;
	virtual TMap<FName, TArray<TSharedPtr<FUICommandInfo>>> GetModeCommands() const override;
};