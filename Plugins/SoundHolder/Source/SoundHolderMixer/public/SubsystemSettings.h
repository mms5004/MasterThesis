#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "MixerParameterCollection.h"
#include "Subsystems/SubsystemCollection.h"
#include "AlphaMixerActor.h"
#include "MixerParameterCollection.h"
#include "SubsystemSettings.generated.h"

UCLASS(config = Game, defaultconfig)
class UBlueprintSubsystemSettings : public UObject
{
	GENERATED_BODY()

public:
	//UPROPERTY(Config, EditAnywhere, Category = "Subsystem")
	TArray<TSubclassOf<UWorldSubsystem>> BlueprintSubsystems;

	UPROPERTY(Config, EditAnywhere, Category = "SoundHolder Mixer")
	TSubclassOf<AAlphaMixerActor> DefaultMixerActor;

	UPROPERTY(Config, EditAnywhere, Category = "SoundHolder Mixer")
	TSoftObjectPtr<UMixerParameterCollection> DefaultMixerParameterCollection;
};

UCLASS()
class UWorldSubsystemBPInitializer : public UWorldSubsystem
{
	GENERATED_BODY()
	virtual void Initialize(FSubsystemCollectionBase& Collection) override
	{
		const UBlueprintSubsystemSettings* Settings = GetDefault<UBlueprintSubsystemSettings>();
		for (auto Subsystem : Settings->BlueprintSubsystems)
		{
			Collection.InitializeDependency(Subsystem);
		}
	}
};