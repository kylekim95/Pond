// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Pond/Public/Subsystems/WSS_RandomEventGenerator.h"
#include "Pond/Public/Subsystems/REGEvent.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeWSS_RandomEventGenerator() {}
// Cross Module References
	ENGINE_API UClass* Z_Construct_UClass_UWorldSubsystem();
	POND_API UClass* Z_Construct_UClass_UREGEvent_NoRegister();
	POND_API UClass* Z_Construct_UClass_UWSS_RandomEventGenerator();
	POND_API UClass* Z_Construct_UClass_UWSS_RandomEventGenerator_NoRegister();
	POND_API UScriptStruct* Z_Construct_UScriptStruct_FInfluence();
	UPackage* Z_Construct_UPackage__Script_Pond();
// End Cross Module References
	DEFINE_FUNCTION(UWSS_RandomEventGenerator::execAddEvent)
	{
		P_GET_OBJECT(UREGEvent,Z_Param_NewEvent);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->AddEvent(Z_Param_NewEvent);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UWSS_RandomEventGenerator::execNotify)
	{
		P_GET_TARRAY(FInfluence,Z_Param_Incidents);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->Notify(Z_Param_Incidents);
		P_NATIVE_END;
	}
	void UWSS_RandomEventGenerator::StaticRegisterNativesUWSS_RandomEventGenerator()
	{
		UClass* Class = UWSS_RandomEventGenerator::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "AddEvent", &UWSS_RandomEventGenerator::execAddEvent },
			{ "Notify", &UWSS_RandomEventGenerator::execNotify },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_UWSS_RandomEventGenerator_AddEvent_Statics
	{
		struct WSS_RandomEventGenerator_eventAddEvent_Parms
		{
			UREGEvent* NewEvent;
		};
		static const UECodeGen_Private::FObjectPropertyParams NewProp_NewEvent;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UWSS_RandomEventGenerator_AddEvent_Statics::NewProp_NewEvent = { "NewEvent", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(WSS_RandomEventGenerator_eventAddEvent_Parms, NewEvent), Z_Construct_UClass_UREGEvent_NoRegister, METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UWSS_RandomEventGenerator_AddEvent_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UWSS_RandomEventGenerator_AddEvent_Statics::NewProp_NewEvent,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UWSS_RandomEventGenerator_AddEvent_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/Subsystems/WSS_RandomEventGenerator.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UWSS_RandomEventGenerator_AddEvent_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UWSS_RandomEventGenerator, nullptr, "AddEvent", nullptr, nullptr, Z_Construct_UFunction_UWSS_RandomEventGenerator_AddEvent_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UWSS_RandomEventGenerator_AddEvent_Statics::PropPointers), sizeof(Z_Construct_UFunction_UWSS_RandomEventGenerator_AddEvent_Statics::WSS_RandomEventGenerator_eventAddEvent_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UWSS_RandomEventGenerator_AddEvent_Statics::Function_MetaDataParams), Z_Construct_UFunction_UWSS_RandomEventGenerator_AddEvent_Statics::Function_MetaDataParams) };
	static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UWSS_RandomEventGenerator_AddEvent_Statics::PropPointers) < 2048);
	static_assert(sizeof(Z_Construct_UFunction_UWSS_RandomEventGenerator_AddEvent_Statics::WSS_RandomEventGenerator_eventAddEvent_Parms) < MAX_uint16);
	UFunction* Z_Construct_UFunction_UWSS_RandomEventGenerator_AddEvent()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UWSS_RandomEventGenerator_AddEvent_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UWSS_RandomEventGenerator_Notify_Statics
	{
		struct WSS_RandomEventGenerator_eventNotify_Parms
		{
			TArray<FInfluence> Incidents;
		};
		static const UECodeGen_Private::FStructPropertyParams NewProp_Incidents_Inner;
		static const UECodeGen_Private::FArrayPropertyParams NewProp_Incidents;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UWSS_RandomEventGenerator_Notify_Statics::NewProp_Incidents_Inner = { "Incidents", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FInfluence, METADATA_PARAMS(0, nullptr) }; // 3315357022
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UWSS_RandomEventGenerator_Notify_Statics::NewProp_Incidents = { "Incidents", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(WSS_RandomEventGenerator_eventNotify_Parms, Incidents), EArrayPropertyFlags::None, METADATA_PARAMS(0, nullptr) }; // 3315357022
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UWSS_RandomEventGenerator_Notify_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UWSS_RandomEventGenerator_Notify_Statics::NewProp_Incidents_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UWSS_RandomEventGenerator_Notify_Statics::NewProp_Incidents,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UWSS_RandomEventGenerator_Notify_Statics::Function_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "//Gives the subsystem information used to determine which events should be invoked\n" },
#endif
		{ "ModuleRelativePath", "Public/Subsystems/WSS_RandomEventGenerator.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Gives the subsystem information used to determine which events should be invoked" },
#endif
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UWSS_RandomEventGenerator_Notify_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UWSS_RandomEventGenerator, nullptr, "Notify", nullptr, nullptr, Z_Construct_UFunction_UWSS_RandomEventGenerator_Notify_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UWSS_RandomEventGenerator_Notify_Statics::PropPointers), sizeof(Z_Construct_UFunction_UWSS_RandomEventGenerator_Notify_Statics::WSS_RandomEventGenerator_eventNotify_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UWSS_RandomEventGenerator_Notify_Statics::Function_MetaDataParams), Z_Construct_UFunction_UWSS_RandomEventGenerator_Notify_Statics::Function_MetaDataParams) };
	static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UWSS_RandomEventGenerator_Notify_Statics::PropPointers) < 2048);
	static_assert(sizeof(Z_Construct_UFunction_UWSS_RandomEventGenerator_Notify_Statics::WSS_RandomEventGenerator_eventNotify_Parms) < MAX_uint16);
	UFunction* Z_Construct_UFunction_UWSS_RandomEventGenerator_Notify()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UWSS_RandomEventGenerator_Notify_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UWSS_RandomEventGenerator);
	UClass* Z_Construct_UClass_UWSS_RandomEventGenerator_NoRegister()
	{
		return UWSS_RandomEventGenerator::StaticClass();
	}
	struct Z_Construct_UClass_UWSS_RandomEventGenerator_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UWSS_RandomEventGenerator_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UWorldSubsystem,
		(UObject* (*)())Z_Construct_UPackage__Script_Pond,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UWSS_RandomEventGenerator_Statics::DependentSingletons) < 16);
	const FClassFunctionLinkInfo Z_Construct_UClass_UWSS_RandomEventGenerator_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_UWSS_RandomEventGenerator_AddEvent, "AddEvent" }, // 1624816981
		{ &Z_Construct_UFunction_UWSS_RandomEventGenerator_Notify, "Notify" }, // 2035881633
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UWSS_RandomEventGenerator_Statics::FuncInfo) < 2048);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UWSS_RandomEventGenerator_Statics::Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "IncludePath", "Subsystems/WSS_RandomEventGenerator.h" },
		{ "ModuleRelativePath", "Public/Subsystems/WSS_RandomEventGenerator.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UWSS_RandomEventGenerator_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UWSS_RandomEventGenerator>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_UWSS_RandomEventGenerator_Statics::ClassParams = {
		&UWSS_RandomEventGenerator::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		0,
		0,
		0x001000A0u,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UWSS_RandomEventGenerator_Statics::Class_MetaDataParams), Z_Construct_UClass_UWSS_RandomEventGenerator_Statics::Class_MetaDataParams)
	};
	UClass* Z_Construct_UClass_UWSS_RandomEventGenerator()
	{
		if (!Z_Registration_Info_UClass_UWSS_RandomEventGenerator.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UWSS_RandomEventGenerator.OuterSingleton, Z_Construct_UClass_UWSS_RandomEventGenerator_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_UWSS_RandomEventGenerator.OuterSingleton;
	}
	template<> POND_API UClass* StaticClass<UWSS_RandomEventGenerator>()
	{
		return UWSS_RandomEventGenerator::StaticClass();
	}
	UWSS_RandomEventGenerator::UWSS_RandomEventGenerator() {}
	DEFINE_VTABLE_PTR_HELPER_CTOR(UWSS_RandomEventGenerator);
	UWSS_RandomEventGenerator::~UWSS_RandomEventGenerator() {}
	struct Z_CompiledInDeferFile_FID_Pond_Source_Pond_Public_Subsystems_WSS_RandomEventGenerator_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Pond_Source_Pond_Public_Subsystems_WSS_RandomEventGenerator_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_UWSS_RandomEventGenerator, UWSS_RandomEventGenerator::StaticClass, TEXT("UWSS_RandomEventGenerator"), &Z_Registration_Info_UClass_UWSS_RandomEventGenerator, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UWSS_RandomEventGenerator), 135374620U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Pond_Source_Pond_Public_Subsystems_WSS_RandomEventGenerator_h_2996076787(TEXT("/Script/Pond"),
		Z_CompiledInDeferFile_FID_Pond_Source_Pond_Public_Subsystems_WSS_RandomEventGenerator_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Pond_Source_Pond_Public_Subsystems_WSS_RandomEventGenerator_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
