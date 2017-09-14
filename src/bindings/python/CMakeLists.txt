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

# Add python package and header directories
find_package(PythonLibs REQUIRED)
include_directories(${PYTHON_INCLUDE_PATH})

# Include source dir and binary dir
include_directories(${PROJECT_SOURCE_DIR}/src/api)
include_directories(${PROJECT_BINARY_DIR}/src/api/)

# Add swig interface files
# Note: These filenames double as (generated .so file) module names!
set(SWIG_INTERFACE_SRCS
    __init__.i
    ../interface/component.i
    ../interface/componententity.i
    ../interface/entity.i
    ../interface/enumerations.i
    ../interface/imports.i
    ../interface/importedentity.i
    ../interface/namedentity.i
    ../interface/units.i
)

# Configure for C++
set_source_files_properties(${SWIG_INTERFACE_SRCS} PROPERTIES CPLUSPLUS ON)

# Set output path (relative to current in build dir)
set(CMAKE_SWIG_OUTDIR libcellml)

# Create bindings for each interface file
foreach(SWIG_INTERFACE_SRC ${SWIG_INTERFACE_SRCS})
    get_filename_component(MODULE_NAME ${SWIG_INTERFACE_SRC} NAME_WE)
    if (${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION} GREATER 3.7)
        swig_add_library(${MODULE_NAME}
            LANGUAGE python
            SOURCES ${SWIG_INTERFACE_SRC})
    else ()
        swig_add_module(${MODULE_NAME} python ${SWIG_INTERFACE_SRC})
    endif ()
    swig_link_libraries(${MODULE_NAME} ${PYTHON_LIBRARIES} cellml)
    set(MODULE_TARGET ${SWIG_MODULE_${MODULE_NAME}_REAL_NAME})
#    message(STATUS "swig_generated_file_fullname: ${swig_generated_file_fullname}")
    set_target_properties(${MODULE_TARGET} PROPERTIES
        CXX_STANDARD 11
        CXX_STANDARD_REQUIRED ON
        CXX_VISIBILITY_PRESET hidden
        #LIBRARY_OUTPUT_DIRECTORY bin
        )
endforeach()

# Add new paths to make clean
set_property(DIRECTORY APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES "libcellml")
