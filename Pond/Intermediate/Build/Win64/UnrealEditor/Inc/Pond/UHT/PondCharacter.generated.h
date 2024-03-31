// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "PondCharacter.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef POND_PondCharacter_generated_h
#error "PondCharacter.generated.h already included, missing '#pragma once' in PondCharacter.h"
#endif
#define POND_PondCharacter_generated_h

#define FID_Pond_Source_Pond_PondCharacter_h_22_SPARSE_DATA
#define FID_Pond_Source_Pond_PondCharacter_h_22_SPARSE_DATA_PROPERTY_ACCESSORS
#define FID_Pond_Source_Pond_PondCharacter_h_22_EDITOR_ONLY_SPARSE_DATA_PROPERTY_ACCESSORS
#define FID_Pond_Source_Pond_PondCharacter_h_22_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execGetHasRifle); \
	DECLARE_FUNCTION(execSetHasRifle);


#define FID_Pond_Source_Pond_PondCharacter_h_22_ACCESSORS
#define FID_Pond_Source_Pond_PondCharacter_h_22_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAPondCharacter(); \
	friend struct Z_Construct_UClass_APondCharacter_Statics; \
public: \
	DECLARE_CLASS(APondCharacter, ACharacter, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/Pond"), NO_API) \
	DECLARE_SERIALIZER(APondCharacter)


#define FID_Pond_Source_Pond_PondCharacter_h_22_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API APondCharacter(APondCharacter&&); \
	NO_API APondCharacter(const APondCharacter&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, APondCharacter); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(APondCharacter); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(APondCharacter) \
	NO_API virtual ~APondCharacter();


#define FID_Pond_Source_Pond_PondCharacter_h_19_PROLOG
#define FID_Pond_Source_Pond_PondCharacter_h_22_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Pond_Source_Pond_PondCharacter_h_22_SPARSE_DATA \
	FID_Pond_Source_Pond_PondCharacter_h_22_SPARSE_DATA_PROPERTY_ACCESSORS \
	FID_Pond_Source_Pond_PondCharacter_h_22_EDITOR_ONLY_SPARSE_DATA_PROPERTY_ACCESSORS \
	FID_Pond_Source_Pond_PondCharacter_h_22_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Pond_Source_Pond_PondCharacter_h_22_ACCESSORS \
	FID_Pond_Source_Pond_PondCharacter_h_22_INCLASS_NO_PURE_DECLS \
	FID_Pond_Source_Pond_PondCharacter_h_22_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> POND_API UClass* StaticClass<class APondCharacter>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Pond_Source_Pond_PondCharacter_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
