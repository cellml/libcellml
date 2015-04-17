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

# The version number.
set(LIBCELLML_VERSION_MAJOR 0)
set(LIBCELLML_VERSION_MINOR 1)
set(LIBCELLML_VERSION_PATCH 0)

foreach(VERSION_PART LIBCELLML_VERSION_MAJOR LIBCELLML_VERSION_MINOR LIBCELLML_VERSION_PATCH)
  string(LENGTH ${${VERSION_PART}} VERSION_PART_LENGTH)
  if(VERSION_PART_LENGTH EQUAL 1)
    set(${VERSION_PART}_PAD 0)
  endif()
endforeach()
set(LIBCELLML_LIBRARY_VERSION 0x${LIBCELLML_VERSION_MAJOR_PAD}${LIBCELLML_VERSION_MAJOR}${LIBCELLML_VERSION_MINOR_PAD}${LIBCELLML_VERSION_MINOR}${LIBCELLML_VERSION_PATCH_PAD}${LIBCELLML_VERSION_PATCH})
set(LIBCELLML_LIBRARY_VERSION_STRING "${LIBCELLML_VERSION_MAJOR}.${LIBCELLML_VERSION_MINOR}.${LIBCELLML_VERSION_PATCH}")

set(CELLML_EXPORT_H "${CMAKE_CURRENT_BINARY_DIR}/api/libcellml/libcellml_export.h")
set(LIBCELLML_CONFIG_H "${CMAKE_CURRENT_BINARY_DIR}/libcellml_config.h")
configure_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/configure/libcellml_config.h.in"
  ${LIBCELLML_CONFIG_H}
)

set(SOURCE_FILES
  ${CMAKE_CURRENT_SOURCE_DIR}/version.cpp
)

set(API_HEADER_FILES
  ${CMAKE_CURRENT_SOURCE_DIR}/api/libcellml/version.h
  ${CELLML_EXPORT_H}
)

set(HEADER_FILES
  ${LIBCELLML_CONFIG_H}
)

include(GenerateExportHeader)
add_compiler_export_flags()

add_library(cellml
  ${SOURCE_FILES}
  ${HEADER_FILES}
  ${API_HEADER_FILES}
)

target_include_directories(cellml
  PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/api>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/api>
  $<INSTALL_INTERFACE:include/>
  PRIVATE
  ${CMAKE_CURRENT_BINARY_DIR}
)

if(LIBCELLML_TREAT_WARNINGS_AS_ERRORS)
  target_warnings_as_errors(cellml)
endif()

if(LIBCELLML_COVERAGE)
  set_target_properties(cellml PROPERTIES COMPILE_FLAGS "-fprofile-arcs -ftest-coverage")
  target_link_libraries(cellml gcov)

  # Share some paths with interested parties (tests)
  set(GCOV_ANALYSIS_PATH "${CMAKE_CURRENT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/cellml.dir" PARENT_SCOPE)
  set(GCOV_PREFIX_PATH "${CMAKE_CURRENT_SOURCE_DIR}" PARENT_SCOPE)
  set(GCOV_BUILD_PREFIX_PATH "${CMAKE_CURRENT_BINARY_DIR}" PARENT_SCOPE)
endif()

generate_export_header(cellml EXPORT_FILE_NAME ${CELLML_EXPORT_H} BASE_NAME LIBCELLML)

set_source_files_properties(${CELLML_EXPORT_H} PROPERTIES GENERATED TRUE)

export(TARGETS cellml FILE libcellml-exports.cmake)

install(TARGETS cellml EXPORT libcellml-targets
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
)

install(FILES
  ${API_HEADER_FILES}
  DESTINATION include/libcellml
)

install(EXPORT libcellml-targets DESTINATION lib/cmake)

