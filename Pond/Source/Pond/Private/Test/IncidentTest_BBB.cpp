// Fill out your copyright notice in the Description page of Project Settings.


#include "Test/IncidentTest_BBB.h"
#include "MyTestInteractableComponent.h"

AIncidentTest_BBB::AIncidentTest_BBB()
{
    Title = "BBB";
    Descriptor = "birds%20singing";

    StaticMesh = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'")).Object;

    StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
    StaticMeshComponent->SetStaticMesh(StaticMesh);

    InteractableComponent = CreateDefaultSubobject<UMyTestInteractableComponent>(TEXT("InteractableComponent"));
}