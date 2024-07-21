// Fill out your copyright notice in the Description page of Project Settings.
#include "EditorSubsystems/ES_SynchronizeIncident.h"
#include "WorldSubsystems/WS_UserPreference.h"
#include "JsonObjectConverter.h"

UES_SynchronizeIncident::UES_SynchronizeIncident()
{
    static ConstructorHelpers::FObjectFinder<UDataTable> DT_Incidents_Type_Loader(TEXT("/Script/Engine.DataTable'/Game/MyContent/DataTables/Incidents_Type.Incidents_Type'"));
    if(DT_Incidents_Type_Loader.Succeeded()){
        DT_Incidents_Type = DT_Incidents_Type_Loader.Object;
    }

    Http = &FHttpModule::Get();
}

void UES_SynchronizeIncident::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);

    //Read DataTable
    TArray<FIncident_Type*> Rows;
    DT_Incidents_Type->GetAllRows(TEXT("ES_SynchronizeIncident: Incidents_Type: GetAllRows"), Rows);
    TArray<FName> RowNames = DT_Incidents_Type->GetRowNames();
    for(int i = 0; i < Rows.Num(); i++){
        IncidentDescriptions.Add(RowNames[i].ToString(), Rows[i]->Description);
    }

    OnGetIncidentsDelegate.BindUObject(this, &UES_SynchronizeIncident::OnGetIncidents);
    OnAddIncidentDelegate.BindUObject(this, &UES_SynchronizeIncident::OnAddIncident);

    Get("/get_incidents", OnGetIncidentsDelegate);
}

void UES_SynchronizeIncident::Deinitialize()
{
    Super::Deinitialize();

    OnGetIncidentsDelegate.BindUObject(this, &UES_SynchronizeIncident::OnGetIncidents);
}

void UES_SynchronizeIncident::OnGetIncidents(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnected)
{
    TArray<FString> DBIncidentList;

    FString ResponseJson = Response->GetContentAsString();
    TSharedPtr<FJsonObject> JsonObject;
    TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(ResponseJson);
    FJsonSerializer::Deserialize(Reader, JsonObject);
    for(auto Elem : JsonObject->GetArrayField("rows")){
        FString Name = Elem->AsObject()->GetStringField("name");
        DBIncidentList.Add(Name);
    }

    for(auto Description : IncidentDescriptions){
        if(DBIncidentList.Find(Description.Key) == INDEX_NONE){
            FAddIncident AddIncident;
            AddIncident.Name = Description.Key;
            AddIncident.Description = Description.Value;
            Post("/add_incident", OnAddIncidentDelegate, AddIncident);
        }
    }
}

void UES_SynchronizeIncident::OnAddIncident(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnected)
{
    //Do nothing
}

void UES_SynchronizeIncident::Get(
    FString Url,
    FHttpRequestCompleteDelegate& Callback
)
{
    TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = Http->CreateRequest();
    Request->OnProcessRequestComplete().BindLambda(
        [=, this](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnected){
            if(!bConnected){
                //Failed to connect to server
            }
            else{
                if(Response.IsValid() && EHttpResponseCodes::IsOk(Response->GetResponseCode())){
                    if(Callback.IsBound())
                        Callback.Execute(Request, Response, bConnected);
                }
                else{
                    //Invalid response from server
                }
            }
        }
    );
    Request->SetURL(BaseUrl + Url);
    Request->SetVerb("GET");
    
    Request->SetHeader("User-Agent", "X-UnrealEngine-Agent");
    Request->SetHeader("Content-Type", "application/json");
    Request->SetHeader("Accept", "application/json");

    Request->ProcessRequest();
}

template <typename T>
void UES_SynchronizeIncident::Post(
    FString Url,
    FHttpRequestCompleteDelegate &Callback, 
    T &RequestContent
)
{
    TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = Http->CreateRequest();
    Request->OnProcessRequestComplete().BindLambda(
        [=, this](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnected){
            if(!bConnected){
                //Failed to connect to server
            }
            else{
                if(Response.IsValid() && EHttpResponseCodes::IsOk(Response->GetResponseCode())){
                    if(Callback.IsBound())
                        Callback.Execute(Request, Response, bConnected);
                }
                else{
                    //Invalid response from server
                }
            }
        }
    );
    Request->SetURL(BaseUrl + Url);
    Request->SetVerb("POST");
    
    Request->SetHeader("User-Agent", "X-UnrealEngine-Agent");
    Request->SetHeader("Content-Type", "application/json");
    Request->SetHeader("Accept", "application/json");

    FString JsonString;
    FJsonObjectConverter::UStructToJsonObjectString(RequestContent, JsonString);
    Request->SetContentAsString(JsonString);

    Request->ProcessRequest();
}
