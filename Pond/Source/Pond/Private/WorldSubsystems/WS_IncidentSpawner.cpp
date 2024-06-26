// Fill out your copyright notice in the Description page of Project Settings.
#include "WorldSubsystems/WS_IncidentSpawner.h"

UWS_IncidentSpawner::UWS_IncidentSpawner()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> IncidentsRawDataTableLoader(TEXT("/Script/Engine.DataTable'/Game/MyContent/DataTables/Incidents/Incidents.Incidents'"));
    if(IncidentsRawDataTableLoader.Succeeded()){
        IncidentsRawDataTable = IncidentsRawDataTableLoader.Object;
    }
}

void UWS_IncidentSpawner::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);

    OnGetIncidentsDelegate.BindUObject(this, &UWS_IncidentSpawner::OnGetIncidents);
    OnNewIncidentDelegate.BindUObject(this, &UWS_IncidentSpawner::OnNewIncident);
}

void UWS_IncidentSpawner::Deinitialize()
{
    Super::Deinitialize();
}

void UWS_IncidentSpawner::PostInitialize()
{
    Super::PostInitialize();

    WS_Network = GetWorld()->GetSubsystem<UWS_Network>();
}

void UWS_IncidentSpawner::OnWorldBeginPlay(UWorld& InWorld)
{
    Super::OnWorldBeginPlay(InWorld);

    //Synchronize Server DB & Client DataTable
    WS_Network->SendHttpGet("/get_incidents", OnGetIncidentsDelegate);
}

void UWS_IncidentSpawner::OnGetIncidents(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnected)
{
    FString ResponseJson = Response->GetContentAsString();
    TSharedPtr<FJsonObject> JsonObject;
    TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(ResponseJson);
    FJsonSerializer::Deserialize(Reader, JsonObject);
    for(auto Elem : JsonObject->GetArrayField("rows")){
        FString Name = Elem->AsObject()->GetStringField("name");
        IncidentsSpawnDataMap.Add(Name, FIncidentsSpawnData());
    }

    for(auto Elem : IncidentsRawDataTable->GetRowMap()){
        FString Name = Elem.Key.ToString();
        FIncidentsRawData* Data = (FIncidentsRawData*)(Elem.Value);
        if(IncidentsSpawnDataMap.Find(Name) == nullptr){
            FNewIncident NewIncident;
            NewIncident.name = Name;
            NewIncident.description = Data->Description;
            WS_Network->SendHttpPost("/new_incident", NewIncident, OnNewIncidentDelegate);

            FIncidentsSpawnData NewIncidentSpawnData;
            IncidentsSpawnDataMap.Add(Name, NewIncidentSpawnData);
        }
        else{
            
        }
    }
}

void UWS_IncidentSpawner::OnNewIncident(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnected)
{
    FString ResponseJson = Response->GetContentAsString();
    // TSharedPtr<FJsonObject> JsonObject;
    // TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(ResponseJson);
    // FJsonSerializer::Deserialize(Reader, JsonObject);
    UE_LOG(LogTemp, Warning, TEXT("%s"), *ResponseJson);
}