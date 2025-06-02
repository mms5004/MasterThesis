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
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AlphaStruct")
    float Value = 0.f;
};

USTRUCT(BlueprintType)
struct FMixerFloatArray : public FMixerBase
{
    GENERATED_BODY()
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AlphaStruct")
    TArray<float> Values;
};

USTRUCT(BlueprintType)
struct FMixerInt : public FMixerBase
{
    GENERATED_BODY()
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AlphaStruct")
    int Value = 0;
};

USTRUCT(BlueprintType)
struct FMixerIntArray : public FMixerBase
{
    GENERATED_BODY()
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AlphaStruct")
    TArray<int> Values;
};

USTRUCT(BlueprintType)
struct FMixerBool : public FMixerBase
{
    GENERATED_BODY()
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AlphaStruct")
    bool Value = false;
};

USTRUCT(BlueprintType)
struct FMixerBoolArray : public FMixerBase
{
    GENERATED_BODY()
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AlphaStruct")
    TArray<bool> Values;
};

USTRUCT(BlueprintType)
struct FMixerVector : public FMixerBase
{
    GENERATED_BODY()
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AlphaStruct")
    FVector Value = FVector::ZeroVector;
};

USTRUCT(BlueprintType)
struct FMixerVectorArray : public FMixerBase
{
    GENERATED_BODY()
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AlphaStruct")
    TArray<FVector> Values;
};

USTRUCT(BlueprintType)
struct FMixerRotator : public FMixerBase
{
    GENERATED_BODY()
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AlphaStruct")
    FRotator Value;
};

USTRUCT(BlueprintType)
struct FRTPCEnum : public FMixerBase
{
    GENERATED_BODY()
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AlphaStruct")
    TObjectPtr<UEnum> Value;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AlphaStruct")
    int32 EnumValue = 0;
};

USTRUCT(BlueprintType)
struct FMixerString : public FMixerBase
{
    GENERATED_BODY()
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AlphaStruct")
    FString Value = "";
};