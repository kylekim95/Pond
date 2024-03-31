// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Pond/Public/Subsystems/REGEvent.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeREGEvent() {}
// Cross Module References
	COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
	POND_API UClass* Z_Construct_UClass_UREGEvent();
	POND_API UClass* Z_Construct_UClass_UREGEvent_NoRegister();
	POND_API UScriptStruct* Z_Construct_UScriptStruct_FInfluence();
	UPackage* Z_Construct_UPackage__Script_Pond();
// End Cross Module References
	static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_Influence;
class UScriptStruct* FInfluence::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_Influence.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_Influence.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FInfluence, (UObject*)Z_Construct_UPackage__Script_Pond(), TEXT("Influence"));
	}
	return Z_Registration_Info_UScriptStruct_Influence.OuterSingleton;
}
template<> POND_API UScriptStruct* StaticStruct<FInfluence>()
{
	return FInfluence::StaticStruct();
}
	struct Z_Construct_UScriptStruct_FInfluence_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
		static const UECodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FInfluence_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "ModuleRelativePath", "Public/Subsystems/REGEvent.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FInfluence_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FInfluence>();
	}
	const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FInfluence_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_Pond,
		nullptr,
		&NewStructOps,
		"Influence",
		nullptr,
		0,
		sizeof(FInfluence),
		alignof(FInfluence),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FInfluence_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FInfluence_Statics::Struct_MetaDataParams)
	};
	UScriptStruct* Z_Construct_UScriptStruct_FInfluence()
	{
		if (!Z_Registration_Info_UScriptStruct_Influence.InnerSingleton)
		{
			UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_Influence.InnerSingleton, Z_Construct_UScriptStruct_FInfluence_Statics::ReturnStructParams);
		}
		return Z_Registration_Info_UScriptStruct_Influence.InnerSingleton;
	}
	void UREGEvent::StaticRegisterNativesUREGEvent()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UREGEvent);
	UClass* Z_Construct_UClass_UREGEvent_NoRegister()
	{
		return UREGEvent::StaticClass();
	}
	struct Z_Construct_UClass_UREGEvent_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UREGEvent_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UObject,
		(UObject* (*)())Z_Construct_UPackage__Script_Pond,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UREGEvent_Statics::DependentSingletons) < 16);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UREGEvent_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "Subsystems/REGEvent.h" },
		{ "ModuleRelativePath", "Public/Subsystems/REGEvent.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UREGEvent_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UREGEvent>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_UREGEvent_Statics::ClassParams = {
		&UREGEvent::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x001000A0u,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UREGEvent_Statics::Class_MetaDataParams), Z_Construct_UClass_UREGEvent_Statics::Class_MetaDataParams)
	};
	UClass* Z_Construct_UClass_UREGEvent()
	{
		if (!Z_Registration_Info_UClass_UREGEvent.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UREGEvent.OuterSingleton, Z_Construct_UClass_UREGEvent_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_UREGEvent.OuterSingleton;
	}
	template<> POND_API UClass* StaticClass<UREGEvent>()
	{
		return UREGEvent::StaticClass();
	}
	UREGEvent::UREGEvent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
	DEFINE_VTABLE_PTR_HELPER_CTOR(UREGEvent);
	UREGEvent::~UREGEvent() {}
	struct Z_CompiledInDeferFile_FID_Pond_Source_Pond_Public_Subsystems_REGEvent_h_Statics
	{
		static const FStructRegisterCompiledInInfo ScriptStructInfo[];
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FStructRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Pond_Source_Pond_Public_Subsystems_REGEvent_h_Statics::ScriptStructInfo[] = {
		{ FInfluence::StaticStruct, Z_Construct_UScriptStruct_FInfluence_Statics::NewStructOps, TEXT("Influence"), &Z_Registration_Info_UScriptStruct_Influence, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FInfluence), 3315357022U) },
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Pond_Source_Pond_Public_Subsystems_REGEvent_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_UREGEvent, UREGEvent::StaticClass, TEXT("UREGEvent"), &Z_Registration_Info_UClass_UREGEvent, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UREGEvent), 4128137868U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Pond_Source_Pond_Public_Subsystems_REGEvent_h_1397798268(TEXT("/Script/Pond"),
		Z_CompiledInDeferFile_FID_Pond_Source_Pond_Public_Subsystems_REGEvent_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Pond_Source_Pond_Public_Subsystems_REGEvent_h_Statics::ClassInfo),
		Z_CompiledInDeferFile_FID_Pond_Source_Pond_Public_Subsystems_REGEvent_h_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Pond_Source_Pond_Public_Subsystems_REGEvent_h_Statics::ScriptStructInfo),
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
