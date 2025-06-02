// Fill out your copyright notice in the Description page of Project Settings.


#include "AlphaMixerActor.h"
#include "SoundHolderMixerSubsystem.h"
#include "Engine/GameInstance.h"

//Need to refactor : OnAlphaUpdated isn't as usefull as before, alpha is send with "MixingLogic" function
//The logic could be separated for performance

// Sets default values
AAlphaMixerActor::AAlphaMixerActor()
{
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AAlphaMixerActor::BeginPlay()
{
	Super::BeginPlay();
    if (UGameInstance* GameInstance = GetGameInstance())
    {
        SoundHolderSubsystem = GameInstance->GetSubsystem<USoundHolderMixerSubsystem>();
        if (SoundHolderSubsystem)
        {
            SoundHolderSubsystem->OnAlphaChanged.AddDynamic(this, &AAlphaMixerActor::OnAlphaUpdated);
        }
    }
}

void AAlphaMixerActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    if (SoundHolderSubsystem)
    {
        SoundHolderSubsystem->OnAlphaChanged.RemoveDynamic(this, &AAlphaMixerActor::OnAlphaUpdated);
    }
    Super::EndPlay(EndPlayReason);
}

void AAlphaMixerActor::OnAlphaUpdated(FString AlphaName, float AlphaValue)
{
    if (AlphaInputs.Contains(AlphaName))
    {
        //auto localStruct = new FMixerFloat;
        //FInstancedStruct alphaStruct = FInstancedStruct::Make(localStruct);
        //EvaluateMixingLogic(AlphaName, alphaStruct);
    }
}