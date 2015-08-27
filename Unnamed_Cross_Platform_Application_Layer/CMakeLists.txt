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

set(UCPAL_DIR ${Unit_Tests_SOURCE_DIR}/Unnamed_Cross_Platform_Application_Layer)
set(UCPAL_BIN ${UCPAL_DIR}/bin)
set(UCPAL_TMP ${UCPAL_DIR}/tmp)

file(GLOB_RECURSE HDRS 
		${UCPAL_DIR}/src/*.h
		${UCPAL_DIR}/src/*.hxx
		${UCPAL_DIR}/src/*.hpp
)

#loads source files
file(GLOB_RECURSE SRCS 
		${UCPAL_DIR}/src/*.c
		${UCPAL_DIR}/src/*.cpp
		${UCPAL_DIR}/src/*.cc
		${UCPAL_DIR}/src/*.cxx
		${UCPAL_DIR}/src/*.inl
)

find_package(OpenGL REQUIRED)

include_directories(
	${UCPAL_DIR}/inc
	${UCPAL_DIR}/src
	${UCPAL_DIR}/headers
	${UCPAL_DIR}/sources
	${OPENGL_INCLUDE_DIRS}
)

#adds the library
add_library(UCPAL STATIC ${HDRS} ${SRCS})
set_target_properties(UCPAL PROPERTIES LINKER_LANGUAGE CXX)

set_target_properties(UCPAL PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${Unit_Tests_SOURCE_DIR}/bin")
set_target_properties(UCPAL PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG "${Unit_Tests_SOURCE_DIR}/bin/$(Platform)/debug")
set_target_properties(UCPAL PROPERTIES RUNTIME_OUTPUT_DIRECTORY_PROFILE "${Unit_Tests_SOURCE_DIR}/bin/$(Platform)/profile")
set_target_properties(UCPAL PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE "${Unit_Tests_SOURCE_DIR}/bin/$(Platform)/release")
set_target_properties(UCPAL PROPERTIES RUNTIME_OUTPUT_DIRECTORY_PRODUCTION "${Unit_Tests_SOURCE_DIR}/bin/$(Platform)/production")
set_target_properties(UCPAL PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${UCPAL_BIN}")
set_target_properties(UCPAL PROPERTIES LIBRARY_OUTPUT_DIRECTORY_DEBUG "${UCPAL_BIN}/$(Platform)/debug")
set_target_properties(UCPAL PROPERTIES LIBRARY_OUTPUT_DIRECTORY_PROFILE "${UCPAL_BIN}/$(Platform)/profile")
set_target_properties(UCPAL PROPERTIES LIBRARY_OUTPUT_DIRECTORY_RELEASE "${UCPAL_BIN}/$(Platform)/release")
set_target_properties(UCPAL PROPERTIES LIBRARY_OUTPUT_DIRECTORY_PRODUCTION "${UCPAL_BIN}/$(Platform)/production")
set_target_properties(UCPAL PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${UCPAL_BIN}")
set_target_properties(UCPAL PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${UCPAL_BIN}/$(Platform)/debug")
set_target_properties(UCPAL PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_PROFILE "${UCPAL_BIN}/$(Platform)/profile")
set_target_properties(UCPAL PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${UCPAL_BIN}/$(Platform)/release")
set_target_properties(UCPAL PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_PRODUCTION "${UCPAL_BIN}/$(Platform)/production")

set_target_properties(UCPAL PROPERTIES INTERMEDIATE_DIRECTORY "${UCPAL_TMP}")
set_target_properties(UCPAL PROPERTIES INTERMEDIATE_DIRECTORY_DEBUG "${UCPAL_TMP}/$(Platform)/debug")
set_target_properties(UCPAL PROPERTIES INTERMEDIATE_DIRECTORY_PROFILE "${UCPAL_TMP}/$(Platform)/profile")
set_target_properties(UCPAL PROPERTIES INTERMEDIATE_DIRECTORY_RELEASE "${UCPAL_TMP}/$(Platform)/release")
set_target_properties(UCPAL PROPERTIES INTERMEDIATE_DIRECTORY_PRODUCTION "${UCPAL_TMP}/$(Platform)/production")

#links required libraries
target_link_libraries(UCPAL winmm.lib ${OPENGL_LIBRARIES})

#install (TARGETS UCPAL RUNTIME DESTINATION "${Unit_Tests_SOURCE_DIR}/bin/$(Platform)/$(Configuration)")