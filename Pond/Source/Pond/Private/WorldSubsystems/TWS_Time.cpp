// Fill out your copyright notice in the Description page of Project Settings.
#include "WorldSubsystems/TWS_Time.h"

UTWS_Time::UTWS_Time()
{
    static ConstructorHelpers::FObjectFinder<UDataTable> DT_Incidents_Time_Loader(TEXT("/Script/Engine.DataTable'/Game/MyContent/DataTables/Incidents_Time.Incidents_Time'"));
    if(DT_Incidents_Time_Loader.Succeeded()){
        DT_Incidents_Time = DT_Incidents_Time_Loader.Object;
    }
}

void UTWS_Time::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);

    //Read DataTable
    TArray<FIncident_Time*> Rows;
    DT_Incidents_Time->GetAllRows<FIncident_Time>(TEXT("WS_Time: Incidents_Time: GetAllRows"), Rows);
    TArray<FName> RowNames = DT_Incidents_Time->GetRowNames();

    //Init Spawnable
    for(int i = 0; i < Rows.Num(); i++){
        FString Name = RowNames[i].ToString();
        Spawnable.Add(MakeTuple(Name, false));
    }
    for(int i = 0; i < Rows.Num(); i++){
        FString Name = RowNames[i].ToString();
        float Start = Rows[i]->SpawnableTimeStart;
        float End = Rows[i]->SpawnableTimeEnd;

        if(End < Start){
            if(Time < Start || (Time >= End && Time < 24.0f)){
                Spawnable[Name] = true;
                //UE_LOG(LogTemp, Warning, TEXT("ADD: %s, %f"), *Name, Time);
            }
        }
        else{
            if(Time >= Start && Time < End){
                Spawnable[Name] = true;
                //UE_LOG(LogTemp, Warning, TEXT("ADD: %s, %f"), *Name, Time);
            }
        }
    }

    //Init StartTimes & EndTimes
    for(int i = 0; i < Rows.Num(); i++){
        StartTimes.Add(MakeTuple(Rows[i]->SpawnableTimeStart, RowNames[i].ToString()));
        EndTimes.Add(MakeTuple(Rows[i]->SpawnableTimeEnd, RowNames[i].ToString()));
    }
    StartTimes.Sort([](auto a, auto b){ return a.Key < b.Key; });
    EndTimes.Sort([](auto a, auto b){ return a.Key < b.Key; });

    //Init StartTimesInd & EndTimesInd
    while(StartTimes[StartTimesInd].Key <= Time){
        StartTimesInd++;
    }
    while(EndTimes[EndTimesInd].Key <= Time){
        EndTimesInd++;
    }
}

void UTWS_Time::Deinitialize()
{
    Super::Deinitialize();
}

void UTWS_Time::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    //Update Time
    bool Overflow = false;
    Time = Time + DeltaTime * TimeSpeed;
    if(Time >= 24.0f){
        Time = Time - 24.0f;
        Overflow = true;
    }
    if(NotifyTimeDelegate.IsBound())
        NotifyTimeDelegate.Broadcast(Time);

    //Update CurrentSpawnable
    if(Overflow){
        while(StartTimesInd < StartTimes.Num() && StartTimes[StartTimesInd].Key < 24.0f){
            //UE_LOG(LogTemp, Warning, TEXT("ADD: %s, %f"), *StartTimes[StartTimesInd].Value, Time);
            Spawnable[StartTimes[StartTimesInd].Value] = true;
            StartTimesInd++;
        }
        while(EndTimesInd < EndTimes.Num() && EndTimes[EndTimesInd].Key < 24.0f){
            //UE_LOG(LogTemp, Warning, TEXT("REMOVE: %s, %f"), *EndTimes[EndTimesInd].Value, Time);
            Spawnable[EndTimes[EndTimesInd].Value] = false;
            EndTimesInd++;
        }
        StartTimesInd = 0;
        EndTimesInd = 0;
        while(StartTimesInd < StartTimes.Num() && StartTimes[StartTimesInd].Key < Time){
            //UE_LOG(LogTemp, Warning, TEXT("ADD: %s, %f"), *StartTimes[StartTimesInd].Value, Time);
            Spawnable[StartTimes[StartTimesInd].Value] = true;
            StartTimesInd++;
        }
        while(EndTimesInd < EndTimes.Num() && EndTimes[EndTimesInd].Key < Time){
            //UE_LOG(LogTemp, Warning, TEXT("REMOVE: %s, %f"), *EndTimes[EndTimesInd].Value, Time);
            Spawnable[EndTimes[EndTimesInd].Value] = false;
            EndTimesInd++;
        }
    }
    else{
        while(StartTimesInd < StartTimes.Num() && StartTimes[StartTimesInd].Key < Time){
            //UE_LOG(LogTemp, Warning, TEXT("ADD: %s, %f"), *StartTimes[StartTimesInd].Value, Time);
            Spawnable[StartTimes[StartTimesInd].Value] = true;
            StartTimesInd++;
        }
        while(EndTimesInd < EndTimes.Num() && EndTimes[EndTimesInd].Key < Time){
            //UE_LOG(LogTemp, Warning, TEXT("REMOVE: %s, %f"), *EndTimes[EndTimesInd].Value, Time);
            Spawnable[EndTimes[EndTimesInd].Value] = false;
            EndTimesInd++;
        }
    }
}

TStatId UTWS_Time::GetStatId() const
{
    return GetStatID();
}