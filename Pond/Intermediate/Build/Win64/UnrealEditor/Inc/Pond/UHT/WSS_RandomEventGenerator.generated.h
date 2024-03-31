// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Subsystems/WSS_RandomEventGenerator.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class UREGEvent;
struct FInfluence;
#ifdef POND_WSS_RandomEventGenerator_generated_h
#error "WSS_RandomEventGenerator.generated.h already included, missing '#pragma once' in WSS_RandomEventGenerator.h"
#endif
#define POND_WSS_RandomEventGenerator_generated_h

#define FID_Pond_Source_Pond_Public_Subsystems_WSS_RandomEventGenerator_h_17_SPARSE_DATA
#define FID_Pond_Source_Pond_Public_Subsystems_WSS_RandomEventGenerator_h_17_SPARSE_DATA_PROPERTY_ACCESSORS
#define FID_Pond_Source_Pond_Public_Subsystems_WSS_RandomEventGenerator_h_17_EDITOR_ONLY_SPARSE_DATA_PROPERTY_ACCESSORS
#define FID_Pond_Source_Pond_Public_Subsystems_WSS_RandomEventGenerator_h_17_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execAddEvent); \
	DECLARE_FUNCTION(execNotify);


#define FID_Pond_Source_Pond_Public_Subsystems_WSS_RandomEventGenerator_h_17_ACCESSORS
#define FID_Pond_Source_Pond_Public_Subsystems_WSS_RandomEventGenerator_h_17_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUWSS_RandomEventGenerator(); \
	friend struct Z_Construct_UClass_UWSS_RandomEventGenerator_Statics; \
public: \
	DECLARE_CLASS(UWSS_RandomEventGenerator, UWorldSubsystem, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/Pond"), NO_API) \
	DECLARE_SERIALIZER(UWSS_RandomEventGenerator)


#define FID_Pond_Source_Pond_Public_Subsystems_WSS_RandomEventGenerator_h_17_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UWSS_RandomEventGenerator(); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UWSS_RandomEventGenerator(UWSS_RandomEventGenerator&&); \
	NO_API UWSS_RandomEventGenerator(const UWSS_RandomEventGenerator&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UWSS_RandomEventGenerator); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UWSS_RandomEventGenerator); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UWSS_RandomEventGenerator) \
	NO_API virtual ~UWSS_RandomEventGenerator();


#define FID_Pond_Source_Pond_Public_Subsystems_WSS_RandomEventGenerator_h_14_PROLOG
#define FID_Pond_Source_Pond_Public_Subsystems_WSS_RandomEventGenerator_h_17_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Pond_Source_Pond_Public_Subsystems_WSS_RandomEventGenerator_h_17_SPARSE_DATA \
	FID_Pond_Source_Pond_Public_Subsystems_WSS_RandomEventGenerator_h_17_SPARSE_DATA_PROPERTY_ACCESSORS \
	FID_Pond_Source_Pond_Public_Subsystems_WSS_RandomEventGenerator_h_17_EDITOR_ONLY_SPARSE_DATA_PROPERTY_ACCESSORS \
	FID_Pond_Source_Pond_Public_Subsystems_WSS_RandomEventGenerator_h_17_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Pond_Source_Pond_Public_Subsystems_WSS_RandomEventGenerator_h_17_ACCESSORS \
	FID_Pond_Source_Pond_Public_Subsystems_WSS_RandomEventGenerator_h_17_INCLASS_NO_PURE_DECLS \
	FID_Pond_Source_Pond_Public_Subsystems_WSS_RandomEventGenerator_h_17_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> POND_API UClass* StaticClass<class UWSS_RandomEventGenerator>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Pond_Source_Pond_Public_Subsystems_WSS_RandomEventGenerator_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
