// Fill out your copyright notice in the Description page of Project Settings.


#include "EditorUtility/EUW_IncidentsSpawnableLocation.h"

UEUW_IncidentsSpawnableLocation::UEUW_IncidentsSpawnableLocation()
{
    static ConstructorHelpers::FObjectFinder<UDataTable> IncidentsSpawnLocationDataTableLoader(TEXT(""));
    if(IncidentsSpawnLocationDataTableLoader.Succeeded()){
        IncidentsSpawnLocationDataTable = IncidentsSpawnLocationDataTableLoader.Object;
    }
}