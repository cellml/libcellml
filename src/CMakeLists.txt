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
include(GenerateExportHeader)

set(CLEAN_FILES)

foreach(VERSION_PART libCellML_VERSION_MAJOR libCellML_VERSION_MINOR libCellML_VERSION_PATCH)
  string(LENGTH ${${VERSION_PART}} VERSION_PART_LENGTH)
  if(VERSION_PART_LENGTH EQUAL 1)
    set(${VERSION_PART}_PAD 0)
  endif()
endforeach()
set(LIBCELLML_LIBRARY_VERSION 0x${libCellML_VERSION_MAJOR_PAD}${libCellML_VERSION_MAJOR}${libCellML_VERSION_MINOR_PAD}${libCellML_VERSION_MINOR}${libCellML_VERSION_PATCH_PAD}${libCellML_VERSION_PATCH})
set(LIBCELLML_LIBRARY_VERSION_STRING "${libCellML_VERSION_MAJOR}.${libCellML_VERSION_MINOR}.${libCellML_VERSION_PATCH}")

set(LIBCELLML_MATHML_DTD_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/dtds/mathml2/mathml2.dtd")

set(LIBCELLML_EXPORTDEFINITIONS_H "${CMAKE_CURRENT_BINARY_DIR}/api/libcellml/exportdefinitions.h")
set(LIBCELLML_VERSIONCONFIG_H "${CMAKE_CURRENT_BINARY_DIR}/versionconfig.h")
configure_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/configure/versionconfig.h.in"
  ${LIBCELLML_VERSIONCONFIG_H}
)

list(APPEND CLEAN_FILES ${LIBCELLML_VERSIONCONFIG_H} ${LIBCELLML_EXPORTDEFINITIONS_H})

set(MATHML_CONFIG_H "${CMAKE_CURRENT_BINARY_DIR}/mathmlconfig.h")
configure_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/configure/mathmlconfig.h.in"
  ${MATHML_CONFIG_H}
)

set(SOURCE_FILES
  ${CMAKE_CURRENT_SOURCE_DIR}/component.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/componententity.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/entity.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/error.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/importedentity.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/importsource.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/logger.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/model.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/namedentity.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/parser.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/printer.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/units.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/utilities.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/validator.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/variable.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/version.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/xmlattribute.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/xmldoc.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/xmlnode.cpp
)

set(API_HEADER_FILES
  ${CMAKE_CURRENT_SOURCE_DIR}/api/libcellml/component.h
  ${CMAKE_CURRENT_SOURCE_DIR}/api/libcellml/componententity.h
  ${CMAKE_CURRENT_SOURCE_DIR}/api/libcellml/entity.h
  ${CMAKE_CURRENT_SOURCE_DIR}/api/libcellml/enumerations.h
  ${CMAKE_CURRENT_SOURCE_DIR}/api/libcellml/error.h
  ${CMAKE_CURRENT_SOURCE_DIR}/api/libcellml/importedentity.h
  ${CMAKE_CURRENT_SOURCE_DIR}/api/libcellml/importsource.h
  ${CMAKE_CURRENT_SOURCE_DIR}/api/libcellml/logger.h
  ${CMAKE_CURRENT_SOURCE_DIR}/api/libcellml/model.h
  ${CMAKE_CURRENT_SOURCE_DIR}/api/libcellml/namedentity.h
  ${CMAKE_CURRENT_SOURCE_DIR}/api/libcellml/parser.h
  ${CMAKE_CURRENT_SOURCE_DIR}/api/libcellml/printer.h
  ${CMAKE_CURRENT_SOURCE_DIR}/api/libcellml/specificationrules.h
  ${CMAKE_CURRENT_SOURCE_DIR}/api/libcellml/types.h
  ${CMAKE_CURRENT_SOURCE_DIR}/api/libcellml/units.h
  ${CMAKE_CURRENT_SOURCE_DIR}/api/libcellml/validator.h
  ${CMAKE_CURRENT_SOURCE_DIR}/api/libcellml/variable.h
  ${CMAKE_CURRENT_SOURCE_DIR}/api/libcellml/version.h
  ${LIBCELLML_EXPORTDEFINITIONS_H}
)

set(MODULE_HEADER_FILES
  ${CMAKE_CURRENT_SOURCE_DIR}/api/libcellml/module/libcellml
)

set(HEADER_FILES
  ${LIBCELLML_VERSIONCONFIG_H}
  ${CMAKE_CURRENT_SOURCE_DIR}/utilities.h
  ${CMAKE_CURRENT_SOURCE_DIR}/xmlattribute.h
  ${CMAKE_CURRENT_SOURCE_DIR}/xmldoc.h
  ${CMAKE_CURRENT_SOURCE_DIR}/xmlnode.h
  ${MATHML_CONFIG_H}
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

generate_export_header(cellml EXPORT_FILE_NAME ${LIBCELLML_EXPORTDEFINITIONS_H} BASE_NAME LIBCELLML)

target_include_directories(cellml
  PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/api>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/api>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/api/libcellml/module>
  $<INSTALL_INTERFACE:include/>
  $<INSTALL_INTERFACE:include/libcellml/module>
  ${LIBXML2_INCLUDE_DIR}
  PRIVATE
  ${CMAKE_CURRENT_BINARY_DIR}
)

target_link_libraries(cellml PUBLIC ${LIBXML2_LIBRARIES})

target_compile_definitions(cellml PUBLIC ${LIBXML2_DEFINITIONS})

set_target_properties(cellml PROPERTIES
  CXX_STANDARD 11
  CXX_STANDARD_REQUIRED ON
  CXX_VISIBILITY_PRESET hidden
  VISIBILITY_INLINES_HIDDEN 1
  DEBUG_POSTFIX d
  VERSION ${libCellML_VERSION}
  INTERFACE_libCellML_MAJOR_VERSION ${libCellML_VERSION_MAJOR}
  COMPATIBLE_INTERFACE_STRING ${libCellML_VERSION_MAJOR}
)

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

include(CMakePackageConfigHelpers)
set(BUILD_TREE_CONFIG_DIR ${PROJECT_BINARY_DIR})
set(LIBCELLML_CONFIG_VERSION_FILE "${BUILD_TREE_CONFIG_DIR}/libcellml-config-version.cmake")
write_basic_package_version_file(
  ${LIBCELLML_CONFIG_VERSION_FILE}
  VERSION ${libCellML_VERSION}
  COMPATIBILITY AnyNewerVersion
)
list(APPEND CLEAN_FILES ${LIBCELLML_CONFIG_VERSION_FILE})

set(LIBCELLML_TARGETS_FILE "${BUILD_TREE_CONFIG_DIR}/libcellml-targets.cmake")
export(EXPORT libcellml-targets FILE ${LIBCELLML_TARGETS_FILE})
list(APPEND CLEAN_FILES ${LIBCELLML_TARGETS_FILE})

set(LIBCELLML_CONFIG_CMAKE_FILE "${BUILD_TREE_CONFIG_DIR}/libcellml-config.cmake")
configure_file("${PROJECT_SOURCE_DIR}/cmake/libcellml-config.cmake"
  ${LIBCELLML_CONFIG_CMAKE_FILE}
  COPYONLY
)
list(APPEND CLEAN_FILES ${LIBCELLML_CONFIG_CMAKE_FILE})

set(ConfigPackageLocation lib/cmake)
install(EXPORT libcellml-targets
  FILE libcellml-targets.cmake
  DESTINATION ${ConfigPackageLocation}
)

install(
  FILES
    ${LIBCELLML_CONFIG_CMAKE_FILE}
    ${LIBCELLML_CONFIG_VERSION_FILE}
  DESTINATION ${ConfigPackageLocation}
  COMPONENT Devel
)

set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES "${CLEAN_FILES}")

