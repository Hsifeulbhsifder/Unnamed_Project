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

set(warnings "/W3 /WX")
	
set(CMAKE_CXX_FLAGS "/D WIN32 /D _WINDOWS /GR /Oi /EHsc")	
set(CMAKE_CXX_FLAGS_DEBUG "/D _DEBUG /D AVRO_DEBUG /MTd /Zi /Ob0 /Od /RTC1")
set(CMAKE_CXX_FLAGS_PROFILE "/D NDEBUG /D AVRO_PROFILE /MT /Zi /O2 /Ob1")
set(CMAKE_CXX_FLAGS_RELEASE "/D NDEBUG /D AVRO_RELEASE /MT /O2 /Ob2")
set(CMAKE_CXX_FLAGS_PRODUCTION "/D NDEBUG /D AVRO_PRODUCTION /MT /Ox /Ob2")
	
set(CMAKE_SHARED_LINKER_FLAGS "")
set(CMAKE_SHARED_LINKER_FLAGS_DEBUG "/debug /INCREMENTAL")
set(CMAKE_SHARED_LINKER_FLAGS_PROFILE "/debug /INCREMENTAL")
set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "/INCREMENTAL:NO")
set(CMAKE_SHARED_LINKER_FLAGS_PRODUCTION "/INCREMENTAL:NO")

set(ENG_DIR ${Unit_Tests_SOURCE_DIR}/Unnamed_Engine_Architecture)
set(ENG_BIN ${ENG_DIR}/bin)
set(ENG_TMP ${ENG_DIR}/tmp)

#loads headers
file(GLOB_RECURSE HDRS 
		${ENG_DIR}/src/*.h
		${ENG_DIR}/src/*.hxx
		${ENG_DIR}/src/*.hpp
)

#loads source files
file(GLOB_RECURSE SRCS 
		${ENG_DIR}/src/*.c
		${ENG_DIR}/src/*.cpp
		${ENG_DIR}/src/*.cc
		${ENG_DIR}/src/*.cxx
		${ENG_DIR}/src/*.inl
)

include_directories(
	${ENG_DIR}/inc
	${ENG_DIR}/src
	${ENG_DIR}/headers
	${ENG_DIR}/sources
	${Unit_Tests_SOURCE_DIR}/Unnamed_Cross_Platform_Application_Layer/inc
	${Unit_Tests_SOURCE_DIR}/Unnamed_Cross_Platform_Application_Layer/src
	${Unit_Tests_SOURCE_DIR}/Unnamed_Cross_Platform_Application_Layer/headers
	${Unit_Tests_SOURCE_DIR}/Unnamed_Cross_Platform_Application_Layer/sources
)

#adds the library
add_library(ENG STATIC ${HDRS} ${SRCS})
set_target_properties(ENG PROPERTIES LINKER_LANGUAGE CXX)

set_target_properties(ENG PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${Unit_Tests_SOURCE_DIR}/bin")
set_target_properties(ENG PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG "${Unit_Tests_SOURCE_DIR}/bin/$(Platform)/debug")
set_target_properties(ENG PROPERTIES RUNTIME_OUTPUT_DIRECTORY_PROFILE "${Unit_Tests_SOURCE_DIR}/bin/$(Platform)/profile")
set_target_properties(ENG PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE "${Unit_Tests_SOURCE_DIR}/bin/$(Platform)/release")
set_target_properties(ENG PROPERTIES RUNTIME_OUTPUT_DIRECTORY_PRODUCTION "${Unit_Tests_SOURCE_DIR}/bin/$(Platform)/production")
set_target_properties(ENG PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${ENG_BIN}")
set_target_properties(ENG PROPERTIES LIBRARY_OUTPUT_DIRECTORY_DEBUG "${ENG_BIN}/$(Platform)/debug")
set_target_properties(ENG PROPERTIES LIBRARY_OUTPUT_DIRECTORY_PROFILE "${ENG_BIN}/$(Platform)/profile")
set_target_properties(ENG PROPERTIES LIBRARY_OUTPUT_DIRECTORY_RELEASE "${ENG_BIN}/$(Platform)/release")
set_target_properties(ENG PROPERTIES LIBRARY_OUTPUT_DIRECTORY_PRODUCTION "${ENG_BIN}/$(Platform)/production")
set_target_properties(ENG PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${ENG_BIN}")
set_target_properties(ENG PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${ENG_BIN}/$(Platform)/debug")
set_target_properties(ENG PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_PROFILE "${ENG_BIN}/$(Platform)/profile")
set_target_properties(ENG PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${ENG_BIN}/$(Platform)/release")
set_target_properties(ENG PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_PRODUCTION "${ENG_BIN}/$(Platform)/production")

set_target_properties(ENG PROPERTIES INTERMEDIATE_DIRECTORY "${ENG_TMP}")
set_target_properties(ENG PROPERTIES INTERMEDIATE_DIRECTORY_DEBUG "${ENG_TMP}/$(Platform)/debug")
set_target_properties(ENG PROPERTIES INTERMEDIATE_DIRECTORY_PROFILE "${ENG_TMP}/$(Platform)/profile")
set_target_properties(ENG PROPERTIES INTERMEDIATE_DIRECTORY_RELEASE "${ENG_TMP}/$(Platform)/release")
set_target_properties(ENG PROPERTIES INTERMEDIATE_DIRECTORY_PRODUCTION "${ENG_TMP}/$(Platform)/production")

#links cross platform application layer
target_link_libraries(ENG UCPAL)

#install (TARGETS ENG RUNTIME DESTINATION "${Unit_Tests_SOURCE_DIR}/bin/$(Platform)/$(Configuration)")