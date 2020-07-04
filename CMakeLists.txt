# Copyright libCellML Contributors
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

cmake_minimum_required(VERSION 3.10.2)

set(PROJECT_NAME libCellML)
project(${PROJECT_NAME} VERSION 0.2.0 LANGUAGES CXX)

# Set policies that affect the build.
if(POLICY CMP0078)
  cmake_policy(SET CMP0078 NEW)
endif()
if(POLICY CMP0086)
  cmake_policy(SET CMP0086 NEW)
endif()

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include(common)
include(environmentchecks)

# Use the following variables when configuring the build from the command line to
# set the corresponding cache variables.

# CLANG_TIDY ==> LIBCELLML_CLANG_TIDY
set(_PARAM_ANNOTATION "Enable Clang-Tidy.")
if(CLANG_TIDY_AVAILABLE)
  set(LIBCELLML_CLANG_TIDY ON CACHE BOOL ${_PARAM_ANNOTATION})
endif()
if(DEFINED CLANG_TIDY AND CLANG_TIDY_AVAILABLE)
  set(LIBCELLML_CLANG_TIDY "${CLANG_TIDY}" CACHE BOOL ${_PARAM_ANNOTATION} FORCE)
elseif(CLANG_TIDY)
  message(WARNING "LLVM coverage testing requested but llvm-profdata or llvm-cov not found!")
endif()
unset(CLANG_TIDY CACHE)

# COVERAGE ==> LIBCELLML_COVERAGE
set(_PARAM_ANNOTATION "Enable coverage testing.")
if(COVERAGE_TESTING_AVAILABLE)
  set(LIBCELLML_COVERAGE ON CACHE BOOL ${_PARAM_ANNOTATION})
endif()
if(DEFINED COVERAGE AND COVERAGE_TESTING_AVAILABLE)
  set(LIBCELLML_COVERAGE "${COVERAGE}" CACHE BOOL ${_PARAM_ANNOTATION} FORCE)
elseif(COVERAGE)
  message(WARNING "Coverage testing requested but gcov or its requirements not found!")
endif()
unset(COVERAGE CACHE)

# LLVM_COVERAGE ==> LIBCELLML_LLVM_COVERAGE
set(_PARAM_ANNOTATION "Enable LLVM coverage testing.")
if(LLVM_COVERAGE_TESTING_AVAILABLE)
  set(LIBCELLML_LLVM_COVERAGE ON CACHE BOOL ${_PARAM_ANNOTATION})
endif()
if(DEFINED LLVM_COVERAGE AND LLVM_COVERAGE_TESTING_AVAILABLE)
  set(LIBCELLML_LLVM_COVERAGE "${LLVM_COVERAGE}" CACHE BOOL ${_PARAM_ANNOTATION} FORCE)
elseif(LLVM_COVERAGE)
  message(WARNING "LLVM coverage testing requested but llvm-profdata or llvm-cov not found!")
endif()
unset(LLVM_COVERAGE CACHE)

# MEMCHECK ==> LIBCELLML_MEMCHECK
set(_PARAM_ANNOTATION "Enable memcheck testing.")
if(VALGRIND_TESTING_AVAILABLE)
  set(LIBCELLML_MEMCHECK ON CACHE BOOL ${_PARAM_ANNOTATION})
endif()
if(DEFINED MEMCHECK AND VALGRIND_TESTING_AVAILABLE)
  set(LIBCELLML_MEMCHECK "${MEMCHECK}" CACHE BOOL ${_PARAM_ANNOTATION} FORCE)
elseif(MEMCHECK)
  message(WARNING "Memcheck testing requested but valgrind or its requirements not found!")
endif()
unset(MEMCHECK CACHE)

# BINDINGS_PYTHON ==> LIBCELLML_BINDINGS_PYTHON
set(_PARAM_ANNOTATION "Build Python wrappers.")
if(BINDINGS_AVAILABLE)
  set(LIBCELLML_BINDINGS_PYTHON ON CACHE BOOL ${_PARAM_ANNOTATION})
endif()
if(DEFINED BINDINGS_PYTHON AND BINDINGS_AVAILABLE)
  set(LIBCELLML_BINDINGS_PYTHON "${BINDINGS_PYTHON}" CACHE BOOL ${_PARAM_ANNOTATION} FORCE)
endif()
unset(BINDINGS_PYTHON CACHE)

# UNIT_TESTS ==> LIBCELLML_UNIT_TESTS
set(_PARAM_ANNOTATION "Enable libCellML tests.")
set(LIBCELLML_UNIT_TESTS ON CACHE BOOL ${_PARAM_ANNOTATION})
if(DEFINED UNIT_TESTS)
  set(LIBCELLML_UNIT_TESTS "${UNIT_TESTS}" CACHE BOOL ${_PARAM_ANNOTATION} FORCE)
endif()
unset(UNIT_TESTS CACHE)

if(LIBCELLML_COVERAGE OR LIBCELLML_MEMCHECK)
  if(NOT LIBCELLML_UNIT_TESTS)
    message(SEND_ERROR "Configuration confusion:
      Memchecking or coverage testing has been requested but unit tests have not.
      This is not possible, please change the configuration to clear this condition.
      ")
  endif()
endif()

# TWAE ==> LIBCELLML_TREAT_WARNINGS_AS_ERRORS -- Note: This excludes third party code, where warnings are never treated as errors.
set(_PARAM_ANNOTATION "Treat warnings as errors, this setting applies only to compilation units built by this project.")
set(LIBCELLML_TREAT_WARNINGS_AS_ERRORS ON CACHE BOOL ${_PARAM_ANNOTATION})
if(DEFINED TWAE)
  set(LIBCELLML_TREAT_WARNINGS_AS_ERRORS "${TWAE}" CACHE BOOL ${_PARAM_ANNOTATION} FORCE)
endif()
unset(TWAE CACHE)

# BUILD_TYPE ==> LIBCELLML_BUILD_TYPE
if(NOT IS_MULTI_CONFIG)
  set(_PARAM_ANNOTATION "Choose the type of build, options are: None(CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release RelWithDebInfo MinSizeRel.")
  set(LIBCELLML_BUILD_TYPE "Debug" CACHE STRING ${_PARAM_ANNOTATION})
  if(DEFINED BUILD_TYPE)
    set(LIBCELLML_BUILD_TYPE ${BUILD_TYPE} CACHE STRING ${_PARAM_ANNOTATION} FORCE)
  endif()
endif()
unset(BUILD_TYPE CACHE)
if(LIBCELLML_MEMCHECK)
  if(LIBCELLML_BUILD_TYPE STREQUAL "Release")
    message(SEND_ERROR "Configuration confusion:
      Release build requested but memchecking has also been requested.
      This is not possible, please change the configuration to clear this condition.
      ")
  endif()
endif()

# INSTALL_PREFIX ==> LIBCELLML_INSTALL_PREFIX
set(_PARAM_ANNOTATION "Install path prefix, prepended onto install directories.")
set(LIBCELLML_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX} CACHE PATH ${_PARAM_ANNOTATION})
if(DEFINED INSTALL_PREFIX)
  set(LIBCELLML_INSTALL_PREFIX ${INSTALL_PREFIX} CACHE PATH ${_PARAM_ANNOTATION} FORCE)
endif()
unset(INSTALL_PREFIX CACHE)

# BUILD_SHARED ==> LIBCELLML_BUILD_SHARED
set(_PARAM_ANNOTATION "Build shared libraries (so, dylib, DLLs).")
set(LIBCELLML_BUILD_SHARED ON CACHE BOOL ${_PARAM_ANNOTATION})
if(DEFINED BUILD_SHARED)
  set(LIBCELLML_BUILD_SHARED ${BUILD_SHARED} CACHE BOOL ${_PARAM_ANNOTATION} FORCE)
endif()
unset(BUILD_SHARED CACHE)

# Uninstall target
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/cmake/cmake_uninstall.in.cmake"
               "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
               IMMEDIATE @ONLY)
add_custom_target(uninstall COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)

# Keep the GUI tidy.
internalise_cmake_variables()
hide_distracting_variables()

# Turn on the ability to create folders to organize projects (.vcproj)
# It creates "CMakePredefinedTargets" folder by default and adds CMake
# defined projects like INSTALL.vcproj and ZERO_CHECK.vcproj
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# cellml library target
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src)

if(LIBCELLML_UNIT_TESTS)
  # enable testing here so that we can make use of the 'test' target
  enable_testing()
  add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/tests)
endif()

# Add docs
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/docs)

# Format our code
if(CLANG_FORMAT_EXE)
  set(FILES_TO_FORMAT
    ${API_HEADER_FILES}
    ${MODULE_HEADER_FILES}
    ${SOURCE_FILES}
    ${HEADER_FILES}
    ${CONFIG_FILES}
    ${TESTS_HEADER_FILES}
    ${TESTS_SOURCE_FILES}
  )

  set(CHECK_CODE_FORMATTING_SCRIPT ${CMAKE_CURRENT_BINARY_DIR}/cmake_command_check_code_formatting.cmake)
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/cmake_command_check_code_formatting.in.cmake
    ${CHECK_CODE_FORMATTING_SCRIPT} @ONLY)
  if(CLANG_FORMAT_TESTING_AVAILABLE)
    add_custom_target(test_clang_format
      COMMAND ${CMAKE_COMMAND} -P ${CHECK_CODE_FORMATTING_SCRIPT}
    )
  endif()

  add_custom_target(format_code
    COMMAND ${CLANG_FORMAT_EXE} -i ${FILES_TO_FORMAT}
    COMMENT "Source code has been reformatted by ClangFormat."
  )
endif()

# Add packaging
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/cmake/packaging)
