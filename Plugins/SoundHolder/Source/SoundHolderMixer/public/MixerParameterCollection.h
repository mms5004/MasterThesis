#pragma once

#include "CoreMinimal.h"
#include "MixerParameterCollection.generated.h"

USTRUCT(BlueprintType)
struct FMixerAudioParameter
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString ParameterName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Value = 0.0f;
};

UCLASS(BlueprintType)
class UMixerParameterCollection : public UDataAsset
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FMixerAudioParameter> Parameters;

};