// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactable.h"

// Add default functionality here for any IInteractable functions that are not pure virtual.

void IInteractable::OnInteract(AActor * Interactor)
{
    if(InteractCondition(Interactor)){
        _OnInteract(Interactor);
    }
}