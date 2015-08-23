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

project(Unnamed_Game)

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

#loads Unnamed_Game headers
file(GLOB_RECURSE HDRS 
		${Unnamed_Game_SOURCE_DIR}/src/*.h
		${Unnamed_Game_SOURCE_DIR}/src/*.hxx
		${Unnamed_Game_SOURCE_DIR}/src/*.hpp
)

#loads Unnamed_Game source files
file(GLOB_RECURSE SRCS 
		${Unnamed_Game_SOURCE_DIR}/src/*.c
		${Unnamed_Game_SOURCE_DIR}/src/*.cpp
		${Unnamed_Game_SOURCE_DIR}/src/*.cc
		${Unnamed_Game_SOURCE_DIR}/src/*.cxx
		${Unnamed_Game_SOURCE_DIR}/src/*.inl
)

include_directories(
	${Unnamed_Game_SOURCE_DIR}/inc
	${Unnamed_Game_SOURCE_DIR}/src
	${Unnamed_Game_SOURCE_DIR}/headers
	${Unnamed_Game_SOURCE_DIR}/sources
	${Unnamed_Game_SOURCE_DIR}/Unnamed_Cross_Platform_Application_Layer/inc
	${Unnamed_Game_SOURCE_DIR}/Unnamed_Cross_Platform_Application_Layer/src
	${Unnamed_Game_SOURCE_DIR}/Unnamed_Cross_Platform_Application_Layer/headers
	${Unnamed_Game_SOURCE_DIR}/Unnamed_Cross_Platform_Application_Layer/sources
	${Unnamed_Game_SOURCE_DIR}/Unnamed_Engine_Architecture/inc
	${Unnamed_Game_SOURCE_DIR}/Unnamed_Engine_Architecture/src
	${Unnamed_Game_SOURCE_DIR}/Unnamed_Engine_Architecture/headers
	${Unnamed_Game_SOURCE_DIR}/Unnamed_Engine_Architecture/sources
)

set(Unnamed_Game_BIN ${Unnamed_Game_SOURCE_DIR}/bin)
set(Unnamed_Game_TMP ${Unnamed_Game_SOURCE_DIR}/tmp)

#adds Unnamed_Game executable
add_executable (Unnamed_Game ${HDRS} ${SRCS})
set_target_properties(Unnamed_Game PROPERTIES LINKER_LANGUAGE CXX)

set_target_properties(Unnamed_Game PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${Unnamed_Game_BIN}")
set_target_properties(Unnamed_Game PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG "${Unnamed_Game_BIN}/$(Platform)/debug")
set_target_properties(Unnamed_Game PROPERTIES RUNTIME_OUTPUT_DIRECTORY_PROFILE "${Unnamed_Game_BIN}/$(Platform)/profile")
set_target_properties(Unnamed_Game PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE "${Unnamed_Game_BIN}/$(Platform)/release")
set_target_properties(Unnamed_Game PROPERTIES RUNTIME_OUTPUT_DIRECTORY_PRODUCTION "${Unnamed_Game_BIN}/$(Platform)/production")
set_target_properties(Unnamed_Game PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${Unnamed_Game_BIN}")
set_target_properties(Unnamed_Game PROPERTIES LIBRARY_OUTPUT_DIRECTORY_DEBUG "${Unnamed_Game_BIN}/$(Platform)/debug")
set_target_properties(Unnamed_Game PROPERTIES LIBRARY_OUTPUT_DIRECTORY_PROFILE "${Unnamed_Game_BIN}/$(Platform)/profile")
set_target_properties(Unnamed_Game PROPERTIES LIBRARY_OUTPUT_DIRECTORY_RELEASE "${Unnamed_Game_BIN}/$(Platform)/release")
set_target_properties(Unnamed_Game PROPERTIES LIBRARY_OUTPUT_DIRECTORY_PRODUCTION "${Unnamed_Game_BIN}/$(Platform)/production")
set_target_properties(Unnamed_Game PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${Unnamed_Game_BIN}")
set_target_properties(Unnamed_Game PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${Unnamed_Game_BIN}/$(Platform)/debug")
set_target_properties(Unnamed_Game PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_PROFILE "${Unnamed_Game_BIN}/$(Platform)/profile")
set_target_properties(Unnamed_Game PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${Unnamed_Game_BIN}/$(Platform)/release")
set_target_properties(Unnamed_Game PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_PRODUCTION "${Unnamed_Game_BIN}/$(Platform)/production")

set_target_properties(Unnamed_Game PROPERTIES INTERMEDIATE_DIRECTORY "${Unnamed_Game_TMP}")
set_target_properties(Unnamed_Game PROPERTIES INTERMEDIATE_DIRECTORY_DEBUG "${Unnamed_Game_TMP}/$(Platform)/debug")
set_target_properties(Unnamed_Game PROPERTIES INTERMEDIATE_DIRECTORY_PROFILE "${Unnamed_Game_TMP}/$(Platform)/profile")
set_target_properties(Unnamed_Game PROPERTIES INTERMEDIATE_DIRECTORY_RELEASE "${Unnamed_Game_TMP}/$(Platform)/release")
set_target_properties(Unnamed_Game PROPERTIES INTERMEDIATE_DIRECTORY_PRODUCTION "${Unnamed_Game_TMP}/$(Platform)/production")

#links engine and rendering engine
target_link_libraries(Unnamed_Game ENG UCPAL)