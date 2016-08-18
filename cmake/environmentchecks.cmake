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

find_package(PythonInterp)

find_program(VALGRIND_EXE NAMES ${PREFERRED_VALGRIND_NAMES} valgrind)
find_program(GCOV_EXE NAMES ${PREFERRED_GCOV_NAMES} gcov)
find_program(FIND_EXE NAMES ${PREFERRED_FIND_NAMES} find)
find_package(Doxygen)
find_package(Sphinx)

if(VALGRIND_EXE AND PYTHONINTERP_FOUND)
  set(VALGRIND_TESTING_AVAILABLE TRUE CACHE BOOL "Executables required to run valgrind testing are available.")
endif()
if(GCOV_EXE AND FIND_EXE AND PYTHONINTERP_FOUND)
  set(COVERAGE_TEST_AVAILABLE TRUE CACHE BOOL "Executables required to run the coverage testing are available.")
endif()
mark_as_advanced(VALGRIND_EXE VALGRIND_TESTING_AVAILABLE GCOV_EXE FIND_EXE COVERAGE_TEST_AVAILABLE)

