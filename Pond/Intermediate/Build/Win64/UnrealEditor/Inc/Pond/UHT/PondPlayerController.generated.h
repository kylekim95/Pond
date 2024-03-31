// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "PondPlayerController.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef POND_PondPlayerController_generated_h
#error "PondPlayerController.generated.h already included, missing '#pragma once' in PondPlayerController.h"
#endif
#define POND_PondPlayerController_generated_h

#define FID_Pond_Source_Pond_PondPlayerController_h_17_SPARSE_DATA
#define FID_Pond_Source_Pond_PondPlayerController_h_17_SPARSE_DATA_PROPERTY_ACCESSORS
#define FID_Pond_Source_Pond_PondPlayerController_h_17_EDITOR_ONLY_SPARSE_DATA_PROPERTY_ACCESSORS
#define FID_Pond_Source_Pond_PondPlayerController_h_17_RPC_WRAPPERS_NO_PURE_DECLS
#define FID_Pond_Source_Pond_PondPlayerController_h_17_ACCESSORS
#define FID_Pond_Source_Pond_PondPlayerController_h_17_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAPondPlayerController(); \
	friend struct Z_Construct_UClass_APondPlayerController_Statics; \
public: \
	DECLARE_CLASS(APondPlayerController, APlayerController, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/Pond"), NO_API) \
	DECLARE_SERIALIZER(APondPlayerController)


#define FID_Pond_Source_Pond_PondPlayerController_h_17_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API APondPlayerController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API APondPlayerController(APondPlayerController&&); \
	NO_API APondPlayerController(const APondPlayerController&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, APondPlayerController); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(APondPlayerController); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(APondPlayerController) \
	NO_API virtual ~APondPlayerController();


#define FID_Pond_Source_Pond_PondPlayerController_h_14_PROLOG
#define FID_Pond_Source_Pond_PondPlayerController_h_17_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Pond_Source_Pond_PondPlayerController_h_17_SPARSE_DATA \
	FID_Pond_Source_Pond_PondPlayerController_h_17_SPARSE_DATA_PROPERTY_ACCESSORS \
	FID_Pond_Source_Pond_PondPlayerController_h_17_EDITOR_ONLY_SPARSE_DATA_PROPERTY_ACCESSORS \
	FID_Pond_Source_Pond_PondPlayerController_h_17_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Pond_Source_Pond_PondPlayerController_h_17_ACCESSORS \
	FID_Pond_Source_Pond_PondPlayerController_h_17_INCLASS_NO_PURE_DECLS \
	FID_Pond_Source_Pond_PondPlayerController_h_17_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> POND_API UClass* StaticClass<class APondPlayerController>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Pond_Source_Pond_PondPlayerController_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
