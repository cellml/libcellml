# Copyright 2015 libCellML Contributors
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
project(${PROJECT_NAME} VERSION 0.1.0 LANGUAGES CXX)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(common)
include(environmentchecks)

# Use the following variables when configuring the build from the command line to
# set the corresponding cache variables.

# COVERAGE ==> LIBCELLML_COVERAGE
set(_PARAM_ANNOTATION "Enable coverage testing.")
if(COVERAGE_TEST_AVAILABLE)
  set(LIBCELLML_COVERAGE ON CACHE BOOL ${_PARAM_ANNOTATION})
endif()
if(COVERAGE AND COVERAGE_TEST_AVAILABLE)
  set(LIBCELLML_COVERAGE "${COVERAGE}" CACHE BOOL ${_PARAM_ANNOTATION} FORCE)
elseif(COVERAGE)
  message(WARNING "Coverage testing requested but gcov or its requirements not found!")
  unset(COVERAGE CACHE)
endif()

# MEMCHECK ==> LIBCELLML_MEMCHECK
set(_PARAM_ANNOTATION "Enable memcheck testing.")
if(VALGRIND_TESTING_AVAILABLE)
  set(LIBCELLML_MEMCHECK ON CACHE BOOL ${_PARAM_ANNOTATION})
endif()
if(MEMCHECK AND VALGRIND_TESTING_AVAILABLE)
  set(LIBCELLML_MEMCHECK "${MEMCHECK}" CACHE BOOL ${_PARAM_ANNOTATION} FORCE)
elseif(MEMCHECK)
  message(WARNING "Memcheck testing requested but valgrind or its requirements not found!")
  unset(MEMCHECK CACHE)
endif()

# UNIT_TESTS ==> LIBCELLML_UNIT_TESTS
set(_PARAM_ANNOTATION "Enable libCellML tests.")
set(LIBCELLML_UNIT_TESTS ON CACHE BOOL ${_PARAM_ANNOTATION})
if(UNIT_TESTS)
  set(LIBCELLML_UNIT_TESTS "${UNIT_TESTS}" CACHE BOOL ${_PARAM_ANNOTATION} FORCE)
endif()

if(LIBCELLML_COVERAGE OR LIBCELLML_MEMCHECK)
  set(LIBCELLML_UNIT_TESTS ON CACHE BOOL ${_PARAM_ANNOTATION} FORCE)
endif()

# TWAE ==> LIBCELLML_TREAT_WARNINGS_AS_ERRORS -- Note: This excludes third party code, where warnings are never treated as errors.
set(_PARAM_ANNOTATION "Treat warnings as errors, this setting applies only to compilation units built by this project.")
set(LIBCELLML_TREAT_WARNINGS_AS_ERRORS ON CACHE BOOL ${_PARAM_ANNOTATION})
if(TWAE)
  set(LIBCELLML_TREAT_WARNINGS_AS_ERRORS "${TWAE}" CACHE BOOL ${_PARAM_ANNOTATION} FORCE)
endif()

# BUILD_TYPE ==> LIBCELLML_BUILD_TYPE
set(_PARAM_ANNOTATION "Choose the type of build, options are: None(CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release RelWithDebInfo MinSizeRel.")
set(LIBCELLML_BUILD_TYPE "Debug" CACHE STRING ${_PARAM_ANNOTATION})
if(BUILD_TYPE)
  set(LIBCELLML_BUILD_TYPE ${BUILD_TYPE} CACHE STRING ${_PARAM_ANNOTATION} FORCE)
endif()
if(LIBCELLML_MEMCHECK OR LIBCELLML_COVERAGE)
  set(LIBCELLML_BUILD_TYPE "Debug" CACHE STRING ${_PARAM_ANNOTATION} FORCE)
endif()

# INSTALL_PREFIX ==> LIBCELLML_INSTALL_PREFIX
set(_PARAM_ANNOTATION "Install path prefix, prepended onto install directories.")
set(LIBCELLML_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX} CACHE STRING ${_PARAM_ANNOTATION})
if(INSTALL_PREFIX)
  set(LIBCELLML_INSTALL_PREFIX ${INSTALL_PREFIX} CACHE STRING ${_PARAM_ANNOTATION} FORCE)
endif()

# BUILD_SHARED ==> LIBCELLML_BUILD_SHARED
set(_PARAM_ANNOTATION "Build shared libraries (so, dylib, DLLs).")
set(LIBCELLML_BUILD_SHARED ON CACHE BOOL ${_PARAM_ANNOTATION})
if(BUILD_SHARED)
  set(LIBCELLML_BUILD_SHARED ${BUILD_SHARED} CACHE BOOL ${_PARAM_ANNOTATION} FORCE)
endif()

# Keep the GUI tidy.
internalise_cmake_variables()
hide_distracting_variables()

# Turn on the ability to create folders to organize projects (.vcproj)
# It creates "CMakePredefinedTargets" folder by default and adds CMake
# defined projects like INSTALL.vcproj and ZERO_CHECK.vcproj
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# cellml library target
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src)

if (LIBCELLML_UNIT_TESTS)
  # enable testing here so that we can make use of the 'test' target
  enable_testing()
  add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/tests)
endif()

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/docs)

