// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AlphaInputStruct.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "InstancedStruct.h"
#include "AlphaMixerActor.h"
#include "MixerParameterCollection.h"
#include "SoundHolderMixerSubsystem.generated.h"

/**
 * Transfer data from actor to mixer actor and static alphas to actors
 */
UCLASS(config = Game, defaultconfig)
class SOUNDHOLDERMIXER_API USoundHolderMixerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    virtual void Deinitialize() override;
    
    //////////////////////////////////////////////////////
    //Virtual Mixer Table Actor
    //////////////////////////////////////////////////////

    UFUNCTION(BlueprintCallable, Category = "SoundHolderMixer")
    void OverrideMixerActor(UClass* Class, bool DeleteOlderMixer);

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    AAlphaMixerActor* MixerActor;

    //////////////////////////////////////////////////////
    // Mixer Parameters Collection
    //////////////////////////////////////////////////////

    UFUNCTION(BlueprintCallable, Category = "SoundHolderMixer")
    void OverrideMixerParameterCollection(UMixerParameterCollection* NewCollection);

    UPROPERTY() // RTPC-like variables, the runtime values are stocked in a static class called in cpp
    TObjectPtr<UMixerParameterCollection> MixerParameterCollection;

    //////////////////////////////////////////////////////
    // Get/Set Mixer Values
    //////////////////////////////////////////////////////

    UFUNCTION(BlueprintCallable, Category = "SoundHolderMixer") // Setter
    void SetAlphaInput(FString Name, FInstancedStruct Value);

    
    UFUNCTION(BlueprintPure, Category = "SoundHolderMixer") // Getter
    float GetAlpha(FString Name, float DefaultValue) const;

    // transfer variable in an AI blackboard style
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAlphahanged, FString, AlphaName, float, Alpha);
    UPROPERTY(BlueprintAssignable, Category = "SoundHolderMixer")
    FOnAlphahanged OnAlphaChanged;


    // Update and setup
private: 
    void InstantiateMixerActor(UClass* Class);
};