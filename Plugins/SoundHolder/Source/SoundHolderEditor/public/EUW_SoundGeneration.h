// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EditorUtilityWidget.h"
#include "EUW_SoundGeneration.generated.h"

/**
 * 
 */
UCLASS() //Suffix cut 
class SOUNDHOLDEREDITOR_API UEUW_SoundGeneration : public UEditorUtilityWidget
{
	GENERATED_BODY()
	
public:

	void SetupParameters(/*FString suffix, */ UPrimitiveComponent * selectedComponent);

	UFUNCTION(BlueprintImplementableEvent, Category = "SoundHolderTool")
	void ParametersUpdated(/*bool suffixChanged, */ bool ComponentChanged);

protected:
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Parameters")
	TArray<UObject*> ObjList; //or AActor if needed

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Parameters")
	UPrimitiveComponent* SelectedComponent;

	//To do : select the settings data asset by default
};