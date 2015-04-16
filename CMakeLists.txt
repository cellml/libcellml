# Copyright 2015 University of Auckland
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#    http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.cmake_minimum_required (VERSION 3.1)


cmake_minimum_required(VERSION 3.2)

set(PROJECT_NAME libCellML)
project(${PROJECT_NAME} CXX)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(common)

# Use the following variables when configuring the build from the command line to
# set the corresponding cache variables.

# COVERAGE ==> LIBCELLML_COVERAGE
set(_PARAM_ANNOTATION "Enable coverage testing.")
if(CMAKE_COMPILER_IS_GNUCXX)
  set( LIBCELLML_COVERAGE OFF CACHE BOOL ${_PARAM_ANNOTATION} )
endif()
if( COVERAGE AND CMAKE_COMPILER_IS_GNUCXX )
  set( LIBCELLML_COVERAGE "${COVERAGE}" CACHE BOOL ${_PARAM_ANNOTATION} FORCE )
endif()

# MEMCHECK ==> LIBCELLML_MEMCHECK
set(_PARAM_ANNOTATION "Enable memcheck testing.")
if(CMAKE_COMPILER_IS_GNUCXX)
  set( LIBCELLML_MEMCHECK OFF CACHE BOOL ${_PARAM_ANNOTATION} )
endif()
if( MEMCHECK AND CMAKE_COMPILER_IS_GNUCXX )
  set( LIBCELLML_MEMCHECK "${MEMCHECK}" CACHE BOOL ${_PARAM_ANNOTATION} FORCE )
endif()

# UNIT_TESTS ==> LIBCELLML_UNIT_TESTS
set(_PARAM_ANNOTATION "Enable build of automated LibCellML tests.")
set( LIBCELLML_UNIT_TESTS OFF CACHE BOOL ${_PARAM_ANNOTATION} )
if( UNIT_TESTS )
  set( LIBCELLML_UNIT_TESTS "${UNIT_TESTS}" CACHE BOOL ${_PARAM_ANNOTATION} FORCE )
endif()

if(LIBCELLML_COVERAGE OR LIBCELLML_MEMCHECK)
  set(LIBCELLML_UNIT_TESTS ON CACHE BOOL ${_PARAM_ANNOTATION} FORCE)
endif()

# TWAE ==> LIBCELLML_WARNINGS_AS_ERRORS -- Note: This excludes third party code, where warnings are never treated as errors.
set(_PARAM_ANNOTATION "Treat warnings as errors (note: warnings in 3rd party code are never treated as errors)")
set( LIBCELLML_TREAT_WARNINGS_AS_ERRORS OFF CACHE BOOL ${_PARAM_ANNOTATION} )
if( TWAE )
  set( LIBCELLML_TREAT_WARNINGS_AS_ERRORS "${TWAE}" CACHE BOOL ${_PARAM_ANNOTATION} FORCE )
endif()

# BUILD_TYPE ==> LIBCELLML_BUILD_TYPE
set(_PARAM_ANNOTATION "Choose the type of build, options are: None(CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release RelWithDebInfo MinSizeRel.")
set( LIBCELLML_BUILD_TYPE "Release" CACHE STRING ${_PARAM_ANNOTATION} )
if( BUILD_TYPE )
  set( LIBCELLML_BUILD_TYPE ${BUILD_TYPE} CACHE STRING ${_PARAM_ANNOTATION} FORCE )
endif()
if( LIBCELLML_MEMCHECK OR LIBCELLML_COVERAGE)
  set( LIBCELLML_BUILD_TYPE "Debug" CACHE STRING ${_PARAM_ANNOTATION} FORCE )
endif()

# INSTALL_PREFIX ==> LIBCELLML_INSTALL_PREFIX
set(_PARAM_ANNOTATION "Install path prefix, prepended onto install directories.")
set( LIBCELLML_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX} CACHE STRING ${_PARAM_ANNOTATION} )
if( INSTALL_PREFIX )
  set( LIBCELLML_INSTALL_PREFIX ${INSTALL_PREFIX} CACHE STRING ${_PARAM_ANNOTATION} FORCE )
endif()

# BUILD_SHARED ==> LIBCELLML_BUILD_SHARED
set(_PARAM_ANNOTATION "Build shared libraries (so, dylib, DLLs).")
set( LIBCELLML_BUILD_SHARED OFF CACHE BOOL ${_PARAM_ANNOTATION} )
if( BUILD_SHARED )
  set( LIBCELLML_BUILD_SHARED ${BUILD_SHARED} CACHE BOOL ${_PARAM_ANNOTATION} FORCE )
endif()

# internalise some CMake variables
set( CMAKE_INSTALL_PREFIX ${LIBCELLML_INSTALL_PREFIX} CACHE INTERNAL "Internalise CMAKE_INSTALL_PREFIX, manipulate via LIBCELLML_INSTALL_PREFIX" FORCE )
set( CMAKE_BUILD_TYPE ${LIBCELLML_BUILD_TYPE} CACHE INTERNAL "Internalise CMAKE_BUILD_TYPE, manipulate via LIBCELLML_BUILD_TYPE" FORCE )
set( BUILD_SHARED_LIBS ${LIBCELLML_BUILD_SHARED} CACHE INTERNAL "Internalise BUILD_SHARED_LIBS, manipulate via LIBCELLML_BUILD_SHARED" FORCE )
set( CMAKE_CODEBLOCKS_EXECUTABLE "" CACHE INTERNAL "The CodeBlocks executable" FORCE )

# cellml library target
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src)

if (LIBCELLML_UNIT_TESTS)
  # enable testing here so that we can make use of the 'test' target
  enable_testing()
  add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/tests)
endif()

