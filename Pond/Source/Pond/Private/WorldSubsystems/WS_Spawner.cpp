// Fill out your copyright notice in the Description page of Project Settings.
#include "WorldSubsystems/WS_Spawner.h"
#include "Incident.h"

UWS_Spawner::UWS_Spawner()
{
    static ConstructorHelpers::FObjectFinder<UDataTable> DT_Incidents_Type_Loader(TEXT("/Script/Engine.DataTable'/Game/MyContent/DataTables/Incidents_Type.Incidents_Type'"));
    if(DT_Incidents_Type_Loader.Succeeded()){
        DT_Incidents_Type = DT_Incidents_Type_Loader.Object;
    }
}

void UWS_Spawner::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);

    //Read DataTable
    TArray<FIncident_Type*> Rows;
    DT_Incidents_Type->GetAllRows<FIncident_Type>(TEXT("WS_Spawner: Incidents_Type: GetAllRows"), Rows);
    TArray<FName> RowNames = DT_Incidents_Type->GetRowNames();
    for(int i = 0; i < Rows.Num(); i++){
        AtoSMap.Add(RowNames[i].ToString(), Rows[i]->ActorToSpawn);
        TagsMap.Add(RowNames[i].ToString(), TArray<FString>());
        LastSpawned_Timestamp.Add(RowNames[i].ToString(), FDateTime::MinValue());
        for(int j = 0; j < Rows[i]->SpawnablePositionTags.Num(); j++){
            TagsMap[RowNames[i].ToString()].Add(Rows[i]->SpawnablePositionTags[j]);
        }
    }
}

void UWS_Spawner::Deinitialize()
{
    Super::Deinitialize();
}

void UWS_Spawner::PostInitialize()
{
    Super::PostInitialize();
    
    WS_UserPreference = GetWorld()->GetSubsystem<UWS_UserPreference>();
    WS_Position = GetWorld()->GetSubsystem<UWS_Position>();

    UTWS_Time* TWS_Time = GetWorld()->GetSubsystem<UTWS_Time>();
    if(TWS_Time && WS_UserPreference && WS_Position)
        TWS_Time->NotifyTimeDelegate.AddDynamic(this, &UWS_Spawner::OnNotifyTime);
    else
        UE_LOG(LogTemp, Warning, TEXT("WS_Spawner::Required WorldSubsystems not initialized"));
}

void UWS_Spawner::OnWorldBeginPlay(UWorld& InWorld)
{
    Super::OnWorldBeginPlay(InWorld);
}

void UWS_Spawner::OnNotifyTime(float Time)
{
    TArray<FString> PreferredIncidents = WS_UserPreference->PreferredIncidents;
    
    if(PreferredIncidents.Num() > 0){
        int MostPreferredIndex = 0;
        FTimespan Temp = FDateTime::Now() - LastSpawned_Timestamp[PreferredIncidents[MostPreferredIndex]];
        if(Temp.GetTotalSeconds() > 30.0f){
            TArray<FString> Tags = TagsMap[PreferredIncidents[MostPreferredIndex]];
            FString Total = "";
            for(int i = 0; i < Tags.Num(); i++){
                Total += "( " + Tags[i];
                if(i != Tags.Num() - 1){
                    Total += " & ";
                }
            }
            Total += " )";

            TSet<FVector> Output;
            WS_Position->Query(Output, Total);

            FRotator Rotator;
            GetWorld()->SpawnActor<AIncident>(
                AtoSMap[PreferredIncidents[MostPreferredIndex]], 
                Output.Array()[0],
                Rotator
            );

            LastSpawned_Timestamp[PreferredIncidents[MostPreferredIndex]] = FDateTime::Now();
        }
        else{
            MostPreferredIndex++;
            if(MostPreferredIndex >= PreferredIncidents.Num()){
                UE_LOG(LogTemp, Warning, TEXT("Nothing to spawn"));
            }
        }
    }
}