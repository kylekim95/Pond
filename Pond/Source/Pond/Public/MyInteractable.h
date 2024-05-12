// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MyInteractable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UMyInteractable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class POND_API IMyInteractable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	void OnInteract(AActor* Interactor);

protected:
	virtual void _OnInteract(AActor* Interactor) = 0;

};
