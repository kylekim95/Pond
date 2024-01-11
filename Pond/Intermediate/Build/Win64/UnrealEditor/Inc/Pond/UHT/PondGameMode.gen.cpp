// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Pond/PondGameMode.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodePondGameMode() {}
// Cross Module References
	ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
	POND_API UClass* Z_Construct_UClass_APondGameMode();
	POND_API UClass* Z_Construct_UClass_APondGameMode_NoRegister();
	UPackage* Z_Construct_UPackage__Script_Pond();
// End Cross Module References
	void APondGameMode::StaticRegisterNativesAPondGameMode()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(APondGameMode);
	UClass* Z_Construct_UClass_APondGameMode_NoRegister()
	{
		return APondGameMode::StaticClass();
	}
	struct Z_Construct_UClass_APondGameMode_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_APondGameMode_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AGameModeBase,
		(UObject* (*)())Z_Construct_UPackage__Script_Pond,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_APondGameMode_Statics::DependentSingletons) < 16);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_APondGameMode_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering HLOD WorldPartition DataLayers Transformation" },
		{ "IncludePath", "PondGameMode.h" },
		{ "ModuleRelativePath", "PondGameMode.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_APondGameMode_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<APondGameMode>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_APondGameMode_Statics::ClassParams = {
		&APondGameMode::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x008802ACu,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_APondGameMode_Statics::Class_MetaDataParams), Z_Construct_UClass_APondGameMode_Statics::Class_MetaDataParams)
	};
	UClass* Z_Construct_UClass_APondGameMode()
	{
		if (!Z_Registration_Info_UClass_APondGameMode.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_APondGameMode.OuterSingleton, Z_Construct_UClass_APondGameMode_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_APondGameMode.OuterSingleton;
	}
	template<> POND_API UClass* StaticClass<APondGameMode>()
	{
		return APondGameMode::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(APondGameMode);
	APondGameMode::~APondGameMode() {}
	struct Z_CompiledInDeferFile_FID_Pond_Source_Pond_PondGameMode_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Pond_Source_Pond_PondGameMode_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_APondGameMode, APondGameMode::StaticClass, TEXT("APondGameMode"), &Z_Registration_Info_UClass_APondGameMode, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(APondGameMode), 2008753486U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Pond_Source_Pond_PondGameMode_h_1913828932(TEXT("/Script/Pond"),
		Z_CompiledInDeferFile_FID_Pond_Source_Pond_PondGameMode_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Pond_Source_Pond_PondGameMode_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
