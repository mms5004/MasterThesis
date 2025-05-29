// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "AlphaMixerActor.generated.h"

class USoundHolderMixerSubsystem;

UCLASS()
class SOUNDHOLDERMIXER_API AAlphaMixerActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AAlphaMixerActor();

	//Separation of alpha update and input update 
	UFUNCTION()
	void OnAlphaUpdated(FName AlphaName, float AlphaValue);

	UFUNCTION(BlueprintImplementableEvent, Category = "SoundHolderMixer")
	void EvaluateMixingLogic(FName InputName, FInstancedStruct InputValue);

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UPROPERTY(EditAnywhere, Category = "SoundHolderMixer")
	TArray<FName> AlphaInputs;

	UPROPERTY(BlueprintReadOnly, Category = "SoundHolderMixer")
	TMap<FName, float> AlphaOutput;

private:
	USoundHolderMixerSubsystem* SoundHolderSubsystem;

};
