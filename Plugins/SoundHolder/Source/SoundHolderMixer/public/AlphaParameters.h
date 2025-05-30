#pragma once

#include "CoreMinimal.h"
#include "Misc/ScopeLock.h" //For multithread, I'm not sure if metasound is thread safe

class  FAlphaParameters
{
    //Allow subsystem to edit private variables
    friend class USoundHolderMixerSubsystem;

public:
    //Return a default value if key is not found
    static float Get(const FString Name,const float DefaulReturn)
    {
        FScopeLock Lock(&Mutex);
        if (float* Found = AlphaMap.Find(Name))
        {
            return *Found;
        }
        return DefaulReturn;
    }

    
    static void Set(const FString& Name,const float Value)
    {
        FScopeLock Lock(&Mutex);
        if (float* item = AlphaMap.Find(Name)) 
        {
            *item = Value;
        }
    }

    static const TMap<FString, float>& GetAlphaMap()
    {return AlphaMap;}

private:
    static TMap<FString, float> AlphaMap;
    static FCriticalSection Mutex;

    //For subsystem
    static void EmptyMap() 
    {
        FScopeLock Lock(&Mutex);
        AlphaMap.Empty();
    }
    static void Add(const FString Name, const float Value)
    {
        FScopeLock Lock(&Mutex);
        AlphaMap.Add(Name, Value);
    }
};