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

  # hash the CMAKE_FLAGS passed and check cache to know if we need to rerun
  string(MD5 cmake_flags_hash "${CMAKE_SHARED_LINKER_FLAGS}")

  if(NOT DEFINED "${_HASH_VAR_NAME}")
    unset("${_VAR_NAME}" CACHE)
  elseif(NOT "${${_HASH_VAR_NAME}}" STREQUAL "${cmake_flags_hash}")
    unset("${_VAR_NAME}" CACHE)
  endif()

  if(NOT DEFINED "${_VAR_NAME}")
    message(STATUS "Performing Test ${_VAR_NAME} - ...")
    set(test_project_dir "${PROJECT_BINARY_DIR}/CMakeTmp/${_VAR_NAME}")

    file(WRITE "${test_project_dir}/CMakeLists.txt"
"
cmake_minimum_required(VERSION 3.18.0)
project(undefined CXX)
add_library(foo SHARED \"foo.cpp\")
")
    if(HAVE_LIBXML2_CONFIG)
      file(APPEND "${test_project_dir}/CMakeLists.txt"
"
target_link_libraries(foo PUBLIC ${LIBXML2_TARGET_NAME})
")
    else()
      file(APPEND "${test_project_dir}/CMakeLists.txt"
"
target_include_directories(foo PUBLIC ${LIBXML2_INCLUDE_DIR})
target_link_libraries(foo PUBLIC ${LIBXML2_LIBRARIES})
target_compile_definitions(foo PUBLIC ${LIBXML2_DEFINITIONS})
")
    endif()

    file(WRITE "${test_project_dir}/foo.cpp"
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
    context->_private = reinterpret_cast<void *>(this);
    xmlSetStructuredErrorFunc(context, structuredErrorCallback);
    //xmlCtxtReadDoc(context, reinterpret_cast<const xmlChar *>(\"basically empty\"), \"/\", nullptr, 0);
    xmlFreeParserCtxt(context);
    xmlSetStructuredErrorFunc(nullptr, nullptr);
    xmlCleanupParser();
}
")

    try_compile(${_VAR_NAME}
      "${test_project_dir}"
      "${test_project_dir}"
      undefined
      CMAKE_FLAGS
        "-DCMAKE_SHARED_LINKER_FLAGS='${CMAKE_SHARED_LINKER_FLAGS}'"
        ${_rpath_arg}
      OUTPUT_VARIABLE output)

    set(${_HASH_VAR_NAME} "${cmake_flags_hash}" CACHE INTERNAL  "hashed try_compile flags")
    message(STATUS "Output:\n${output}")
    message(STATUS "OUTPUT_:\n${OUTPUT_}")
    message(STATUS "Output:\n${OUTPUT}")

    if(${_VAR_NAME})
      message(STATUS "Performing Test ${_VAR_NAME} - Success")
    else()
      message(STATUS "Performing Test ${_VAR_NAME} - Failed")
      file(APPEND ${CMAKE_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/CMakeError.log
        "Performing Test ${_VAR_NAME} failed with the following output:\n"
        "${OUTPUT}\n")
    endif()
  endif()
endfunction()
