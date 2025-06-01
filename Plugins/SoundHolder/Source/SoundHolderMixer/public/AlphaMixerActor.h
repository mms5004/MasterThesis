// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InstancedStruct.h"
#include "GameFramework/Actor.h"
#include "AlphaMixerActor.generated.h"

class USoundHolderMixerSubsystem;

UCLASS()
class SOUNDHOLDERMIXER_API AAlphaMixerActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AAlphaMixerActor();


	UFUNCTION()
	void OnAlphaUpdated(FString Name, float AlphaValue);

	UFUNCTION(BlueprintImplementableEvent, Category = "SoundHolderMixer")
	void MixingLogic(const FString& Name, FInstancedStruct InputValue);

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UPROPERTY(EditAnywhere, Category = "SoundHolderMixer")
	TArray<FString> AlphaInputs;

	UPROPERTY(BlueprintReadOnly, Category = "SoundHolderMixer")
	TMap<FString, float> AlphaOutput;

	UPROPERTY(BlueprintReadOnly, Category = "SoundHolderMixer")
	TArray<FString> InputNames;

private:
	USoundHolderMixerSubsystem* SoundHolderSubsystem;
};