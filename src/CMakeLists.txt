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

include(GenerateExportHeader)

foreach(VERSION_PART libCellML_VERSION_MAJOR libCellML_VERSION_MINOR libCellML_VERSION_PATCH)
  string(LENGTH ${${VERSION_PART}} VERSION_PART_LENGTH)
  if(VERSION_PART_LENGTH EQUAL 1)
    set(${VERSION_PART}_PAD 0)
  endif()
endforeach()
set(LIBCELLML_LIBRARY_VERSION 0x${libCellML_VERSION_MAJOR_PAD}${libCellML_VERSION_MAJOR}${libCellML_VERSION_MINOR_PAD}${libCellML_VERSION_MINOR}${libCellML_VERSION_PATCH_PAD}${libCellML_VERSION_PATCH})
set(LIBCELLML_LIBRARY_VERSION_STRING "${libCellML_VERSION_MAJOR}.${libCellML_VERSION_MINOR}.${libCellML_VERSION_PATCH}")

set(CELLML_EXPORT_H "${CMAKE_CURRENT_BINARY_DIR}/api/libcellml/libcellml_export.h")
set_source_files_properties(${CELLML_EXPORT_H} PROPERTIES GENERATED TRUE)
set(LIBCELLML_CONFIG_H "${CMAKE_CURRENT_BINARY_DIR}/libcellml_config.h")
configure_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/configure/libcellml_config.h.in"
  ${LIBCELLML_CONFIG_H}
)

set(SOURCE_FILES
  ${CMAKE_CURRENT_SOURCE_DIR}/component.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/componententity.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/entity.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/import.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/importedentity.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/model.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/namedentity.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/units.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/variable.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/version.cpp
)

set(API_HEADER_FILES
  ${CMAKE_CURRENT_SOURCE_DIR}/api/libcellml/component.h
  ${CMAKE_CURRENT_SOURCE_DIR}/api/libcellml/componententity.h
  ${CMAKE_CURRENT_SOURCE_DIR}/api/libcellml/entity.h
  ${CMAKE_CURRENT_SOURCE_DIR}/api/libcellml/enumerations.h
  ${CMAKE_CURRENT_SOURCE_DIR}/api/libcellml/import.h
  ${CMAKE_CURRENT_SOURCE_DIR}/api/libcellml/importedentity.h
  ${CMAKE_CURRENT_SOURCE_DIR}/api/libcellml/model.h
  ${CMAKE_CURRENT_SOURCE_DIR}/api/libcellml/namedentity.h
  ${CMAKE_CURRENT_SOURCE_DIR}/api/libcellml/types.h
  ${CMAKE_CURRENT_SOURCE_DIR}/api/libcellml/units.h
  ${CMAKE_CURRENT_SOURCE_DIR}/api/libcellml/variable.h
  ${CMAKE_CURRENT_SOURCE_DIR}/api/libcellml/version.h
  ${CELLML_EXPORT_H}
  ${CMAKE_CURRENT_SOURCE_DIR}/api/libcellml/module/libcellml
)

set(HEADER_FILES
  ${LIBCELLML_CONFIG_H}
)

# Only does anything if configuration target is Visual Studio.
group_source_to_dir_structure(
  ${SOURCE_FILES}
  ${HEADER_FILES}
  ${MODULE_HEADER_FILES}
  ${API_HEADER_FILES}
)

add_library(cellml
  ${SOURCE_FILES}
  ${HEADER_FILES}
  ${MODULE_HEADER_FILES}
  ${API_HEADER_FILES}
)

generate_export_header(cellml EXPORT_FILE_NAME ${CELLML_EXPORT_H} BASE_NAME LIBCELLML)

target_include_directories(cellml
  PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/api>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/api>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/api/libcellml/module>
  $<INSTALL_INTERFACE:include/>
  $<INSTALL_INTERFACE:include/libcellml/module>
  PRIVATE
  ${CMAKE_CURRENT_BINARY_DIR}
)

if(LIBCELLML_UNIT_TESTS)
  target_compile_definitions(cellml PRIVATE EXPORT_FOR_TESTING=LIBCELLML_EXPORT)
else()
  target_compile_definitions(cellml PRIVATE EXPORT_FOR_TESTING=)
endif()

set_target_properties(cellml PROPERTIES
  CXX_STANDARD 11
  CXX_STANDARD_REQUIRED ON
  CXX_VISIBILITY_PRESET hidden
  VISIBILITY_INLINES_HIDDEN 1)

if(LIBCELLML_TREAT_WARNINGS_AS_ERRORS)
  target_warnings_as_errors(cellml)
endif()

if(LIBCELLML_COVERAGE)
  set_target_properties(cellml PROPERTIES COMPILE_FLAGS "-fprofile-arcs -ftest-coverage"
    LINK_FLAGS "-fprofile-arcs -ftest-coverage")

  # Share some paths with interested parties (tests)
  set(GCOV_ANALYSIS_PATH "${CMAKE_CURRENT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/cellml.dir" PARENT_SCOPE)
  set(GCOV_PREFIX_PATH "${CMAKE_CURRENT_SOURCE_DIR}" PARENT_SCOPE)
  set(GCOV_BUILD_PREFIX_PATH "${CMAKE_CURRENT_BINARY_DIR}" PARENT_SCOPE)

  set(GCOV_CLEAN_FILES)
  foreach(src_file ${SOURCE_FILES})
    get_filename_component(_tmp_file "${src_file}" NAME)
    list(APPEND GCOV_CLEAN_FILES "${CMAKE_CURRENT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/cellml.dir/${_tmp_file}.gcno")
    list(APPEND GCOV_CLEAN_FILES "${CMAKE_CURRENT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/cellml.dir/${_tmp_file}.gcda")
  endforeach()
  set_directory_properties(${GCOV_ANALYSIS_PATH} PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES "${GCOV_CLEAN_FILES}")
endif()

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

install(FILES
  ${MODULE_HEADER_FILES}
  DESTINATION include/libcellml/module
)

install(EXPORT libcellml-targets DESTINATION lib/cmake)

