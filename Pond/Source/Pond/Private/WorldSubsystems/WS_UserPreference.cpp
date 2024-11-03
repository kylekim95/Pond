// Fill out your copyright notice in the Description page of Project Settings.
#include "WorldSubsystems/WS_UserPreference.h"

UWS_UserPreference::UWS_UserPreference()
{
    
}

void UWS_UserPreference::Initialize(FSubsystemCollectionBase &Collection)
{
    Super::Initialize(Collection);

    // Elements of UserState is the cosine distance {fear, sadness, joy, disgust, anger}
    // 2[Inverse] -> 1[No Relevance] -> 0[Strong Relevance]
    UserPreferenceVector = { 0.001f, 0.001f, 0.001f, 0.001f, 0.001f };
    PrevUserPreferenceVector = UserPreferenceVector;

    OnPreferredIncidentsDelegate.BindUObject(this, &UWS_UserPreference::OnPreferredIncidents);
}

void UWS_UserPreference::Deinitialize()
{
    Super::Deinitialize();
}

void UWS_UserPreference::PostInitialize()
{
    Super::PostInitialize();

    WS_Network = GetWorld()->GetSubsystem<UWS_Network>();
}

void UWS_UserPreference::OnWorldBeginPlay(UWorld& InWorld)
{
    Super::OnWorldBeginPlay(InWorld);

    FPreferredIncidents _PreferredIncidents;
    _PreferredIncidents.user_state = UserPreferenceVector;
    WS_Network->Post("/preferred_incidents", OnPreferredIncidentsDelegate, _PreferredIncidents);
}

void UWS_UserPreference::UpdateUserPreferenceVector(TArray<float> Influence, TArray<float> Strength)
{
    if(Influence.Num() != UserPreferenceVector.Num() && Strength.Num() != UserPreferenceVector.Num()){
        UE_LOG(LogTemp, Error, TEXT("UpdateUserState: Invalid Target/Influence vector input"));
        return;
    }
    //Target is Similarity therefore 1 - Similarity = Cosine difference
    for(int i = 0; i < UserPreferenceVector.Num(); i++){
        UserPreferenceVector[i] = FMath::Lerp(UserPreferenceVector[i], 1 - Influence[i], Strength[i]);
    }
    float Sum = 0;
    TArray<float> Diff({0.0f,0.0f,0.0f,0.0f,0.0f});
    for(int i = 0; i < UserPreferenceVector.Num(); i++){
        Diff[i] = UserPreferenceVector[i] - PrevUserPreferenceVector[i];
        Sum += Diff[i];
    }
    if(Sum >= Threshold){
        FPreferredIncidents _PreferredIncidents;
        _PreferredIncidents.user_state = UserPreferenceVector;
        WS_Network->Post("/preferred_incidents", OnPreferredIncidentsDelegate, _PreferredIncidents);
        PrevUserPreferenceVector = UserPreferenceVector;
    }
}

void UWS_UserPreference::OnPreferredIncidents(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnected)
{
    FString ResponseJson = Response->GetContentAsString();
    TSharedPtr<FJsonObject> JsonObject;
    TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(ResponseJson);
    FJsonSerializer::Deserialize(Reader, JsonObject);
    auto Rows = JsonObject->GetArrayField("rows");
    for(auto Row : Rows){
        FString Name = Row->AsObject()->GetStringField("name");
        double Similarity = Row->AsObject()->GetNumberField("similarity");

        PreferredIncidents.Add(Name);
    }
}