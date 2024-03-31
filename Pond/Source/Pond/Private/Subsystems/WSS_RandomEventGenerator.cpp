// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/WSS_RandomEventGenerator.h"

void UWSS_RandomEventGenerator::Initialize(FSubsystemCollectionBase &Collection)
{
    //  TEST
    Test = NewObject<UREGEvent>();
    Test->Name = "Awesome";
    Test12 = NewObject<UREGEvent>();
    Test12->Name = "WTF";
    
    Test->InfluencedBy.Add(FInfluence("Hello.World", 0.5f));
    Test12->InfluencedBy.Add(FInfluence("Foo.Bar", 0.25f));

    AddEvent(Test);
    AddEvent(Test12);

    TArray<FInfluence> Test4;
    Test4.Add(FInfluence("Foo.Bar", 4.0f));
    Notify(Test4);
    //  ~TEST

    // GetWorld()->GetTimerManager().SetTimer(
    //     TimerHandle,
    //     this,
    //     &UWSS_RandomEventGenerator::Assess,
    //     5.0f,
    //     true
    // );
}

void UWSS_RandomEventGenerator::Deinitialize()
{

}

void UWSS_RandomEventGenerator::Notify(TArray<FInfluence> Incidents)
{
    for(auto Elem : Incidents){
        FString Tag = Elem.Tag;
        float Strength = Elem.Strength;
        if(Environment.Find(Tag) == nullptr)
            Environment.Add(Tag, 0.0f);
        Environment[Tag] += Strength;
    }
    Assess();
}

void UWSS_RandomEventGenerator::Assess()
{
    for(auto Elem : Events){
        float Score = Elem.Value->GetScore(Environment);
        InvokeMeter[Elem.Key] += Score;
        if(InvokeMeter[Elem.Key] > 0.5f)
            Elem.Value->Invoke();
    }
}

void UWSS_RandomEventGenerator::AddEvent(UREGEvent* NewEvent)
{
    Events.Add(NewEvent->Name, NewEvent);
    InvokeMeter.Add(NewEvent->Name, 0.0f);
}