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

find_package(LibXml2 CONFIG QUIET)
if(NOT LibXml2_FOUND)
  find_package(LibXml2 REQUIRED)
  set(_LibXml2_FIND_REPORTED TRUE CACHE INTERNAL "Flag for reporting on what LibXml2 was found.")
endif()

set(_libxml2_target "")

if(TARGET LibXml2::LibXml2)
  set(_libxml2_target LibXml2::LibXml2)
elseif(TARGET LibXml2)
  set(_libxml2_target LibXml2)
elseif(TARGET xml2)
  set(_libxml2_target xml2)
endif()

if(NOT _libxml2_target)
  if(DEFINED LIBXML2_LIBRARIES AND DEFINED LIBXML2_INCLUDE_DIRS)
    message(WARNING "Creating legacy target for LibXml2. This is not ideal.")
    add_library(_libxml2_legacy INTERFACE)
    target_include_directories(_libxml2_legacy INTERFACE
      ${LIBXML2_INCLUDE_DIRS}
    )
    target_link_libraries(_libxml2_legacy INTERFACE
      ${LIBXML2_LIBRARIES}
    )
    set(_libxml2_defs "${LIBXML2_DEFINITIONS}")
    if(_libxml2_defs)
      list(TRANSFORM _libxml2_defs REPLACE "^-D" "")
      target_compile_definitions(_libxml2_legacy INTERFACE ${_libxml2_defs})
    endif()
    set(_libxml2_target _libxml2_legacy)
  else()
    message(FATAL_ERROR "LibXml2 found but no targets or usable variables.")
  endif()
endif()

if(NOT TARGET LibXml2::LibXml2)
  add_library(LibXml2::LibXml2 INTERFACE IMPORTED)
  target_link_libraries(LibXml2::LibXml2 INTERFACE
    ${_libxml2_target}
  )
endif()

set(_libxml2_includes "")
set(_libxml2_libs "")
set(_libxml2_defs "")

get_target_property(_tmp LibXml2::LibXml2 INTERFACE_INCLUDE_DIRECTORIES)
if(_tmp)
  set(_libxml2_includes "${_tmp}")
  string(REPLACE ";" "|" _LIBXML2_INCLUDE_DIRS_ESCAPED "${_libxml2_includes}")
endif()

get_target_property(_tmp LibXml2::LibXml2 INTERFACE_LINK_LIBRARIES)
if(_tmp)
  set(_libxml2_libs "${_tmp}")
  string(REPLACE ";" "|" _LIBXML2_LIBRARIES_ESCAPED "${_libxml2_libs}")
endif()

get_target_property(_tmp LibXml2::LibXml2 INTERFACE_COMPILE_DEFINITIONS)
if(_tmp)
  set(_libxml2_defs "${_tmp}")
  list(TRANSFORM _libxml2_defs REPLACE "^-D" "")
  string(REPLACE ";" "|" _LIBXML2_DEFINITIONS_ESCAPED "${_libxml2_defs}")
endif()

if(NOT ZLIB_FOUND)
  find_package(ZLIB CONFIG QUIET)
  if(NOT ZLIB_FOUND)
    find_package(ZLIB REQUIRED)
    set(_ZLIB_FIND_REPORTED TRUE CACHE INTERNAL "Flag for reporting on what ZLIB was found.")
  endif()
endif()

set(_zlib_target "")

if(TARGET ZLIB::ZLIB)
  set(_zlib_target ZLIB::ZLIB)
elseif(TARGET z)
  set(_zlib_target z)
endif()

if(NOT _zlib_target)
  add_library(_zlib_legacy INTERFACE)
  target_include_directories(_zlib_legacy INTERFACE ${ZLIB_INCLUDE_DIRS})
  target_link_libraries(_zlib_legacy INTERFACE ${ZLIB_LIBRARIES})
  set(_zlib_target _zlib_legacy)
endif()

if(NOT TARGET ZLIB::ZLIB)
  add_library(ZLIB::ZLIB INTERFACE IMPORTED)
  target_link_libraries(ZLIB::ZLIB INTERFACE ${_zlib_target})
endif()
get_target_property(ZLIB_TARGET_TYPE ZLIB::ZLIB TYPE)
get_target_property(LIBXML2_TARGET_TYPE LibXml2::LibXml2 TYPE)

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

message(STATUS "about to call test_libxml2_const_error_structured_error_callback:")
test_libxml2_const_error_structured_error_callback()
message(STATUS "finished call test_libxml2_const_error_structured_error_callback:")

if(CONST_ERROR_STRUCTURED_ERROR_CALLBACK)
  set(CONST_ERROR_STRUCTURED_ERROR_CALLBACK_TYPE "const xmlError *")
else()
  set(CONST_ERROR_STRUCTURED_ERROR_CALLBACK_TYPE "xmlErrorPtr")
endif()
