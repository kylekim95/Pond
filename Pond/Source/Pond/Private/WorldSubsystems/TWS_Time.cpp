// Fill out your copyright notice in the Description page of Project Settings.
#include "WorldSubsystems/TWS_Time.h"

void UTWS_Time::Initialize(FSubsystemCollectionBase &Collection)
{
    Super::Initialize(Collection);

    Timer = 20.0f;
    TimerSpeedMultiplier = 0.03125f;
}

void UTWS_Time::Deinitialize()
{
    Super::Deinitialize();
}

void UTWS_Time::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    Timer = (Timer + DeltaTime * TimerSpeedMultiplier);
    if(Timer >= 24.0f){
        Timer = Timer - 24.0f;
    }
    if(NotifyTimeDelegate.IsBound()){
        NotifyTimeDelegate.Broadcast(Timer);
    }
}

TStatId UTWS_Time::GetStatId() const
{
    return GetStatID();
}

float UTWS_Time::GetCurrentTime()
{
    return Timer;
}