#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AlphaInputStruct.generated.h"

USTRUCT(BlueprintType)
struct FMixerFloat
{
    GENERATED_BODY()
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Value = 0.f;
};

USTRUCT(BlueprintType)
struct FMixerFloatArray
{
    GENERATED_BODY()
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<float> Values;
};

USTRUCT(BlueprintType)
struct FMixerInt
{
    GENERATED_BODY()
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int Value = 0;
};

USTRUCT(BlueprintType)
struct FMixerIntArray
{
    GENERATED_BODY()
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<int> Values;
};

USTRUCT(BlueprintType)
struct FMixerBool
{
    GENERATED_BODY()
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool Value = false;
};

USTRUCT(BlueprintType)
struct FMixerBoolArray
{
    GENERATED_BODY()
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<bool> Values;
};

USTRUCT(BlueprintType)
struct FMixerVector
{
    GENERATED_BODY()
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector Value = FVector::ZeroVector;
};

USTRUCT(BlueprintType)
struct FMixerVectorArray
{
    GENERATED_BODY()
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FVector> Values;
};

USTRUCT(BlueprintType)
struct FMixerRotator
{
    GENERATED_BODY()
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FRotator Value;
};

USTRUCT(BlueprintType)
struct FRTPCEnum
{
    GENERATED_BODY()
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<UEnum> Value;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 EnumValue = 0;
};

USTRUCT(BlueprintType)
struct FMixerString
{
    GENERATED_BODY()
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Value = "";
};
