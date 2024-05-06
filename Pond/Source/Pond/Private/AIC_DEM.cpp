// Fill out your copyright notice in the Description page of Project Settings.


#include "AIC_DEM.h"
#include "BehaviorTree/BehaviorTree.h"

void AAIC_DEM::BeginPlay()
{
    if(BT_DEM != nullptr)
    {
        RunBehaviorTree(BT_DEM);
    }
}

// void AAIC_DEM::HelloWorld()
// {
//     UE_LOG(LogTemp, Warning, TEXT("Hello World!"));
// }