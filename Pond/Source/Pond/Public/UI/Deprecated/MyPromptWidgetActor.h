// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyPromptWidgetActor.generated.h"

class UUserWidget;
class UWidgetComponent;
class UWidgetAnimation;

UCLASS()
class POND_API AMyPromptWidgetActor : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	AMyPromptWidgetActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UWidgetComponent* PromptWidgetComponent;

public:
	void ChangeWidgetClass(TSubclassOf<class UUserWidget> NewWidgetClass);
	void PlayAnimationByName(FName AnimName);
};
