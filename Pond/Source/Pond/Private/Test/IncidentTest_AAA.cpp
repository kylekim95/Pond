// Fill out your copyright notice in the Description page of Project Settings.


#include "Test/IncidentTest_AAA.h"
#include "MyTestInteractableComponent.h"

AIncidentTest_AAA::AIncidentTest_AAA()
{
    Title = "AAA";
    Descriptor = "cthulhu";

    StaticMesh = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'")).Object;

    StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
    StaticMeshComponent->SetStaticMesh(StaticMesh);

    InteractableComponent = CreateDefaultSubobject<UMyTestInteractableComponent>(TEXT("InteractableComponent"));
}