// Fill out your copyright notice in the Description page of Project Settings.


#include "WSS_UserTracker.h"
#include "JsonObjectConverter.h"
#include "Incident.h"

UWSS_UserTracker::UWSS_UserTracker()
{
	Http = &FHttpModule::Get();

	static ConstructorHelpers::FObjectFinder<UDataTable> IncidentsDTLoader(TEXT("/Script/Engine.DataTable'/Game/MyContent/DataTables/Incidents.Incidents'"));
    if(IncidentsDTLoader.Succeeded())
    {
        DT_Incidents = IncidentsDTLoader.Object;
    }
}

void UWSS_UserTracker::Initialize(FSubsystemCollectionBase &Collection)
{
    SendHttpGet("/get_incidents");

	ForGetRequest.BindLambda(
		[=, this](FString ResponseJson){
			TSharedPtr<FJsonObject> JsonObject;
			TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(ResponseJson);
			FJsonSerializer::Deserialize(Reader, JsonObject);
			auto Rows = JsonObject->GetArrayField("rows");
			for(auto Elem : Rows){
				FString Title = Elem->AsObject()->GetStringField("title");
				IncidentMap.Add(Title, nullptr);
			}
			for(auto Elem : DT_Incidents->GetRowMap()){
				if(IncidentMap.Contains(Elem.Key.ToString())){
					IncidentMap[Elem.Key.ToString()] = ((FIncidents_DataTable_Value*)Elem.Value)->IncidentClass;
				}
				else{
					FString Descriptor = ((FIncidents_DataTable_Value*)Elem.Value)->IncidentClass.GetDefaultObject()->Descriptor;
					SendHttpGet("/new_incident?title=" + Elem.Key.ToString() + "&descriptor=" + Descriptor);
					IncidentMap.Add(Elem.Key.ToString(), ((FIncidents_DataTable_Value*)Elem.Value)->IncidentClass);
				}
			}
			ForGetRequest.Unbind();
		}
	);

	UserState = { 0.0001f, 0.0001f, 0.0001f, 0.0001f, 0.0001f };
}

void UWSS_UserTracker::Deinitialize()
{

}

template<typename T>
void UWSS_UserTracker::SendHttpPost(FString Url, T& RequestBodyStruct)
{
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = Http->CreateRequest();
	Request->OnProcessRequestComplete().BindUObject(this, &UWSS_UserTracker::OnPostResponse);
	Request->SetURL(ServerBaseUrl + Url);
	Request->SetVerb("POST");

    Request->SetHeader("User-Agent", "X-UnrealEngine-Agent");
	Request->SetHeader("Content-Type", "application/json");
    Request->SetHeader("Accept", "application/json");

    FString JsonString;
    FJsonObjectConverter::UStructToJsonObjectString(RequestBodyStruct, JsonString);
    Request->SetContentAsString(JsonString);

	Request->ProcessRequest();
}

void UWSS_UserTracker::SendHttpGet(FString Url)
{
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = Http->CreateRequest();
	Request->OnProcessRequestComplete().BindUObject(this, &UWSS_UserTracker::OnGetResponse);
	Request->SetURL(ServerBaseUrl + Url);
	Request->SetVerb("Get");

    Request->SetHeader("User-Agent", "X-UnrealEngine-Agent");
	Request->SetHeader("Content-Type", "application/json");
    Request->SetHeader("Accept", "application/json");

    Request->ProcessRequest();
}

void UWSS_UserTracker::OnPostResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectSuccessfully)
{
	if(!bConnectSuccessfully){
		UE_LOG(LogTemp, Error, TEXT("Failed to connect to server"));
	} 
	else{
		if(Response.IsValid() && EHttpResponseCodes::IsOk(Response->GetResponseCode()))
		{
			if(ForPostRequest.IsBound())
				ForPostRequest.Execute(Response->GetContentAsString());
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Invalid response"));
		}
	}
}

void UWSS_UserTracker::OnGetResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectSuccessfully)
{
	if(!bConnectSuccessfully){
		UE_LOG(LogTemp, Error, TEXT("Failed to connect to server"));
	} 
	else{
		if(Response.IsValid() && EHttpResponseCodes::IsOk(Response->GetResponseCode()))
		{
			if(ForGetRequest.IsBound())
				ForGetRequest.Execute(Response->GetContentAsString());
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Invalid response"));
		}
	}
}

void UWSS_UserTracker::UpdateUserState(TArray<float> Target, TArray<float> Influence)
{
	for(int i = 0; i < UserState.Num(); i++)
		UserState[i] += (Target[i] * Influence[i]);
	
	FPostRequest_ClosestNeighbor_Incident Args;
	Args.user_state = UserState;
	SendHttpPost("/closest_neighbor", Args);

	ForPostRequest.BindLambda(
		[=, this](FString ResponseJson){
			TSharedPtr<FJsonObject> JsonObject;
			TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(ResponseJson);
			FJsonSerializer::Deserialize(Reader, JsonObject);
			auto Rows = JsonObject->GetArrayField("rows");
		
			TArray<TTuple<FString, double>> Candidates;
			for(auto Elem : Rows){
				FString Title = Elem->AsObject()->GetStringField("title");
				double Score = Elem->AsObject()->GetNumberField("score");
				Candidates.Add(TTuple<FString, double>(Title, Score));
			}
			Candidates.Sort([](TTuple<FString, double> a, TTuple<FString, double> b){
				return a.Value > b.Value;
			});
			//Candidates[0] -> Max Similarity

			ForPostRequest.Unbind();
		}
	);
}
