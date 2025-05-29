#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AlphaInputStruct.generated.h"


USTRUCT()
struct FMixerBase
{
    GENERATED_BODY()
};


USTRUCT(BlueprintType)
struct FMixerFloat : public FMixerBase
{
    GENERATED_BODY()
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Value = 0.f;
};

USTRUCT(BlueprintType)
struct FMixerFloatArray : public FMixerBase
{
    GENERATED_BODY()
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<float> Values;
};

USTRUCT(BlueprintType)
struct FMixerInt : public FMixerBase
{
    GENERATED_BODY()
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int Value = 0;
};

USTRUCT(BlueprintType)
struct FMixerIntArray : public FMixerBase
{
    GENERATED_BODY()
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<int> Values;
};

USTRUCT(BlueprintType)
struct FMixerBool : public FMixerBase
{
    GENERATED_BODY()
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool Value = false;
};

USTRUCT(BlueprintType)
struct FMixerBoolArray : public FMixerBase
{
    GENERATED_BODY()
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<bool> Values;
};

USTRUCT(BlueprintType)
struct FMixerVector : public FMixerBase
{
    GENERATED_BODY()
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector Value = FVector::ZeroVector;
};

USTRUCT(BlueprintType)
struct FMixerVectorArray : public FMixerBase
{
    GENERATED_BODY()
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FVector> Values;
};

USTRUCT(BlueprintType)
struct FMixerRotator : public FMixerBase
{
    GENERATED_BODY()
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FRotator Value;
};

USTRUCT(BlueprintType)
struct FRTPCEnum : public FMixerBase
{
    GENERATED_BODY()
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<UEnum> Value;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 EnumValue = 0;
};

USTRUCT(BlueprintType)
struct FMixerString : public FMixerBase
{
    GENERATED_BODY()
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Value = "";
};