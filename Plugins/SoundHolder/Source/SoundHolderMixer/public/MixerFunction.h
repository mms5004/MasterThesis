#pragma once
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SoundHolderMixerSubsystem.h"
#include "AlphaParameters.h"
#include "MixerFunction.generated.h"

USTRUCT(BlueprintType)
struct FMixerAlpha
{
	GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Name;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Value;
};

UCLASS()
class SOUNDHOLDERMIXER_API UFLMixerFunction : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Mixer Utility", meta = (Keywords = "Get Subsystem"))
	static bool GetSubsystem(USoundHolderMixerSubsystem*& MixerSubsystem);

    UFUNCTION(BlueprintCallable, Category = "Mixer Utility", meta = (Keywords = "Get Alphas", OutParm = "OutputAlpha"))
    static void GetAlphas(TArray<FMixerAlpha>& OutputAlpha);
};

inline bool UFLMixerFunction::GetSubsystem(USoundHolderMixerSubsystem*& MixerSubsystem)
{
    for (const FWorldContext& Context : GEngine->GetWorldContexts())
    {
        if (UWorld * World = Context.World()) //Could compare the mode too : Context.WorldType == EWorldType::PIE 
        {
            if (auto* instance = World->GetGameInstance()) 
            {
                MixerSubsystem = instance->GetSubsystem<USoundHolderMixerSubsystem>();
                if (MixerSubsystem) 
                {
                    return true;
                }
            }
        }
    }
	return false;
}

inline void UFLMixerFunction::GetAlphas(TArray<FMixerAlpha>& OutputAlpha)
{
    const TMap<FString, float>& Parameters = FAlphaParameters::GetAlphaMap();

    FMixerAlpha localAlpha;
    for (auto& item : Parameters)
    {
        localAlpha.Name = item.Key;
        localAlpha.Value = item.Value;
        OutputAlpha.Add(localAlpha);
    }
}
