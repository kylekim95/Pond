// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Deprecated/MyPromptWidgetActor.h"
#include "Components/WidgetComponent.h"
#include "Animation/WidgetAnimation.h"
#include "MovieScene.h"
#include "UI/Deprecated/AnimWidget.h"

// Sets default values
AMyPromptWidgetActor::AMyPromptWidgetActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PromptWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("PromptWidgetComponent"));
	PromptWidgetComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	PromptWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
}

// Called when the game starts or when spawned
void AMyPromptWidgetActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMyPromptWidgetActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMyPromptWidgetActor::ChangeWidgetClass(TSubclassOf<class UUserWidget> NewWidgetClass)
{
	PromptWidgetComponent->SetWidgetClass(NewWidgetClass);
}

void AMyPromptWidgetActor::PlayAnimationByName(FName AnimName)
{
	IAnimWidget* Temp = Cast<IAnimWidget>(PromptWidgetComponent->GetWidget());
	if(Temp)
		Temp->PlayAnimationByName(AnimName);
}