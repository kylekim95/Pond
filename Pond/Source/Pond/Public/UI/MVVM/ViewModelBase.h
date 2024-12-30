// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UI/MVVM/ViewModelProperty.h"
#include "ViewModelBase.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FViewModelPropertyChanged, ViewModelPropertyBase*)

#define PROPERTY(TypeName, VarName) \
private: \
	ViewModelProperty<TypeName> VarName; \
	FViewModelPropertyChanged VarName##Changed; \
public: \
	TypeName Get##VarName(){  \
		return VarName.Get(); \
	} \
	void Set##VarName(TypeName NewValue){ \
		VarName.Set(NewValue); \
		BroadcastChange(&VarName); \
	}

#define INIT(VarName) \
	VarName.SetName(#VarName); \
	Delegates.Add({#VarName, VarName##Changed}); \

UCLASS()
class POND_API UViewModelBase : public UObject
{
	GENERATED_BODY()

public:
	UViewModelBase();
	TMap<FName, FViewModelPropertyChanged> Delegates;
protected:
	void BroadcastChange(ViewModelPropertyBase* Property);
};
