// Copyright Epic Games, Inc. All Rights Reserved.

#include "GenerateSoundInLevel.h"
#include "InteractiveToolManager.h"
#include "ToolBuilderUtil.h"
#include "BaseBehaviors/ClickDragBehavior.h"

// for raycast into World
#include "CollisionQueryParams.h"
#include "Engine/World.h"

#include "SceneManagement.h"

//Editor Utility Widget
#include "Editor.h"
#include "Editor/Blutility/Public/EditorUtilitySubsystem.h"
#include "Editor/Blutility/Classes/EditorUtilityWidget.h"
#include "Editor/Blutility/Classes/EditorUtilityWidgetBlueprint.h"
#include "Framework/Application/SlateApplication.h"


// localization namespace
#define LOCTEXT_NAMESPACE "GenerateSoundInLevel"

/*
 * ToolBuilder
 */

UInteractiveTool* UGenerateSoundInLevelBuilder::BuildTool(const FToolBuilderState & SceneState) const
{
	UGenerateSoundInLevel* NewTool = NewObject<UGenerateSoundInLevel>(SceneState.ToolManager);
	NewTool->SetWorld(SceneState.World);
	return NewTool;
}


UGenerateSoundInLevelProperties::UGenerateSoundInLevelProperties()
{
	// initialize the points and distance to reasonable values
	SelectionCoordonate = FVector(0,0,0);
}

void UGenerateSoundInLevel::SetupWidgetBlueprint()
{
	if (WidgetInstance)	{return;}

	// initialize widget utility  //UE_LOG(LogTemp, Warning, TEXT("Setup?"))
	FSoftObjectPath WidgetPath;	WidgetPath.SetPath("/SoundHolder/Tools/EUW_SoundGeneration.EUW_SoundGeneration_C");

	//UEditorUtilityWidgetBlueprint* WidgetBP = Cast<UEditorUtilityWidgetBlueprint>(StaticLoadObject(UEditorUtilityWidgetBlueprint::StaticClass(), nullptr, *WidgetPath.ToString())); //Removing the _C to load blueprint
	UClass* WidgetClass = Cast<UClass>(StaticLoadObject(UClass::StaticClass(), nullptr, *WidgetPath.ToString()));
	if (WidgetClass && GEditor)
	{
		//if (UEditorUtilitySubsystem* EditorUtilitySubsystem = GEditor->GetEditorSubsystem<UEditorUtilitySubsystem>())
		//{
		//	EditorUtilitySubsystem->SpawnAndRegisterTab(WidgetBP);
		//}
		if (UWorld* World = GEditor->GetEditorWorldContext().World())
		{
			WidgetInstance = CreateWidget<UEUW_SoundGeneration>(World, WidgetClass);
			if (WidgetInstance)
			{
				TSharedRef<SWindow> WidgetWindow = SNew(SWindow)
					.Title(FText::FromString("Sound Tool"))
					.ClientSize(FVector2D(500, 400))
					.SupportsMinimize(true)
					.SupportsMaximize(false);

				TSharedRef<SWidget> SlateWidget = WidgetInstance->TakeWidget();

				WidgetWindow->SetContent(SlateWidget);

				FSlateApplication::Get().AddWindow(WidgetWindow);

				if (IsValid(ComponentHit))
				{
					WidgetInstance->SetupParameters(Properties->Suffix, ComponentHit);

				}
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("widget error ! "))
			}
		}
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Utility renamed/moved or deleted ! "))
	}
}

void UGenerateSoundInLevel::SetWorld(UWorld* World)
{
	check(World);
	this->TargetWorld = World;
}


void UGenerateSoundInLevel::Setup()
{
	UInteractiveTool::Setup();

	// Add default mouse input behavior
	UClickDragInputBehavior* MouseBehavior = NewObject<UClickDragInputBehavior>();
	// We will use the shift key to indicate that we should move the second point. 
	// This call tells the Behavior to call our OnUpdateModifierState() function on mouse-down and mouse-move
	MouseBehavior->Modifiers.RegisterModifier(MoveSecondPointModifierID, FInputDeviceState::IsShiftKeyDown);
	MouseBehavior->Initialize(this);
	AddInputBehavior(MouseBehavior);

	// Create the property set and register it with the Tool
	Properties = NewObject<UGenerateSoundInLevelProperties>(this, "Sound Generation");
	AddToolPropertySource(Properties);
	
	bSecondPointModifierDown = false;
	bMoveSecondPoint = false;

	SetupWidgetBlueprint();
}


void UGenerateSoundInLevel::OnUpdateModifierState(int ModifierID, bool bIsOn)
{
	// keep track of the "second point" modifier (shift key for mouse input)
	if (ModifierID == MoveSecondPointModifierID)
	{
		bSecondPointModifierDown = bIsOn;
	}
}


FInputRayHit UGenerateSoundInLevel::CanBeginClickDragSequence(const FInputDeviceRay& PressPos)
{
	// we only start drag if press-down is on top of something we can raycast
	FVector Temp;
	FInputRayHit Result = FindRayHit(PressPos.WorldRay, Temp);
	return Result;
}


void UGenerateSoundInLevel::OnClickPress(const FInputDeviceRay& PressPos)
{
	// determine whether we are moving first or second point for the drag sequence
	bMoveSecondPoint = bSecondPointModifierDown;
	UpdatePosition(PressPos.WorldRay);
}


void UGenerateSoundInLevel::OnClickDrag(const FInputDeviceRay& DragPos)
{
	UpdatePosition(DragPos.WorldRay);
}


FInputRayHit UGenerateSoundInLevel::FindRayHit(const FRay& WorldRay, FVector& HitPos)
{
	// trace a ray into the World
	FCollisionObjectQueryParams QueryParams(FCollisionObjectQueryParams::AllObjects);
	FHitResult Result;
	bool bHitWorld = TargetWorld->LineTraceSingleByObjectType(Result, WorldRay.Origin, WorldRay.PointAt(999999), QueryParams);
	if (bHitWorld)
	{
		ComponentHit = Result.GetComponent();
		HitPos = Result.ImpactPoint; 
		return FInputRayHit(Result.Distance);
	}
	return FInputRayHit();
}


void UGenerateSoundInLevel::UpdatePosition(const FRay& WorldRay)
{
	FInputRayHit HitResult = FindRayHit(WorldRay, Properties->SelectionCoordonate);
	if (HitResult.bHit)
	{
		//SelectedObject = HitResult.HitOwner;// .HitObject;
	}
}



void UGenerateSoundInLevel::OnPropertyModified(UObject* PropertySet, FProperty* Property)
{
	// if the user updated any of the property fields, update the distance
}


void UGenerateSoundInLevel::Render(IToolsContextRenderAPI* RenderAPI)
{
	FPrimitiveDrawInterface* PDI = RenderAPI->GetPrimitiveDrawInterface();
	// draw a thin line that shows through objects
	/*
	PDI->DrawLine(Properties->StartPoint, Properties->EndPoint,
		FColor(240, 16, 16), SDPG_Foreground, 2.0f, 0.0f, true);
	// draw a thicker line that is depth-tested
	PDI->DrawLine(Properties->StartPoint, Properties->EndPoint,
		FColor(240, 16, 16), SDPG_World, 4.0f, 0.0f, true);
	*/
}


#undef LOCTEXT_NAMESPACE
