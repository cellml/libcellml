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

function(TARGET_WARNINGS_AS_ERRORS _TARGET)
  set(_COMPILER_WAE)

  set(_GNU_FLAGS_COMPILER_COMPAT "GNU" "AppleClang" "Clang")
  list(FIND _GNU_FLAGS_COMPILER_COMPAT "${CMAKE_CXX_COMPILER_ID}" _INDEX)
  if(${_INDEX} GREATER -1)
    set(_COMPILER_WAE -Wall -W -Werror)
  elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    set(_COMPILER_WAE /W3)
  endif()

  if(_COMPILER_WAE)
    target_compile_options(${_TARGET} PRIVATE ${_COMPILER_WAE})
  endif()
  unset(_COMPILER_WAE)
endfunction()

function(INTERNALISE_CMAKE_VARIABLES)
  # internalise some CMake variables
  set(CMAKE_INSTALL_PREFIX ${LIBCELLML_INSTALL_PREFIX} CACHE INTERNAL "Internalise CMAKE_INSTALL_PREFIX, manipulate via LIBCELLML_INSTALL_PREFIX" FORCE)
  set(CMAKE_BUILD_TYPE ${LIBCELLML_BUILD_TYPE} CACHE INTERNAL "Internalise CMAKE_BUILD_TYPE, manipulate via LIBCELLML_BUILD_TYPE" FORCE)
  set(BUILD_SHARED_LIBS ${LIBCELLML_BUILD_SHARED} CACHE INTERNAL "Internalise BUILD_SHARED_LIBS, manipulate via LIBCELLML_BUILD_SHARED" FORCE)
endfunction()

function(HIDE_DISTRACTING_VARIABLES)
  # Mark cache variables that aren't libCellML configuration variables as advanced
  # to hide them from the user in a CMake GUI.
  mark_as_advanced(CMAKE_CONFIGURATION_TYPES)
  mark_as_advanced(CMAKE_CODEBLOCKS_EXECUTABLE)
  mark_as_advanced(QT_QMAKE_EXECUTABLE)
  if(APPLE)
    mark_as_advanced(CMAKE_OSX_ARCHITECTURES)
    mark_as_advanced(CMAKE_OSX_DEPLOYMENT_TARGET)
    mark_as_advanced(CMAKE_OSX_SYSROOT)
  endif()
  if(WIN32)
    if(LibXml2_FOUND AND HAVE_LIBXML2_CONFIG)
      mark_as_advanced(LibXml2_DIR)
    elseif(LibXml2_FOUND AND NOT HAVE_LIBXML2_CONFIG)
      mark_as_advanced(LIBXML2_INCLUDE_DIR)
      mark_as_advanced(LIBXML2_LIBRARY)
      mark_as_advanced(LIBXML2_XMLLINT_EXECUTABLE)
    endif()
  else()
    mark_as_advanced(pkgcfg_lib_PC_LIBXML_xml2)
  endif()
endfunction()

function(GROUP_SOURCE_TO_DIR_STRUCTURE)
  if(MSVC)
    foreach(_FILE ${ARGN})
      # Basic test for determining if current file is a source file or header file.
      if(${_FILE} MATCHES ".+\.cpp$")
        set(_FILE_PREFIX "Source Files\\")
      else()
        set(_FILE_PREFIX "Header Files\\")
      endif()
      # Get relative path from current source directory or current binary directory.
      if(${_FILE} MATCHES "^${CMAKE_CURRENT_SOURCE_DIR}.+")
        file(RELATIVE_PATH _FILE_RELATIVE_PATH "${CMAKE_CURRENT_SOURCE_DIR}" ${_FILE})
      else()
        file(RELATIVE_PATH _FILE_RELATIVE_PATH "${CMAKE_CURRENT_BINARY_DIR}" ${_FILE})
        # Assume all files in the current binary directory are generated header files!
        set(_FILE_PREFIX "Generated Header Files\\")
      endif()
      get_filename_component(_FILE_GROUP ${_FILE_RELATIVE_PATH} DIRECTORY)
      if(_FILE_GROUP)
        string(REPLACE "/" "\\" _FILE_GROUP ${_FILE_GROUP})
      endif()
      source_group("${_FILE_PREFIX}${_FILE_GROUP}" FILES "${_FILE}")
    endforeach()
  endif()
endfunction()

function(CONFIGURE_CLANG_AND_CLANG_TIDY_SETTINGS _TARGET)
  if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang"
     OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "AppleClang")
    # The full list of diagnostic flags in Clang can be found at
    # https://clang.llvm.org/docs/DiagnosticsReference.html
    set(_COMPILE_OPTIONS
      -Weverything
      -Wno-c++98-compat
      -Wno-c++98-compat-pedantic
      -Wno-documentation
      -Wno-documentation-unknown-command
      -Wno-exit-time-destructors
      -Wno-global-constructors
      -Wno-missing-prototypes
      -Wno-padded
    )

    if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "AppleClang" AND
        ${CMAKE_CXX_COMPILER_VERSION} VERSION_GREATER_EQUAL 7.0.0)
      list(APPEND _COMPILE_OPTIONS
        -Wno-reserved-id-macro
      )
    endif()

    if(NOT "${_TARGET}" STREQUAL "cellml")
      list(APPEND _COMPILE_OPTIONS
        --system-header-prefix=gtest/
      )
    endif()

    set_target_properties(${_TARGET} PROPERTIES
      COMPILE_OPTIONS "${_COMPILE_OPTIONS}"
    )
  endif()

  if(CLANG_TIDY_AVAILABLE)
    if(NOT "${_TARGET}" STREQUAL "cellml")
        set(_NO_CPPCOREGUIDELINES_PRO_TYPE_VARARG -cppcoreguidelines-pro-type-vararg)
        set(_NO_CPPCOREGUIDELINES_SPECIAL_MEMBER_FUNCTIONS -cppcoreguidelines-special-member-functions)
        set(_NO_HICPP_SPECIAL_MEMBER_FUNCTIONS -hicpp-special-member-functions)
        set(_NO_HICPP_VARARG -hicpp-vararg)
    endif()

    # The full list of Clang-Tidy checks can be found at
    # https://clang.llvm.org/extra/clang-tidy/checks/list.html
    set(_CLANG_TIDY_WARNINGS
      -*
      bugprone-*
      cert-*
      -cert-err58-cpp
      cppcoreguidelines-*
      -cppcoreguidelines-avoid-magic-numbers
      -cppcoreguidelines-owning-memory
      -cppcoreguidelines-pro-type-reinterpret-cast
      ${_NO_CPPCOREGUIDELINES_PRO_TYPE_VARARG}
      -cppcoreguidelines-slicing
      ${_NO_CPPCOREGUIDELINES_SPECIAL_MEMBER_FUNCTIONS}
      fuchsia-*
      -fuchsia-default-arguments
      -fuchsia-statically-constructed-objects
      google-*
      -google-readability-todo
      -google-runtime-references
      hicpp-*
      ${_NO_HICPP_SPECIAL_MEMBER_FUNCTIONS}
      ${_NO_HICPP_VARARG}
      llvm-*
      misc-*
      -misc-non-private-member-variables-in-classes
      modernize-*
      -modernize-raw-string-literal
      performance-*
      -performance-inefficient-string-concatenation
      readability-*
      -readability-magic-numbers
    )
    string(REPLACE ";" ","
           _CLANG_TIDY_WARNINGS "${_CLANG_TIDY_WARNINGS}")
    if(LIBCELLML_TREAT_WARNINGS_AS_ERRORS)
      set(_CLANG_TIDY_WARNINGS_AS_ERRORS ";-warnings-as-errors=${_CLANG_TIDY_WARNINGS}")
    endif()
    set_target_properties(${_TARGET} PROPERTIES
      CXX_CLANG_TIDY "${CLANG_TIDY_EXE};-checks=${_CLANG_TIDY_WARNINGS}${_CLANG_TIDY_WARNINGS_AS_ERRORS}"
    )
  endif()
endfunction()
