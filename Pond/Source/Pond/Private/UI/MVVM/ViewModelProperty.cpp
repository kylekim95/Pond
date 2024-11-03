#include "UI/MVVM/ViewModelProperty.h"

ViewModelPropertyBase::ViewModelPropertyBase(){

}

ViewModelPropertyBase::~ViewModelPropertyBase(){
    
}

FName ViewModelPropertyBase::GetName(){
    return Name;
}

void ViewModelPropertyBase::SetName(FName _Name){
    Name = _Name;
}
