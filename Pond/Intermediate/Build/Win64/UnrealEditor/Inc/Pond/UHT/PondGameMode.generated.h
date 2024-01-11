// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "PondGameMode.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef POND_PondGameMode_generated_h
#error "PondGameMode.generated.h already included, missing '#pragma once' in PondGameMode.h"
#endif
#define POND_PondGameMode_generated_h

#define FID_Pond_Source_Pond_PondGameMode_h_12_SPARSE_DATA
#define FID_Pond_Source_Pond_PondGameMode_h_12_SPARSE_DATA_PROPERTY_ACCESSORS
#define FID_Pond_Source_Pond_PondGameMode_h_12_EDITOR_ONLY_SPARSE_DATA_PROPERTY_ACCESSORS
#define FID_Pond_Source_Pond_PondGameMode_h_12_RPC_WRAPPERS_NO_PURE_DECLS
#define FID_Pond_Source_Pond_PondGameMode_h_12_ACCESSORS
#define FID_Pond_Source_Pond_PondGameMode_h_12_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAPondGameMode(); \
	friend struct Z_Construct_UClass_APondGameMode_Statics; \
public: \
	DECLARE_CLASS(APondGameMode, AGameModeBase, COMPILED_IN_FLAGS(0 | CLASS_Transient | CLASS_Config), CASTCLASS_None, TEXT("/Script/Pond"), POND_API) \
	DECLARE_SERIALIZER(APondGameMode)


#define FID_Pond_Source_Pond_PondGameMode_h_12_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	POND_API APondGameMode(APondGameMode&&); \
	POND_API APondGameMode(const APondGameMode&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(POND_API, APondGameMode); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(APondGameMode); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(APondGameMode) \
	POND_API virtual ~APondGameMode();


#define FID_Pond_Source_Pond_PondGameMode_h_9_PROLOG
#define FID_Pond_Source_Pond_PondGameMode_h_12_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Pond_Source_Pond_PondGameMode_h_12_SPARSE_DATA \
	FID_Pond_Source_Pond_PondGameMode_h_12_SPARSE_DATA_PROPERTY_ACCESSORS \
	FID_Pond_Source_Pond_PondGameMode_h_12_EDITOR_ONLY_SPARSE_DATA_PROPERTY_ACCESSORS \
	FID_Pond_Source_Pond_PondGameMode_h_12_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Pond_Source_Pond_PondGameMode_h_12_ACCESSORS \
	FID_Pond_Source_Pond_PondGameMode_h_12_INCLASS_NO_PURE_DECLS \
	FID_Pond_Source_Pond_PondGameMode_h_12_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> POND_API UClass* StaticClass<class APondGameMode>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Pond_Source_Pond_PondGameMode_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
