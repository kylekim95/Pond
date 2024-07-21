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

void UWS_Network::Get(
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
void UWS_Network::Post(
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
