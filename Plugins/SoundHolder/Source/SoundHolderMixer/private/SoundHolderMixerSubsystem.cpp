// Fill out your copyright notice in the Description page of Project Settings.

#include "SoundHolderMixerSubsystem.h"
#include "SubsystemSettings.h"
#include "AlphaParameters.h"
#include "Engine/World.h" // for to be compile in package plugin : FActorSpawnParameters
TMap<FString, float> FAlphaParameters::AlphaMap;
FCriticalSection FAlphaParameters::Mutex;

void USoundHolderMixerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    UE_LOG(LogTemp, Log, TEXT("Sound Holder Mixer Subsystem initialized"));

    //Get default value
    const UBlueprintSubsystemSettings* Settings = GetDefault<UBlueprintSubsystemSettings>();

    if (TSubclassOf<AAlphaMixerActor> DefaultMixer = Settings->DefaultMixerActor)
    {
        InstantiateMixerActor(DefaultMixer);
    }
    if (TSoftObjectPtr<UMixerParameterCollection> DefaultParameterCollection = Settings->DefaultMixerParameterCollection) 
    {
        OverrideMixerParameterCollection(DefaultParameterCollection.LoadSynchronous());
    }
}

void USoundHolderMixerSubsystem::Deinitialize()
{
    FAlphaParameters::AlphaMap.Empty();
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

    FAlphaParameters::AlphaMap.Empty();
    for (const auto& Elem : MixerParameterCollection->Parameters)
    {
        FAlphaParameters::Add(Elem.Key, Elem.Value);
    }
}



//Update Alpha if name correspond and data is valid. In other cases, send data into the mixer actor
void USoundHolderMixerSubsystem::SetAlphaInput(FString Name, FInstancedStruct Value)
{
    if (!Value.IsValid() || Name == "") {return;} //In case of empty/not valid call

    float* Found = FAlphaParameters::AlphaMap.Find(Name); //Detect if key already exist
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
    MixerActor->MixingLogic(Name, Value);
}

//Return default value if parameter not found
float USoundHolderMixerSubsystem::GetAlpha(FString Name, float DefaultValue) const
{
    return FAlphaParameters::Get(Name, DefaultValue);
}


//Private function
void USoundHolderMixerSubsystem::InstantiateMixerActor(UClass* Class)
{
    if (!Class) {return;}
    UWorld* World = GetWorld();
    if (World)
    {        
        FActorSpawnParameters Params;
        Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
        Params.ObjectFlags = RF_Transient;
        MixerActor = World->SpawnActor<AAlphaMixerActor>(Class, Params);
    }
}