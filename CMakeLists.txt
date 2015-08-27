cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

set(CMAKE_CONFIGURATION_TYPES Debug Profile Release Production CACHE TYPE INTERNAL FORCE )

MACRO(ADD_MSVC_PRECOMPILED_HEADER PrecompiledHeader PrecompiledSource SourcesVar)
  IF(MSVC)
    GET_FILENAME_COMPONENT(PrecompiledBasename ${PrecompiledHeader} NAME_WE)
    SET(PrecompiledBinary "${CMAKE_CURRENT_BINARY_DIR}/${PrecompiledBasename}.pch")
    SET(Sources ${${SourcesVar}})

    SET_SOURCE_FILES_PROPERTIES(${PrecompiledSource}
                                PROPERTIES COMPILE_FLAGS "/Yc\"${PrecompiledHeader}\" /Fp\"${PrecompiledBinary}\""
                                           OBJECT_OUTPUTS "${PrecompiledBinary}")
    SET_SOURCE_FILES_PROPERTIES(${Sources}
                                PROPERTIES COMPILE_FLAGS "/Yu\"${PrecompiledHeader}\" /FI\"${PrecompiledHeader}\" /Fp\"${PrecompiledBinary}\""
                                           OBJECT_DEPENDS "${PrecompiledBinary}")  
    # Add precompiled header to SourcesVar
    LIST(APPEND ${SourcesVar} ${PrecompiledSource})
  ENDIF(MSVC)
ENDMACRO(ADD_MSVC_PRECOMPILED_HEADER)

project(Unit_Tests)

set(warnings "/W3 /WX")
	
set(CMAKE_CXX_FLAGS "/D WIN32 /D _WINDOWS /GR /Oi /EHsc")	
set(CMAKE_CXX_FLAGS_DEBUG "/D _DEBUG /D AVRO_DEBUG /MTd /Zi /Ob0 /Od /RTC1")
set(CMAKE_CXX_FLAGS_PROFILE "/D NDEBUG /D AVRO_PROFILE /MT /Zi /O2 /Ob1")
set(CMAKE_CXX_FLAGS_RELEASE "/D NDEBUG /D AVRO_RELEASE /MT /O2 /Ob2")
set(CMAKE_CXX_FLAGS_PRODUCTION "/D NDEBUG /D AVRO_PRODUCTION /MT /Ox /Ob2")
	
set(CMAKE_EXE_LINKER_FLAGS "/SUBSYSTEM:WINDOWS")
set(CMAKE_EXE_LINKER_FLAGS_DEBUG "/debug /INCREMENTAL")
set(CMAKE_EXE_LINKER_FLAGS_PROFILE "/debug /INCREMENTAL")
set(CMAKE_EXE_LINKER_FLAGS_RELEASE "/INCREMENTAL:NO")
set(CMAKE_EXE_LINKER_FLAGS_PRODUCTION "/INCREMENTAL:NO")

set(CMAKE_SHARED_LINKER_FLAGS "")
set(CMAKE_SHARED_LINKER_FLAGS_DEBUG "/debug")
set(CMAKE_SHARED_LINKER_FLAGS_PROFILE "/debug")
set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "/INCREMENTAL:NO")
set(CMAKE_SHARED_LINKER_FLAGS_PRODUCTION "/INCREMENTAL:NO")

set(CMAKE_CXX_FLAGS)

if( CMAKE_BUILD_TYPE STREQUAL "" )
	
	set( CMAKE_BUILD_TYPE "Debug")
	
endif ( CMAKE_BUILD_TYPE STREQUAL "" )

add_definitions(${warnings})

#builds engine and cross platform application layer
add_subdirectory(Unnamed_Engine_Architecture)
add_subdirectory(Unnamed_Cross_Platform_Application_Layer)

#loads Unit_Tests headers
file(GLOB_RECURSE HDRS 
		${Unit_Tests_SOURCE_DIR}/src/*.h
		${Unit_Tests_SOURCE_DIR}/src/*.hxx
		${Unit_Tests_SOURCE_DIR}/src/*.hpp
)

#loads Unit_Tests source files
file(GLOB_RECURSE SRCS 
		${Unit_Tests_SOURCE_DIR}/src/*.c
		${Unit_Tests_SOURCE_DIR}/src/*.cpp
		${Unit_Tests_SOURCE_DIR}/src/*.cc
		${Unit_Tests_SOURCE_DIR}/src/*.cxx
		${Unit_Tests_SOURCE_DIR}/src/*.inl
)

include_directories(
	${Unit_Tests_SOURCE_DIR}/inc
	${Unit_Tests_SOURCE_DIR}/src
	${Unit_Tests_SOURCE_DIR}/headers
	${Unit_Tests_SOURCE_DIR}/sources
	${Unit_Tests_SOURCE_DIR}/Unnamed_Cross_Platform_Application_Layer/inc
	${Unit_Tests_SOURCE_DIR}/Unnamed_Cross_Platform_Application_Layer/src
	${Unit_Tests_SOURCE_DIR}/Unnamed_Cross_Platform_Application_Layer/headers
	${Unit_Tests_SOURCE_DIR}/Unnamed_Cross_Platform_Application_Layer/sources
	${Unit_Tests_SOURCE_DIR}/Unnamed_Engine_Architecture/inc
	${Unit_Tests_SOURCE_DIR}/Unnamed_Engine_Architecture/src
	${Unit_Tests_SOURCE_DIR}/Unnamed_Engine_Architecture/headers
	${Unit_Tests_SOURCE_DIR}/Unnamed_Engine_Architecture/sources
)

set(Unit_Tests_BIN ${Unit_Tests_SOURCE_DIR}/bin)
set(Unit_Tests_TMP ${Unit_Tests_SOURCE_DIR}/tmp)

#adds Unit_Tests executable
add_executable (Unit_Tests ${HDRS} ${SRCS})
set_target_properties(Unit_Tests PROPERTIES LINKER_LANGUAGE CXX)

set_target_properties(Unit_Tests PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${Unit_Tests_BIN}")
set_target_properties(Unit_Tests PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG "${Unit_Tests_BIN}/$(Platform)/debug")
set_target_properties(Unit_Tests PROPERTIES RUNTIME_OUTPUT_DIRECTORY_PROFILE "${Unit_Tests_BIN}/$(Platform)/profile")
set_target_properties(Unit_Tests PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE "${Unit_Tests_BIN}/$(Platform)/release")
set_target_properties(Unit_Tests PROPERTIES RUNTIME_OUTPUT_DIRECTORY_PRODUCTION "${Unit_Tests_BIN}/$(Platform)/production")
set_target_properties(Unit_Tests PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${Unit_Tests_BIN}")
set_target_properties(Unit_Tests PROPERTIES LIBRARY_OUTPUT_DIRECTORY_DEBUG "${Unit_Tests_BIN}/$(Platform)/debug")
set_target_properties(Unit_Tests PROPERTIES LIBRARY_OUTPUT_DIRECTORY_PROFILE "${Unit_Tests_BIN}/$(Platform)/profile")
set_target_properties(Unit_Tests PROPERTIES LIBRARY_OUTPUT_DIRECTORY_RELEASE "${Unit_Tests_BIN}/$(Platform)/release")
set_target_properties(Unit_Tests PROPERTIES LIBRARY_OUTPUT_DIRECTORY_PRODUCTION "${Unit_Tests_BIN}/$(Platform)/production")
set_target_properties(Unit_Tests PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${Unit_Tests_BIN}")
set_target_properties(Unit_Tests PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${Unit_Tests_BIN}/$(Platform)/debug")
set_target_properties(Unit_Tests PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_PROFILE "${Unit_Tests_BIN}/$(Platform)/profile")
set_target_properties(Unit_Tests PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${Unit_Tests_BIN}/$(Platform)/release")
set_target_properties(Unit_Tests PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_PRODUCTION "${Unit_Tests_BIN}/$(Platform)/production")

set_target_properties(Unit_Tests PROPERTIES INTERMEDIATE_DIRECTORY "${Unit_Tests_TMP}")
set_target_properties(Unit_Tests PROPERTIES INTERMEDIATE_DIRECTORY_DEBUG "${Unit_Tests_TMP}/$(Platform)/debug")
set_target_properties(Unit_Tests PROPERTIES INTERMEDIATE_DIRECTORY_PROFILE "${Unit_Tests_TMP}/$(Platform)/profile")
set_target_properties(Unit_Tests PROPERTIES INTERMEDIATE_DIRECTORY_RELEASE "${Unit_Tests_TMP}/$(Platform)/release")
set_target_properties(Unit_Tests PROPERTIES INTERMEDIATE_DIRECTORY_PRODUCTION "${Unit_Tests_TMP}/$(Platform)/production")

#links engine and rendering engine
target_link_libraries(Unit_Tests ENG UCPAL)