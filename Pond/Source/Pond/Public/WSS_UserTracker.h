// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "http.h"
#include "WSS_UserTracker.generated.h"

DECLARE_DELEGATE_OneParam(FHandleResponse, FString ResponseJson)

/**
 * 
 */

class AIncident;

UCLASS()
class POND_API UWSS_UserTracker : public UWorldSubsystem
{
	GENERATED_BODY()
	
	TArray<float> UserState;
	TMap<FString, TSubclassOf<AIncident>> IncidentMap;
	UPROPERTY(EditAnywhere)
	class UDataTable* DT_Incidents;

public:
	UWSS_UserTracker();
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	void UpdateUserState(TArray<float> Target, TArray<float> Influence);

protected:
	template<typename T>
	void SendHttpPost(FString Url, T& RequestBodyStruct);
	void SendHttpGet(FString Url);

private:
	FHttpModule* Http;
	const FString ServerBaseUrl = "http://localhost:8080";
	void OnGetResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectSuccessfully);
	void OnPostResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectSuccessfully);
	FHandleResponse ForGetRequest;
	FHandleResponse ForPostRequest;
};

USTRUCT(BlueprintType)
struct FPostRequest_ClosestNeighbor_Incident
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<float> user_state;
};

USTRUCT(BlueprintType)
struct FIncidents_DataTable_Value
{
	GENERATED_BODY()

	UPROPERTY()
	TSubclassOf<AIncident> IncidentClass;
};