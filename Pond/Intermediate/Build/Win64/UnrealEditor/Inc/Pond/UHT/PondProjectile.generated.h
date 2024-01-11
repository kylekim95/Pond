// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "PondProjectile.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class AActor;
class UPrimitiveComponent;
struct FHitResult;
#ifdef POND_PondProjectile_generated_h
#error "PondProjectile.generated.h already included, missing '#pragma once' in PondProjectile.h"
#endif
#define POND_PondProjectile_generated_h

#define FID_Pond_Source_Pond_PondProjectile_h_15_SPARSE_DATA
#define FID_Pond_Source_Pond_PondProjectile_h_15_SPARSE_DATA_PROPERTY_ACCESSORS
#define FID_Pond_Source_Pond_PondProjectile_h_15_EDITOR_ONLY_SPARSE_DATA_PROPERTY_ACCESSORS
#define FID_Pond_Source_Pond_PondProjectile_h_15_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execOnHit);


#define FID_Pond_Source_Pond_PondProjectile_h_15_ACCESSORS
#define FID_Pond_Source_Pond_PondProjectile_h_15_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAPondProjectile(); \
	friend struct Z_Construct_UClass_APondProjectile_Statics; \
public: \
	DECLARE_CLASS(APondProjectile, AActor, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/Pond"), NO_API) \
	DECLARE_SERIALIZER(APondProjectile) \
	static const TCHAR* StaticConfigName() {return TEXT("Game");} \



#define FID_Pond_Source_Pond_PondProjectile_h_15_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API APondProjectile(APondProjectile&&); \
	NO_API APondProjectile(const APondProjectile&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, APondProjectile); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(APondProjectile); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(APondProjectile) \
	NO_API virtual ~APondProjectile();


#define FID_Pond_Source_Pond_PondProjectile_h_12_PROLOG
#define FID_Pond_Source_Pond_PondProjectile_h_15_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Pond_Source_Pond_PondProjectile_h_15_SPARSE_DATA \
	FID_Pond_Source_Pond_PondProjectile_h_15_SPARSE_DATA_PROPERTY_ACCESSORS \
	FID_Pond_Source_Pond_PondProjectile_h_15_EDITOR_ONLY_SPARSE_DATA_PROPERTY_ACCESSORS \
	FID_Pond_Source_Pond_PondProjectile_h_15_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Pond_Source_Pond_PondProjectile_h_15_ACCESSORS \
	FID_Pond_Source_Pond_PondProjectile_h_15_INCLASS_NO_PURE_DECLS \
	FID_Pond_Source_Pond_PondProjectile_h_15_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> POND_API UClass* StaticClass<class APondProjectile>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Pond_Source_Pond_PondProjectile_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
