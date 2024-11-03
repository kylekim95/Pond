#pragma once

#include "CoreMinimal.h"

class ViewModelPropertyBase
{
public:
	ViewModelPropertyBase();
	virtual ~ViewModelPropertyBase();
	FName GetName();
	void SetName(FName _Name);
private:
	FName Name;
};

template<typename T>
class ViewModelProperty : public ViewModelPropertyBase
{
public:
	ViewModelProperty();
	~ViewModelProperty();
	T Get(){ return Value; };
	void Set(T NewValue){ Value = NewValue; }
private:
	T Value;
};
template<typename T>
ViewModelProperty<T>::ViewModelProperty()
{

}
template<typename T>
ViewModelProperty<T>::~ViewModelProperty(){

}