// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "InstancedStruct.h"
#include "AlphaMixerActor.h"
#include "SoundHolderMixerSubsystem.generated.h"

/**
 * Transfer data from actor to mixer actor and static alphas to actors
 */
UCLASS()
class SOUNDHOLDERMIXER_API USoundHolderMixerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    virtual void Deinitialize() override;
    
    UFUNCTION(BlueprintCallable, Category = "SoundHolderMixer")
    void OverrideMixerActor(UClass* Class, bool DeleteOlderMixer);
    
    UPROPERTY() // RTPC-like variables
    TMap<FName, float> Alphas;

    
    UFUNCTION(BlueprintCallable, Category = "SoundHolderMixer") // Setter
    void SetAlphaInput(FName Key, FInstancedStruct Value);

    
    UFUNCTION(BlueprintPure, Category = "SoundHolderMixer") // Getter
    float GetAlpha(FName Key) const;

    // transfer variable in an AI blackboard style
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAlphahanged, FName, AlphaName, float, Alpha);
    UPROPERTY(BlueprintAssignable, Category = "SoundHolderMixer")
    FOnAlphahanged OnAlphaChanged;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    AAlphaMixerActor* MixerActor;

protected: 
    void InstantiateMixerActor(UClass* Class);
};