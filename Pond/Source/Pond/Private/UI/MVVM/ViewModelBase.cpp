// Fill out your copyright notice in the Description page of Project Settings.
#include "UI/MVVM/ViewModelBase.h"
#include "UI/MVVM/ViewModelProperty.h"

UViewModelBase::UViewModelBase(){
    
}

void UViewModelBase::BroadcastChange(ViewModelPropertyBase* Property){
    FName PropertyName = Property->GetName();
    if(Delegates.Find(PropertyName) == nullptr) return;
    Delegates[PropertyName].Broadcast(Property);
}
