# Function: Test_LibXml2_Const_Error_Structured_Error_Callback
#
# Test if LibXml2 uses const Error * for structured error callback function.
#
# CONST_ERROR_STRUCTURED_ERROR_CALLBACK - true if const Error * is required
# for structuredErrorCallback.
#

function(Test_LibXml2_Const_Error_Structured_Error_Callback)
  set(_VAR_NAME "CONST_ERROR_STRUCTURED_ERROR_CALLBACK")
  set(_HASH_VAR_NAME "HASH_${_VAR_NAME}")

  # Hash the CMAKE_FLAGS passed and check cache to know if we need to rerun.
  string(MD5 _CMAKE_FLAGS_HASH "${CMAKE_SHARED_LINKER_FLAGS}")

  if(NOT DEFINED "${_HASH_VAR_NAME}")
    unset("${_VAR_NAME}" CACHE)
  elseif(NOT "${${_HASH_VAR_NAME}}" STREQUAL "${_CMAKE_FLAGS_HASH}")
    unset("${_VAR_NAME}" CACHE)
  endif()

  if(NOT DEFINED "${_VAR_NAME}")
    message(STATUS "Performing Test ${_VAR_NAME} - ...")
    set(_TEST_PROJECT_DIR "${PROJECT_BINARY_DIR}/CMakeTmp/${_VAR_NAME}")

    file(WRITE "${_TEST_PROJECT_DIR}/CMakeLists.txt"
"
cmake_minimum_required(VERSION 3.18.0)
project(undefined CXX)
add_library(foo SHARED \"foo.cpp\")
")
    if(HAVE_LIBXML2_CONFIG)
      file(TO_CMAKE_PATH "${LibXml2_DIR}" _SAFE_LibXml2_DIR)
      file(APPEND "${_TEST_PROJECT_DIR}/CMakeLists.txt"
"
set(LibXml2_DIR \"${_SAFE_LibXml2_DIR}\")
find_package(LibXml2 CONFIG)
target_link_libraries(foo PUBLIC ${LIBXML2_TARGET_NAME})
")
    else()
      file(APPEND "${_TEST_PROJECT_DIR}/CMakeLists.txt"
"
find_package(LibXml2)
target_include_directories(foo PUBLIC ${LIBXML2_INCLUDE_DIR})
target_link_libraries(foo PUBLIC ${LIBXML2_LIBRARIES})
target_compile_definitions(foo PUBLIC ${LIBXML2_DEFINITIONS})
")
    endif()

    file(WRITE "${_TEST_PROJECT_DIR}/foo.cpp"
"
#include <libxml/tree.h>
#include <libxml/xmlerror.h>

void structuredErrorCallback(void *userData, const xmlError *error)
{
}

void function()
{
    xmlInitParser();
    xmlParserCtxtPtr context = xmlNewParserCtxt();
    xmlSetStructuredErrorFunc(context, structuredErrorCallback);
    xmlFreeParserCtxt(context);
    xmlSetStructuredErrorFunc(nullptr, nullptr);
    xmlCleanupParser();
}
")

    try_compile(${_VAR_NAME}
      "${_TEST_PROJECT_DIR}"
      "${_TEST_PROJECT_DIR}"
      undefined
      CMAKE_FLAGS
        "-DCMAKE_SHARED_LINKER_FLAGS='${CMAKE_SHARED_LINKER_FLAGS}'"
      OUTPUT_VARIABLE _OUTPUT)

    set(${_HASH_VAR_NAME} "${_CMAKE_FLAGS_HASH}" CACHE INTERNAL  "Hashed try_compile flags.")

    if(${_VAR_NAME})
      message(STATUS "Performing Test ${_VAR_NAME} - Success")
    else()
      message(STATUS "Performing Test ${_VAR_NAME} - Failed")
      file(APPEND ${CMAKE_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/CMakeError.log
        "Performing Test ${_VAR_NAME} failed with the following output:\n"
        "${_OUTPUT}\n")
    endif()
  endif()
endfunction()
