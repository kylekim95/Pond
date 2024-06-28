// Fill out your copyright notice in the Description page of Project Settings.
#include "WorldSubsystems/WS_IncidentSpawner.h"

void Normalize(TArray<float>&);
float CosineSimilarity(TArray<float>&, TArray<float>&);

UWS_IncidentSpawner::UWS_IncidentSpawner()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> IncidentsRawDataTableLoader(TEXT("/Script/Engine.DataTable'/Game/MyContent/DataTables/IncidentsRawData.IncidentsRawData'"));
    if(IncidentsRawDataTableLoader.Succeeded()){
        IncidentsRawDataTable = IncidentsRawDataTableLoader.Object;
    }
}

void UWS_IncidentSpawner::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);

    OnGetIncidentsDelegate.BindUObject(this, &UWS_IncidentSpawner::OnGetIncidents);
    OnNewIncidentDelegate.BindUObject(this, &UWS_IncidentSpawner::OnNewIncident);

    // UserState = {1.0f, 1.0f, 1.0f, 1.0f, 1.0f};
    // PrevUserState = {1.0f, 1.0f, 1.0f, 1.0f, 1.0f};
    // Mistake! should not be these values
    // Elements of UserState is the cosine distance {fear, sadness, joy, disgust, anger}
    UserState = { 0.001f, 0.001f, 0.001f, 0.001f, 0.001f };
    PrevUserState = UserState;
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
    // UpdateUserState({1.0f, 0.0f, 0.0f, 0.0f, 0.0f}, {1.0f, 0.0f, 0.0f, 0.0f, 0.0f});
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
    // UE_LOG(LogTemp, Warning, TEXT("%s"), *ResponseJson);
}

void UWS_IncidentSpawner::UpdateUserState(TArray<float> Target, TArray<float> Influence)
{
    if(Target.Num() != UserState.Num() && Influence.Num() != UserState.Num()){
        UE_LOG(LogTemp, Error, TEXT("UpdateUserState: Invalid Target/Influence vector input"));
        return;
    }

    //Target is Similarity therefore 1 - Similarity = Cosine difference
    for(int i = 0; i < UserState.Num(); i++){
        UserState[i] = FMath::Lerp(UserState[i], 1 - Target[i], Influence[i]);
    }
    float temp = CosineSimilarity(UserState, PrevUserState);

    FClosestNeighbor ClosestNeighbor;
    ClosestNeighbor.user_state = UserState;
    WS_Network->SendHttpPost("/closest_neighbor", ClosestNeighbor, OnClosestNeighborDelegate);
}

void UWS_IncidentSpawner::OnClosestNeighbor(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnected)
{
    FString ResponseJson = Response->GetContentAsString();

    UE_LOG(LogTemp, Warning, TEXT("%s"), *ResponseJson);

    TSharedPtr<FJsonObject> JsonObject;
    TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(ResponseJson);
    FJsonSerializer::Deserialize(Reader, JsonObject);
    auto Rows = JsonObject->GetArrayField("rows");

    for(auto Elem : Rows){
        FString Title = Elem->AsObject()->GetStringField("title");
        double Score = Elem->AsObject()->GetNumberField("score");
        UE_LOG(LogTemp, Warning, TEXT("%s, %f"), *Title, Score);
        Candidates.Add(TTuple<FString, double>(Title, Score));
    }
    Candidates.Sort([](TTuple<FString, double> a, TTuple<FString, double> b){
        return a.Value > b.Value;
    });
}