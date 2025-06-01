// Fill out your copyright notice in the Description page of Project Settings.


#include "EUW_SoundGeneration.h"


void UEUW_SoundGeneration::SetupParameters(UPrimitiveComponent* selectedComponent)
{
	bool componentChanged = false;


	if (SelectedComponent != selectedComponent)
	{
		componentChanged = true;
		SelectedComponent = selectedComponent;
	}

	if (componentChanged)
	{
		ParametersUpdated(componentChanged);
	}
}