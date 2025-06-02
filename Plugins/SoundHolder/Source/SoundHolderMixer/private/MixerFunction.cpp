#include "MixerFunction.h"

bool UFLMixerFunction::GetSubsystem(USoundHolderMixerSubsystem*& MixerSubsystem)
{
#if WITH_EDITOR
    for (const FWorldContext& Context : GEngine->GetWorldContexts())
    {
        if (UWorld* World = Context.World()) //Could compare the mode too : Context.WorldType == EWorldType::PIE 
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
#endif
    return false;
}

void UFLMixerFunction::GetAlphas(TArray<FMixerAlpha>& OutputAlpha)
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