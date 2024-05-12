// Fill out your copyright notice in the Description page of Project Settings.


#include "MyInteractable.h"

// Add default functionality here for any IMyInteractable functions that are not pure virtual.

void IMyInteractable::OnInteract(AActor* Interactor)
{
    _OnInteract(Interactor);
}