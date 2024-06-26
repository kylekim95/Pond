// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "http.h"
#include "WS_Network.generated.h"

/**
 * 
 */

UCLASS()
class POND_API UWS_Network : public UWorldSubsystem
{
	GENERATED_BODY()
	
public:
	UWS_Network();
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	template<typename T>
	void SendHttpPost(
		FString Url,
		T& RequestBodyStruct,
		FHttpRequestCompleteDelegate& Callback
	);
	void SendHttpGet(
		FString Url,
		FHttpRequestCompleteDelegate& Callback
	);

private:
	FHttpModule* Http;
	const FString ServerBaseUrl = "http://localhost:8080";
};
