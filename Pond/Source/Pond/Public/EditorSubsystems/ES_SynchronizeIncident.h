// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "EditorSubsystem.h"
#include "http.h"
#include "ES_SynchronizeIncident.generated.h"

UCLASS()
class POND_API UES_SynchronizeIncident : public UEditorSubsystem
{
	GENERATED_BODY()

public:
	UES_SynchronizeIncident();
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

private:
	UDataTable* DT_Incidents_Type;
	TMap<FString, FString> IncidentDescriptions;
	
	FHttpModule* Http;
	const FString BaseUrl = "http://localhost:8080";
	
	FHttpRequestCompleteDelegate OnGetIncidentsDelegate;
	void OnGetIncidents(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnected);
	FHttpRequestCompleteDelegate OnAddIncidentDelegate;
	void OnAddIncident(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnected);

	void Get(
		FString Url,
		FHttpRequestCompleteDelegate& Callback
	);
	template <typename T>
	void Post(
		FString Url,
		FHttpRequestCompleteDelegate& Callback,
		T& RequestBody
	);
};

USTRUCT(BlueprintType)
struct FAddIncident
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FString Name;
	UPROPERTY(EditAnywhere)
	FString Description;
};