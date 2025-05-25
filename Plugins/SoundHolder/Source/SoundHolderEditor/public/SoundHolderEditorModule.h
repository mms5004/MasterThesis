#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
//#include "Modules/ModuleInterface.h"

// Module definition for the editor mode
class FSoundHolderEditor : public FDefaultModuleImpl
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
