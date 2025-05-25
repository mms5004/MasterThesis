

#include "SoundHolderEditorMode.h"
#include "SoundHolderEditorModeToolkit.h"
#include "EdModeInteractiveToolsContext.h"
#include "InteractiveToolManager.h"
#include "SoundHolderEditorModeCommands.h"

//////////////////////////////////////////////////////////////////////////
// 1) To add tools, include the header bellow
//////////////////////////////////////////////////////////////////////////
#include "Tools/ShowGizmo.h"
#include "Tools/GenerateSoundInLevel.h"

//////////////////////////////////////////////////////////////////////////
// 2) Then you need to add the variable in the .h of this class to define its value here
//////////////////////////////////////////////////////////////////////////

#define LOCTEXT_NAMESPACE "SoundHolderEditorMode"

const FEditorModeID USoundHolderEditorMode::EM_EditorModeEditorModeId = TEXT("EM_EditorModeEditorMode");

FString USoundHolderEditorMode::ShowGizmos = TEXT("EditorMode_ShowGizmos");
FString USoundHolderEditorMode::GenerateSoundInLevel = TEXT("EditorMode_GenerateSoundInLevel");


USoundHolderEditorMode::USoundHolderEditorMode()
{
	FModuleManager::Get().LoadModule("EditorStyle");

	// appearance and icon in the editing mode ribbon can be customized here
	Info = FEditorModeInfo(USoundHolderEditorMode::EM_EditorModeEditorModeId,
		LOCTEXT("SoundHolder", "SoundAutomationMode"),
		FSlateIcon(),
		true);
}

USoundHolderEditorMode::~USoundHolderEditorMode()
{
}

void USoundHolderEditorMode::ActorSelectionChangeNotify()
{
}

void USoundHolderEditorMode::Enter()
{
	UEdMode::Enter();

	//////////////////////////////////////////////////////////////////////////
	// 3) register the ToolBuilders for your Tools here.
	// The string name passed to the ToolManager is used to select/activate the ToolBuilder later.
	// Obviously the variables in "SoundHolderEditorModeCommands.h" have to be created to be use with "SampleToolCommands"
	//////////////////////////////////////////////////////////////////////////
 
	const FSoundHolderEditorModeCommands& SampleToolCommands = FSoundHolderEditorModeCommands::Get();

	RegisterTool(SampleToolCommands.ShowGizmos, ShowGizmos, NewObject<UShowGizmoBuilder>(this));
	RegisterTool(SampleToolCommands.GenerateSoundInLevel, GenerateSoundInLevel, NewObject<UGenerateSoundInLevelBuilder>(this));

	// active tool type is not relevant here, we just set to default
	GetToolManager()->SelectActiveToolType(EToolSide::Left, ShowGizmos);
}

void USoundHolderEditorMode::CreateToolkit()
{
	Toolkit = MakeShareable(new FSoundHolderEditorModeToolkit);
}

TMap<FName, TArray<TSharedPtr<FUICommandInfo>>> USoundHolderEditorMode::GetModeCommands() const
{
	return FSoundHolderEditorModeCommands::Get().GetCommands();
}

#undef LOCTEXT_NAMESPACE