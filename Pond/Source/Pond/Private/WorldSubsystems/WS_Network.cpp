// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldSubsystems/WS_Network.h"
#include "JsonObjectConverter.h"

UWS_Network::UWS_Network()
{
    Http = &FHttpModule::Get();
}

void UWS_Network::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);
}

void UWS_Network::Deinitialize()
{
    Super::Deinitialize();
}

template<typename T>
void UWS_Network::SendHttpPost(
    FString Url,
    T& RequestBodyStruct,
    FHttpRequestCompleteDelegate& Callback
)
{
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = Http->CreateRequest();
	Request->OnProcessRequestComplete().BindLambda(
        [=, this](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnected){
            if(!bConnected){
                UE_LOG(LogTemp, Error, TEXT("Failed to connect to server"));
            } 
            else{
                if(Response.IsValid() && EHttpResponseCodes::IsOk(Response->GetResponseCode()))
                {
                    if(Callback.IsBound())
                        Callback.Execute(Request, Response, bConnected);
                }
                else
                {
                    UE_LOG(LogTemp, Error, TEXT("Invalid response"));
                }
            }
        }
    );
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

void UWS_Network::SendHttpGet(
    FString Url,
    FHttpRequestCompleteDelegate& Callback
)
{
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = Http->CreateRequest();
	Request->OnProcessRequestComplete().BindLambda(
        [=, this](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnected){
            if(!bConnected){
                UE_LOG(LogTemp, Error, TEXT("Failed to connect to server"));
            } 
            else{
                if(Response.IsValid() && EHttpResponseCodes::IsOk(Response->GetResponseCode()))
                {
                    if(Callback.IsBound())
                        Callback.Execute(Request, Response, bConnected);
                }
                else
                {
                    UE_LOG(LogTemp, Error, TEXT("Invalid response"));
                }
            }
        }
    );
	Request->SetURL(ServerBaseUrl + Url);
	Request->SetVerb("GET");

    Request->SetHeader("User-Agent", "X-UnrealEngine-Agent");
	Request->SetHeader("Content-Type", "application/json");
    Request->SetHeader("Accept", "application/json");

    Request->ProcessRequest();
}