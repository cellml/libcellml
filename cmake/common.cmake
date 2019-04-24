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
  mark_as_advanced(CMAKE_CONFIGURATION_TYPES)
  mark_as_advanced(CMAKE_CODEBLOCKS_EXECUTABLE)
  mark_as_advanced(QT_QMAKE_EXECUTABLE)
  if(APPLE)
    mark_as_advanced(CMAKE_OSX_ARCHITECTURES)
    mark_as_advanced(CMAKE_OSX_DEPLOYMENT_TARGET)
    mark_as_advanced(CMAKE_OSX_SYSROOT)
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
  if(   "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang"
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
      -Wno-gnu-zero-variadic-macro-arguments
      -Wno-missing-prototypes
      -Wno-newline-eof
      -Wno-padded
      -Wno-reserved-id-macro
      -Wno-switch-enum
      -Wno-unused-macros
      -Wno-used-but-marked-unused
    )

  if(NOT "${_TARGET}" STREQUAL "cellml")
    list(APPEND _COMPILE_OPTIONS
      --system-header-prefix=gtest/
    )
  endif()

    set_target_properties(${_TARGET} PROPERTIES
      COMPILE_OPTIONS "${_COMPILE_OPTIONS}"
    )
  endif()

  if(CLANG_TIDY_EXE)
    if("${_TARGET}" STREQUAL "cellml")
      set(_CPPCOREGUIDELINES_PRO_TYPE_VARARG cppcoreguidelines-pro-type-vararg)
      set(_CPPCOREGUIDELINES_SPECIAL_MEMBER_FUNCTIONS cppcoreguidelines-special-member-functions)
      set(_HICPP_SPECIAL_MEMBER_FUNCTIONS hicpp-special-member-functions)
      set(_HICPP_VARARG hicpp-vararg)
    endif()

    # The full list of Clang-Tidy checks can be found at
    # https://clang.llvm.org/extra/clang-tidy/checks/list.html
    set(_CLANG_TIDY_WARNINGS
      -*
#      abseil-*
#      android-*
#      boost-*
      bugprone-*
#      cert-*
      cppcoreguidelines-avoid-c-arrays
      cppcoreguidelines-avoid-goto
#      cppcoreguidelines-avoid-magic-numbers
      cppcoreguidelines-c-copy-assignment-signature
      cppcoreguidelines-explicit-virtual-functions
      cppcoreguidelines-interfaces-global-init
      cppcoreguidelines-macro-usage
      cppcoreguidelines-narrowing-conversions
      cppcoreguidelines-no-malloc
      cppcoreguidelines-non-private-member-variables-in-classes
#      cppcoreguidelines-owning-memory
      cppcoreguidelines-pro-bounds-array-to-pointer-decay
      cppcoreguidelines-pro-bounds-constant-array-index
      cppcoreguidelines-pro-bounds-pointer-arithmetic
      cppcoreguidelines-pro-type-const-cast
      cppcoreguidelines-pro-type-cstyle-cast
      cppcoreguidelines-pro-type-member-init
#      cppcoreguidelines-pro-type-reinterpret-cast
      cppcoreguidelines-pro-type-static-cast-downcast
      cppcoreguidelines-pro-type-union-access
      ${_CPPCOREGUIDELINES_PRO_TYPE_VARARG}
#      cppcoreguidelines-slicing
      ${_CPPCOREGUIDELINES_SPECIAL_MEMBER_FUNCTIONS}
#      fuchsia-default-arguments
      fuchsia-header-anon-namespaces
      fuchsia-multiple-inheritance
      fuchsia-overloaded-operator
      fuchsia-restrict-system-includes
#      fuchsia-statically-constructed-objects
      fuchsia-trailing-return
      fuchsia-virtual-inheritance
      google-build-explicit-make-pair
      google-build-namespaces
      google-build-using-namespace
      google-default-arguments
      google-explicit-constructor
      google-global-names-in-headers
      google-objc-avoid-throwing-exception
      google-objc-function-naming
      google-objc-global-variable-declaration
      google-readability-avoid-underscore-in-googletest-name
      google-readability-braces-around-statements
      google-readability-casting
      google-readability-function-size
      google-readability-namespace-comments
#      google-readability-todo
      google-runtime-int
      google-runtime-operator
#      google-runtime-references
      hicpp-avoid-c-arrays
      hicpp-avoid-goto
      hicpp-braces-around-statements
      hicpp-deprecated-headers
      hicpp-exception-baseclass
      hicpp-explicit-conversions
      hicpp-function-size
      hicpp-invalid-access-moved
      hicpp-member-init
      hicpp-move-const-arg
      hicpp-multiway-paths-covered
      hicpp-named-parameter
      hicpp-new-delete-operators
      hicpp-no-array-decay
      hicpp-no-assembler
      hicpp-no-malloc
      hicpp-noexcept-move
      hicpp-signed-bitwise
      ${_HICPP_SPECIAL_MEMBER_FUNCTIONS}
      hicpp-static-assert
      hicpp-undelegated-constructor
      hicpp-uppercase-literal-suffix
      hicpp-use-auto
      hicpp-use-emplace
      hicpp-use-equals-default
      hicpp-use-equals-delete
      hicpp-use-noexcept
      hicpp-use-nullptr
      hicpp-use-override
      ${_HICPP_VARARG}
      llvm-*
      misc-definitions-in-headers
      misc-misplaced-const
      misc-new-delete-overloads
      misc-non-copyable-objects
#      misc-non-private-member-variables-in-classes
      misc-redundant-expression
      misc-static-assert
      misc-throw-by-value-catch-by-reference
      misc-unconventional-assign-operator
      misc-uniqueptr-reset-release
      misc-unused-alias-decls
      misc-unused-parameters
      misc-unused-using-decls
      modernize-*
#      mpi-*
#      objc-*
      performance-*
      readability-avoid-const-params-in-decls
      readability-braces-around-statements
      readability-const-return-type
      readability-container-size-empty
      readability-delete-null-pointer
      readability-deleted-default
      readability-else-after-return
      readability-function-size
      readability-identifier-naming
      readability-implicit-bool-conversion
      readability-inconsistent-declaration-parameter-name
      readability-isolate-declaration
#      readability-magic-numbers
      readability-misleading-indentation
      readability-misplaced-array-index
      readability-named-parameter
      readability-non-const-parameter
      readability-redundant-control-flow
      readability-redundant-declaration
      readability-redundant-function-ptr-dereference
      readability-redundant-member-init
      readability-redundant-preprocessor
      readability-redundant-smartptr-get
      readability-redundant-string-cstr
      readability-redundant-string-init
      readability-simplify-boolean-expr
      readability-simplify-subscript-expr
      readability-static-accessed-through-instance
      readability-static-definition-in-anonymous-namespace
      readability-string-compare
      readability-uniqueptr-delete-release
      readability-uppercase-literal-suffix
#      zircon-*
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
