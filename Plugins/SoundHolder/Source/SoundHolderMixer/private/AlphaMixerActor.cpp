// Fill out your copyright notice in the Description page of Project Settings.


#include "AlphaMixerActor.h"
#include "SoundHolderMixerSubsystem.h"

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
            //SoundHolderSubsystem->SetAlphaInput.AddDynamic(this, &AAlphaMixerActor::EvaluateMixingLogic);
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

void AAlphaMixerActor::OnAlphaUpdated(FName AlphaName, float AlphaValue)
{
    if (AlphaInputs.Contains(AlphaName))
    {
        //FInstancedStruct TestStruct = FInstancedStruct::Make(FVector::UpVector);
        //FInstancedStruct GenericStruct = FInstancedStruct::Make(AlphaValue);
        //EvaluateMixingLogic(AlphaName, GenericStruct);
    }
}