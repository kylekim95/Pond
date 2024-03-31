// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/REGEvent.h"

float UREGEvent::GetScore(TMap<FString, float> Environment)
{
    float score = 0.0f;
    for(auto Elem : InfluencedBy){
        if(Environment.Find(Elem.Tag) != nullptr){
            score += Environment[Elem.Tag] * Elem.Strength;
        }
    }
    return score;
}

void UREGEvent::Invoke()
{
    UE_LOG(LogTemp, Warning, TEXT("Event: %s Invoked"), *Name);
}