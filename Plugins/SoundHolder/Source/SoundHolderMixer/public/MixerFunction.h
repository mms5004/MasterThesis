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
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mixer")
    FString Name;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mixer")
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