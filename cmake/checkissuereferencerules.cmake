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

# Check that ruleToInformation (in issue.cpp) has one entry for each
# Issue::ReferenceRule value (in issue.h), in declaration order, and that the
# name of each entry matches its rule.
# Usage: cmake -P checkissuereferencerules.cmake <issue.h> <issue.cpp>

set(_ISSUE_HEADER_FILE ${CMAKE_ARGV3})
set(_ISSUE_SOURCE_FILE ${CMAKE_ARGV4})

# Retrieve the Issue::ReferenceRule values.

file(READ ${_ISSUE_HEADER_FILE} _CONTENT)
string(REGEX MATCH "enum class ReferenceRule[^{]*{([^}]*)}" _MATCH "${_CONTENT}")

if(NOT _MATCH)
  message(FATAL_ERROR "Could not find the Issue::ReferenceRule enum in '${_ISSUE_HEADER_FILE}'.")
endif()

string(REGEX REPLACE "//[^\n]*" "" _ENUM_BODY "${CMAKE_MATCH_1}")
string(REGEX MATCHALL "[A-Z0-9_]+" _RULES "${_ENUM_BODY}")

# Retrieve the ruleToInformation entries.

file(READ ${_ISSUE_SOURCE_FILE} _CONTENT)
string(REGEX MATCH "ruleToInformation\\[\\] = {(.*)\n};" _MATCH "${_CONTENT}")

if(NOT _MATCH)
  message(FATAL_ERROR "Could not find the ruleToInformation table in '${_ISSUE_SOURCE_FILE}'.")
endif()

string(REGEX MATCHALL "{Issue::ReferenceRule::[A-Z0-9_]+, \"[A-Z0-9_]*\"" _ENTRIES "${CMAKE_MATCH_1}")

# Compare the two.

list(LENGTH _RULES _RULES_COUNT)
list(LENGTH _ENTRIES _ENTRIES_COUNT)

if(NOT _RULES_COUNT EQUAL _ENTRIES_COUNT)
  message(FATAL_ERROR "Issue::ReferenceRule has ${_RULES_COUNT} values, but ruleToInformation has ${_ENTRIES_COUNT} entries.")
endif()

math(EXPR _LAST_INDEX "${_RULES_COUNT} - 1")

foreach(_INDEX RANGE ${_LAST_INDEX})
  list(GET _RULES ${_INDEX} _RULE)
  list(GET _ENTRIES ${_INDEX} _ENTRY)
  string(REGEX REPLACE "{Issue::ReferenceRule::([A-Z0-9_]+), \"([A-Z0-9_]*)\"" "\\1;\\2" _ENTRY "${_ENTRY}")
  list(GET _ENTRY 0 _ENTRY_RULE)
  list(LENGTH _ENTRY _ENTRY_LENGTH)

  if(_ENTRY_LENGTH EQUAL 2)
    list(GET _ENTRY 1 _ENTRY_NAME)
  else()
    set(_ENTRY_NAME "")
  endif()

  if(NOT _ENTRY_RULE STREQUAL _RULE)
    message(FATAL_ERROR "ruleToInformation entry #${_INDEX} is for '${_ENTRY_RULE}', but Issue::ReferenceRule value #${_INDEX} is '${_RULE}'.")
  endif()

  if(_RULE STREQUAL "UNDEFINED" OR _RULE STREQUAL "UNSPECIFIED")
    set(_EXPECTED_NAME "")
  else()
    set(_EXPECTED_NAME ${_RULE})
  endif()

  if(NOT _ENTRY_NAME STREQUAL _EXPECTED_NAME)
    message(FATAL_ERROR "ruleToInformation entry for '${_RULE}' has name '${_ENTRY_NAME}', but '${_EXPECTED_NAME}' was expected.")
  endif()
endforeach()
