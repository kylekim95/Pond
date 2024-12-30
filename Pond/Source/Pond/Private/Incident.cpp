// Fill out your copyright notice in the Description page of Project Settings.
#include "Incident.h"

// Sets default values
AIncident::AIncident()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}
// Called when the game starts or when spawned
void AIncident::BeginPlay()
{
	Super::BeginPlay();

	if(ActionSequence == nullptr){
		ActionSequence = new TQueue<FActionDelegate>();
	}
}
// Called every frame
void AIncident::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(bCont && !(ActionSequence->IsEmpty())){
		if(Promise){
			delete Promise;
			Promise = nullptr;
		}
		Promise = new TPromise<TResult<int>>();
		Promise->GetFuture().Next([&bCont = bCont](TResult<int> Result){
			bCont = true;
		});
		
		bCont = false;
		
		FActionDelegate NextAction;
		FString Params;
		ActionSequence->Dequeue(NextAction);
		ActionParams.Dequeue(Params);
		NextAction.ExecuteIfBound(Params);
	}
}

void AIncident::EnqueueAction(FActionDelegate ActionDelegate, FString Params)
{
	if(ActionSequence == nullptr){
		ActionSequence = new TQueue<FActionDelegate>();
	}
	ActionSequence->Enqueue(ActionDelegate);
	ActionParams.Enqueue(Params);
}
void AIncident::SetPromiseValue(ETerminationType TerminationType, int Value)
{
	Promise->SetValue(TResult<int>{TerminationType, Value});
}
