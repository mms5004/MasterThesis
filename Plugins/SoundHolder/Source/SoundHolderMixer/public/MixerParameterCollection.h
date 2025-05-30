#pragma once

#include "CoreMinimal.h"
#include "AlphaParameters.h"
#include "MixerParameterCollection.generated.h"

UCLASS(Blueprintable, BlueprintType)
class UMixerParameterCollection : public UPrimaryDataAsset
{
    GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString CollectionName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TMap<FString, float> Parameters;
};