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

#
# Note: Most tests are just here to check if the calling signatures and
# return types are converted ok.
# Some tests check if the state of the objects has changed, not as a
# test of function (which is tested in the C++ tests), but as a check
# to see if the underlying methods have been called correctly.
#

if(LIBCELLML_BINDINGS_PYTHON) # Or any other bindings
    find_package(SWIG 3 REQUIRED)
    include(${SWIG_USE_FILE})
    mark_as_advanced(SWIG_EXECUTABLE)
endif()

if(LIBCELLML_BINDINGS_PYTHON)
    add_subdirectory(python)
endif()
