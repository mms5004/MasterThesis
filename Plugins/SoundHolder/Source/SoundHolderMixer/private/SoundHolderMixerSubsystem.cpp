// Fill out your copyright notice in the Description page of Project Settings.

#include "SoundHolderMixerSubsystem.h"


void USoundHolderMixerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    UE_LOG(LogTemp, Log, TEXT("Sound Holder Mixer Subsystem initialized"));

    InstantiateMixerActor(AAlphaMixerActor::StaticClass());   
}

void USoundHolderMixerSubsystem::Deinitialize()
{
    Alphas.Empty();
}

void USoundHolderMixerSubsystem::OverrideMixerActor(UClass* Class, bool DeleteOlderMixer)
{
    if (MixerActor && DeleteOlderMixer) 
    {
        MixerActor->Destroy();
    }
    InstantiateMixerActor(Class);
}

void USoundHolderMixerSubsystem::OverrideMixerParameterCollection(UMixerParameterCollection* NewCollection)
{
    MixerParameterCollection = NewCollection;
}

void USoundHolderMixerSubsystem::SetAlphaInput(FString Key, FInstancedStruct Value)
{
    float* Found = Alphas.Find(Key); //Detect if key already exist

    if (!Value.IsValid() || Key == "") //If empty call are made
    {return;}

    if (const FMixerFloat* FloatChecker = Value.GetPtr<FMixerFloat>()) // Check if FInstancedStruct is a float
    {
        if (Found) 
        {
            if (!FMath::IsNearlyEqual(*Found, FloatChecker->Value))
            {
                UpdateMixerParameter(Key, FloatChecker->Value);

                //Need to remove this
                Alphas.Add(Key, FloatChecker->Value);
                OnAlphaChanged.Broadcast(Key, FloatChecker->Value);
            }
        }       
    }
   //Not directly an alpha and need to be send into the mixer actor
    MixerActor->EvaluateMixingLogic(Key, Value);
}

float USoundHolderMixerSubsystem::GetAlpha(FString Key) const
{
    const float* Value = Alphas.Find(Key);
    return Value ? *Value : 0.0f;
}




//Private functions

void USoundHolderMixerSubsystem::InstantiateMixerActor(UClass* Class)
{
    if (!Class) {return;}
    UWorld* World = GetWorld();
    if (World) //MixerActor = World->SpawnActor<AAlphaMixerActor>();
    {        
        FActorSpawnParameters Params;
        Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
        Params.ObjectFlags = RF_Transient;
        MixerActor = World->SpawnActor<AAlphaMixerActor>(Class, Params);
    }
}

void USoundHolderMixerSubsystem::UpdateMixerParameter(FString Name, float NewValue)
{
    if (MixerParameterCollection)
    {
        for (auto& Entry : MixerParameterCollection->Parameters)
        {
            if (Entry.ParameterName == Name)
            {
                Entry.Value = NewValue;
                OnAlphaChanged.Broadcast(Name, NewValue);
                break;
            }
        }
    }    
}