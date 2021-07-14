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

add_executable(generatorprofilesha1value generatorprofilesha1value.cpp)
target_link_libraries(generatorprofilesha1value cellml)

if(LIBCELLML_CLANG_TIDY)
  configure_clang_and_clang_tidy_settings(generatorprofilesha1value)
endif()

if(LIBCELLML_TREAT_WARNINGS_AS_ERRORS)
  target_warnings_as_errors(generatorprofilesha1value)
endif()
