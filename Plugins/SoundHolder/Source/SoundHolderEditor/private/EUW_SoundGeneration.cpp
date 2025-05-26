// Fill out your copyright notice in the Description page of Project Settings.


#include "EUW_SoundGeneration.h"


void UEUW_SoundGeneration::SetupParameters(FString suffix, UPrimitiveComponent* selectedComponent)
{
	bool suffixChanged = false;
	bool componentChanged = false;

	if (Suffix != suffix) 
	{
		suffixChanged = true;
		Suffix = suffix;
	}

	if (SelectedComponent != selectedComponent)
	{
		componentChanged = true;
		SelectedComponent = selectedComponent;
	}

	if (suffixChanged || componentChanged) 
	{
		ParametersUpdated(suffixChanged, componentChanged);
	}

	//To test, not sure it's secure 
	/*
	ParametersUpdated(
		(Suffix != suffix)? suffix = Suffix : false,
		false
	);*/
}

void UEUW_SoundGeneration::ChangeSuffix(FString suffix)
{
	
}

void UEUW_SoundGeneration::GetAllReferences(FString suffix)
{
	
}
