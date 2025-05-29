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
    if (!NewCollection || MixerParameterCollection == NewCollection) {return;}
    MixerParameterCollection = NewCollection;

    Alphas.Empty();
    for (const auto& Elem : MixerParameterCollection->Parameters)
    {
        Alphas.Add(Elem.Key, Elem.Value);
    }
}

//Update Alpha if name corresponded and data is valid. In other cases, send data into the mixer actor
void USoundHolderMixerSubsystem::SetAlphaInput(FString Name, FInstancedStruct Value)
{
    if (!Value.IsValid() || Name == "") {return;} //In case of empty/not valid call

    float* Found = Alphas.Find(Name); //Detect if key already exist
    if (Found) 
    {
        // Check if FInstancedStruct is a FMixerFloat
        if (const FMixerFloat* FloatChecker = Value.GetPtr<FMixerFloat>())
        {
            if (!FMath::IsNearlyEqual(*Found, FloatChecker->Value))
            {
                *Found = FloatChecker->Value;
                OnAlphaChanged.Broadcast(Name, FloatChecker->Value);
            }
        }       
    }

    if(MixerActor)
    MixerActor->EvaluateMixingLogic(Name, Value);
}

//Return -1 if parameter not found
float USoundHolderMixerSubsystem::GetAlpha(FString Name) const
{
    const float* Value = Alphas.Find(Name);
    return Value ? *Value : -1.0f;
}




//Private function

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