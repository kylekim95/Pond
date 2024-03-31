// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "SkippingStones.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class AActor;
class UPrimitiveComponent;
struct FHitResult;
struct FThrowDesc;
#ifdef POND_SkippingStones_generated_h
#error "SkippingStones.generated.h already included, missing '#pragma once' in SkippingStones.h"
#endif
#define POND_SkippingStones_generated_h

#define FID_Pond_Source_Pond_Public_SkippingStones_h_12_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FThrowDesc_Statics; \
	POND_API static class UScriptStruct* StaticStruct();


template<> POND_API UScriptStruct* StaticStruct<struct FThrowDesc>();

#define FID_Pond_Source_Pond_Public_SkippingStones_h_36_SPARSE_DATA
#define FID_Pond_Source_Pond_Public_SkippingStones_h_36_SPARSE_DATA_PROPERTY_ACCESSORS
#define FID_Pond_Source_Pond_Public_SkippingStones_h_36_EDITOR_ONLY_SPARSE_DATA_PROPERTY_ACCESSORS
#define FID_Pond_Source_Pond_Public_SkippingStones_h_36_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execThrow); \
	DECLARE_FUNCTION(execOnHitComponent); \
	DECLARE_FUNCTION(execOnOverlapEnd); \
	DECLARE_FUNCTION(execOnOverlapBegin);


#define FID_Pond_Source_Pond_Public_SkippingStones_h_36_ACCESSORS
#define FID_Pond_Source_Pond_Public_SkippingStones_h_36_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUSkippingStones(); \
	friend struct Z_Construct_UClass_USkippingStones_Statics; \
public: \
	DECLARE_CLASS(USkippingStones, UActorComponent, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/Pond"), NO_API) \
	DECLARE_SERIALIZER(USkippingStones)


#define FID_Pond_Source_Pond_Public_SkippingStones_h_36_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API USkippingStones(USkippingStones&&); \
	NO_API USkippingStones(const USkippingStones&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, USkippingStones); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(USkippingStones); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(USkippingStones) \
	NO_API virtual ~USkippingStones();


#define FID_Pond_Source_Pond_Public_SkippingStones_h_33_PROLOG
#define FID_Pond_Source_Pond_Public_SkippingStones_h_36_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Pond_Source_Pond_Public_SkippingStones_h_36_SPARSE_DATA \
	FID_Pond_Source_Pond_Public_SkippingStones_h_36_SPARSE_DATA_PROPERTY_ACCESSORS \
	FID_Pond_Source_Pond_Public_SkippingStones_h_36_EDITOR_ONLY_SPARSE_DATA_PROPERTY_ACCESSORS \
	FID_Pond_Source_Pond_Public_SkippingStones_h_36_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Pond_Source_Pond_Public_SkippingStones_h_36_ACCESSORS \
	FID_Pond_Source_Pond_Public_SkippingStones_h_36_INCLASS_NO_PURE_DECLS \
	FID_Pond_Source_Pond_Public_SkippingStones_h_36_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> POND_API UClass* StaticClass<class USkippingStones>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Pond_Source_Pond_Public_SkippingStones_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
