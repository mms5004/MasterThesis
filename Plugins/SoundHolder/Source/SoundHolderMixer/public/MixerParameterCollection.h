#pragma once

#include "CoreMinimal.h"
#include "AlphaParameters.h"
#include "Engine/DataAsset.h"
#include "MixerParameterCollection.generated.h"

UCLASS(Blueprintable, BlueprintType)
class UMixerParameterCollection : public UPrimaryDataAsset
{
    GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mixer")
    FString CollectionName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mixer")
    TMap<FString, float> Parameters;
};