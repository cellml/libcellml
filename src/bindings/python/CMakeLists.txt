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

# Based on an example from
#  http://www.swig.org/Doc3.0/Introduction.html#Introduction_build_system

# Add python package and header directories
find_package(PythonLibs REQUIRED)
include_directories(${PYTHON_INCLUDE_PATH})

# Create empty flags
set(CMAKE_SWIG_FLAGS "")

# Enable cpp
set_source_files_properties(../interface/cellml.i PROPERTIES CPLUSPLUS ON)
set_source_files_properties(../interface/cellml.i PROPERTIES SWIG_FLAGS "-includeall")

# Include source dir
#include_directories(${PROJECT_SOURCE_DIR})
#include_directories(${PROJECT_SOURCE_DIR}/api/)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# Add library
swig_add_library(cellml
    LANGUAGE python
    SOURCES ../interface/cellml.i)

# Link with Python libraries
swig_link_libraries(cellml cellml ${PYTHON_LIBRARIES})

# Link with CellML libraries
#swig_link_libraries(cellml libcellml)
