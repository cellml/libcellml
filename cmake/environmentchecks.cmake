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
# limitations under the License.

include(CheckCXXCompilerFlag)
include(TestUndefinedSymbolsAllowed)
include(TestLibXml2ConstErrorStructuredErrorCallback)

get_property(IS_MULTI_CONFIG GLOBAL PROPERTY GENERATOR_IS_MULTI_CONFIG)

find_program(GIT_EXE NAMES ${PRFERRED_GIT_NAMES} git)

# Need to change a lot of what we would normally do as it doesn't apply to Emscripten.
if (EMSCRIPTEN)
    find_program(NODE_EXE NAMES ${PREFERRED_NODE_NAMES} node)
    find_program(NPM_EXE NAMES ${PREFERRED_NPM_NAMES} npm)
else ()
  if(CMAKE_VERSION VERSION_GREATER_EQUAL 3.18 AND CMAKE_SYSTEM_NAME STREQUAL "Linux")
    set(_FIND_PYTHON_DEVELOPMENT_TYPE Development.Module)
    set(FIND_PYTHON_DEVELOPMENT_MODULE TRUE)
  else()
    set(_FIND_PYTHON_DEVELOPMENT_TYPE Development)
  endif()

  test_undefined_symbols_allowed()

  find_package(Python ${PREFERRED_PYTHON_VERSION} COMPONENTS Interpreter ${_FIND_PYTHON_DEVELOPMENT_TYPE})

  find_program(BUILDCACHE_EXE buildcache)
  if(NOT BUILDCACHE_EXE)
    if(MSVC)
      find_program(CLCACHE_EXE clcache)
    else()
      find_program(CCACHE_EXE ccache)
    endif()
  endif()
  find_program(CLANG_FORMAT_EXE NAMES ${PREFERRED_CLANG_FORMAT_NAMES} clang-format)
  find_program(CLANG_TIDY_EXE NAMES ${PREFERRED_CLANG_TIDY_NAMES} clang-tidy)
  find_program(DOT_EXE NAMES ${PREFERRED_FIND_NAMES} dot)
  find_program(FIND_EXE NAMES ${PREFERRED_FIND_NAMES} find)
  find_program(GCOV_EXE NAMES ${PREFERRED_GCOV_NAMES} gcov)
  find_program(LLVM_COV_EXE NAMES ${PREFERRED_LLVM_COV_NAMES} llvm-cov HINTS ${LLVM_BIN_DIR} ENV PATH /Library/Developer/CommandLineTools/usr/bin/)
  find_program(LLVM_PROFDATA_EXE NAMES ${PREFERRED_LLVM_PROFDATA_NAMES} llvm-profdata HINTS ${LLVM_BIN_DIR} ENV PATH /Library/Developer/CommandLineTools/usr/bin/)
  find_program(VALGRIND_EXE NAMES ${PREFERRED_VALGRIND_NAMES} valgrind)
  find_program(INSTALL_NAME_TOOL_EXE NAMES ${PREFERRED_INSTALL_NAME_TOOL_NAMES} install_name_tool)

  if(Python_Interpreter_FOUND)
    if(NOT DEFINED TEST_COVERAGE_RESULT)
      set(TEST_COVERAGE_RESULT -1 CACHE INTERNAL "Result of testing for Python coverage.")
      message(STATUS "Performing Test HAVE_COVERAGE")
      get_filename_component(PYTHON_DIR ${Python_EXECUTABLE} DIRECTORY)
      execute_process(COMMAND ${Python_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/cmake/python_package_check.py exclude-until-coverage-plugin
        RESULT_VARIABLE TEST_COVERAGE_RESULT OUTPUT_QUIET ERROR_QUIET)
      if(TEST_COVERAGE_RESULT EQUAL 0)
        set(HAVE_COVERAGE TRUE)
        message(STATUS "Performing Test HAVE_COVERAGE - Success")
      else()
        set(HAVE_COVERAGE FALSE)
        message(STATUS "Performing Test HAVE_COVERAGE - Failed")
      endif()
    endif()
  endif()

  find_package(Doxygen)
  find_package(Sphinx)
  find_package(SWIG 3)

  set(_ORIGINAL_CMAKE_REQUIRED_FLAGS ${CMAKE_REQUIRED_FLAGS})

  set(CMAKE_REQUIRED_FLAGS -fprofile-instr-generate)
  check_cxx_compiler_flag("-fprofile-instr-generate -fcoverage-mapping" LLVM_COVERAGE_COMPILER_FLAGS_OK)

  set(CMAKE_REQUIRED_FLAGS "-fprofile-arcs -ftest-coverage")
  check_cxx_compiler_flag("-fprofile-arcs -ftest-coverage" GCC_COVERAGE_COMPILER_FLAGS_OK)

  set(CMAKE_REQUIRED_FLAGS ${_ORIGINAL_CMAKE_REQUIRED_FLAGS})

  if(MSVC)
    mark_as_advanced(CLCACHE_EXE)
  else()
    mark_as_advanced(CCACHE_EXE)
  endif()

  mark_as_advanced(
    BUILDCACHE_EXE
    CLANG_TIDY_EXE
    CLANG_FORMAT_EXE
    DOT_EXE
    FIND_EXE
    GCC_COVERAGE_COMPILER_FLAGS_OK
    GCOV_EXE
    GIT_EXE
    INSTALL_NAME_TOOL_EXE
    LLVM_COV_EXE
    LLVM_COVERAGE_COMPILER_FLAGS_OK
    LLVM_PROFDATA_EXE
    SWIG_EXECUTABLE
    VALGRIND_EXE
  )
endif()

# Find libxml2
set(HAVE_LIBXML2_CONFIG FALSE)
# We want to use config mode for finding libXml2.
# This is especially important on Windows with Visual Studio.
# To do this we need to have two find_package calls and explicitly state that
# we wish to use Config mode in the first call.  Finding LibXml2 in config mode
# is the preferred method so we will try this first quietly.
#
# This does change how we get information about include paths and such so we
# need to track how we found LibXml2.
find_package(LibXml2 CONFIG QUIET)
if(LibXml2_FOUND)
  if(TARGET z)
    set(HAVE_ZLIB_TARGET TRUE)
    get_target_property(ZLIB_TARGET_TYPE z TYPE)
  else()
    find_package(ZLIB CONFIG QUIET)
    if(ZLIB_FOUND)
      if(TARGET z)
        set(HAVE_ZLIB_TARGET TRUE)
        get_target_property(ZLIB_TARGET_TYPE z TYPE)
      endif()
    else()
      find_package(ZLIB REQUIRED)
      set(_ZLIB_FIND_REPORTED TRUE CACHE INTERNAL "Flag for reporting on what ZLIB was found.")
    endif()
  endif()
  set(HAVE_LIBXML2_CONFIG TRUE)
  # Different versions of LibXml2 have different names for the library target.
  # We try and capture that here.
  if(TARGET xml2)
    set(LIBXML2_TARGET_NAME xml2)
  elseif(TARGET LibXml2)
    set(LIBXML2_TARGET_NAME LibXml2)
  elseif(TARGET LibXml2::LibXml2)
    set(LIBXML2_TARGET_NAME LibXml2::LibXml2)
  else()
    message(FATAL_ERROR "FindLibXml2: Found configuration file for LibXml2 but could not determine a target name from it.")
  endif()
  get_target_property(LIBXML2_TARGET_TYPE ${LIBXML2_TARGET_NAME} TYPE)
  set(HAVE_LIBXML2_TARGET TRUE)
  # Clear out GUI variables created in module search mode.
  foreach(_XML2_VAR LIBXML2_LIBRARY LIBXML2_INCLUDE_DIR LIBXML2_XMLLINT_EXECUTABLE)
    if(DEFINED ${_XML2_VAR} AND NOT ${${_XML2_VAR}})
      unset(${_XML2_VAR} CACHE)
    endif()
  endforeach()
else()
  find_package(LibXml2 REQUIRED)
  set(_LibXml2_FIND_REPORTED TRUE CACHE INTERNAL "Flag for reporting on what LibXml2 was found.")
  if(TARGET z)
    set(HAVE_ZLIB_TARGET TRUE)
    get_target_property(ZLIB_TARGET_TYPE z TYPE)
  else()
    find_package(ZLIB REQUIRED)
    set(_ZLIB_FIND_REPORTED TRUE CACHE INTERNAL "Flag for reporting on what ZLIB was found.")
  endif()
  if(LibXml2_FOUND)
    # Clear out GUI variable created in config search mode.
    unset(LibXml2_DIR CACHE)
  endif()
endif()

if(NOT DEFINED _LibXml2_FIND_REPORTED)
  set(_LibXml2_FIND_REPORTED TRUE CACHE INTERNAL "Flag for reporting on what LibXml2 was found.")
  message(STATUS "Found LibXml2: ${LIBXML2_LIBRARIES} (found version \"${LIBXML2_VERSION_STRING}\").")
endif()

if(NOT DEFINED _ZLIB_FIND_REPORTED)
  set(_ZLIB_FIND_REPORTED TRUE CACHE INTERNAL "Flag for reporting on what ZLIB was found.")
  if(CMAKE_VERSION VERSION_GREATER_EQUAL 3.26)
    set(ZLIB_VERSION_STRING ${ZLIB_VERSION})
  endif()
  message(STATUS "Found ZLIB: ${ZLIB_LIBRARIES} (found version \"${ZLIB_VERSION_STRING}\").")
endif()

if(BUILDCACHE_EXE OR CLCACHE_EXE OR CCACHE_EXE)
  set(COMPILER_CACHE_AVAILABLE TRUE CACHE INTERNAL "Executable required to cache compilations.")
endif()

if(CLANG_FORMAT_EXE)
  set(CLANG_FORMAT_VERSION_MINIMUM 11)
  execute_process(COMMAND ${CLANG_FORMAT_EXE} -version
                  OUTPUT_VARIABLE CLANG_FORMAT_VERSION
                  ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE)
  string(REGEX REPLACE "^.*clang-format version ([.0-9]+).*$" "\\1" CLANG_FORMAT_VERSION "${CLANG_FORMAT_VERSION}")

  if(CLANG_FORMAT_VERSION VERSION_LESS CLANG_FORMAT_VERSION_MINIMUM)
    message(STATUS "ClangFormat ${CLANG_FORMAT_VERSION} was found, but version ${CLANG_FORMAT_VERSION_MINIMUM}+ is needed to use ClangFormat")
  else()
    set(CLANG_FORMAT_AVAILABLE TRUE CACHE INTERNAL "Executable required to use ClangFormat is available.")

    if(GIT_EXE)
      set(CLANG_FORMAT_TESTING_AVAILABLE TRUE CACHE INTERNAL "Executables required to run the ClangFormat test are available.")
    endif()
  endif()
endif()

if(IS_MULTI_CONFIG)
  set(CONFIG_DIR_SUFFIX "/$<CONFIG>")
endif()

if(CLANG_TIDY_EXE)
  set(CLANG_TIDY_AVAILABLE TRUE CACHE INTERNAL "Executable required to perform static analysis is available.")
endif()

if(FIND_EXE AND GCOV_EXE AND Python_Interpreter_FOUND AND GCC_COVERAGE_COMPILER_FLAGS_OK)
  set(COVERAGE_TESTING_AVAILABLE TRUE CACHE INTERNAL "Executables required to run the coverage testing are available.")
endif()

if(SWIG_EXECUTABLE)
  set(BINDINGS_AVAILABLE TRUE CACHE INTERNAL "Executable required to generate bindings is available.")
endif()

if(BINDINGS_AVAILABLE AND (Python_Development.Module_FOUND OR Python_Development_FOUND))
  set(PYTHON_BINDINGS_AVAILABLE TRUE CACHE INTERNAL "Requirements for creating Python bindings are available.")
endif()

if(VALGRIND_EXE AND Python_Interpreter_FOUND)
  set(VALGRIND_TESTING_AVAILABLE TRUE CACHE INTERNAL "Executable required to run valgrind testing is available.")
endif()

if(LLVM_PROFDATA_EXE AND LLVM_COV_EXE AND FIND_EXE AND LLVM_COVERAGE_COMPILER_FLAGS_OK)
  set(LLVM_COVERAGE_TESTING_AVAILABLE TRUE CACHE INTERNAL "Executables required to run the llvm coverage testing are available.")
endif()

if(INSTALL_NAME_TOOL_EXE)
  set(INSTALL_NAME_TOOL_AVAILABLE TRUE CACHE INTERNAL "Executable required for manipulating dynamic library paths is available.")
endif()

if(HAVE_COVERAGE)
  set(PYTHON_COVERAGE_TESTING_AVAILABLE TRUE CACHE INTERNAL "Module required to run Python coverage testing is available.")
endif()

if(WIN32 AND NOT EMSCRIPTEN)
  find_program(MAKENSIS_EXE NAMES ${PREFERRED_NSIS_NAMES} makensis
    HINTS "C:/Program\ Files/NSIS/" "C:/Program\ Files\ (x86)/NSIS/")
  mark_as_advanced(MAKENSIS_EXE)
  if(MAKENSIS_EXE)
    set(NSIS_FOUND TRUE)
  else()
    set(NSIS_FOUND FALSE)
  endif()
endif()

if(EMSCRIPTEN AND NODE_EXE AND NPM_EXE)
    set(JAVASCRIPT_BINDINGS_TESTING_AVAILABLE TRUE CACHE INTERNAL "Executables required to run the javascript bindings tests are available.")
endif()

test_libxml2_const_error_structured_error_callback()

if(CONST_ERROR_STRUCTURED_ERROR_CALLBACK)
  set(CONST_ERROR_STRUCTURED_ERROR_CALLBACK_TYPE "const xmlError *")
else()
  set(CONST_ERROR_STRUCTURED_ERROR_CALLBACK_TYPE "xmlErrorPtr")
endif()
