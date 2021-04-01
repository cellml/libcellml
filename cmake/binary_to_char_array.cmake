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

# This script requires CMake version 3.18 to run hence why it is not directly part of the build configuration.
# usage:
#  cmake -P binary_to_char_array.cmake <full-path-to-xhtml-math11-f.dtd>
#
# Err, not quite working like that just yet.

function(STRING_HEX_KEY_TO_C_BYTE_ARRAY STRING_HEX VARIABLE_NAME _DATA_STATEMENT _LEN_STATEMENT)
    # Separate into individual bytes.
    string(REGEX MATCHALL "([A-Fa-f0-9][A-Fa-f0-9])" SEPARATED_HEX ${STRING_HEX})

    list(LENGTH SEPARATED_HEX HEX_LEN)
    # Append the "0x" to each byte.
    list(JOIN SEPARATED_HEX ", 0x" FORMATTED_HEX)

    # Prepend "(0x"
    string(PREPEND FORMATTED_HEX "{0x")

    # Append " )"
    string(APPEND FORMATTED_HEX " }")

    set(${_DATA_STATEMENT} "const std::vector<unsigned char> ${VARIABLE_NAME} = ${FORMATTED_HEX};" PARENT_SCOPE)
    set(${_LEN_STATEMENT} "static const size_t ${VARIABLE_NAME}_LEN = ${HEX_LEN};" PARENT_SCOPE)
endfunction()

if(CMAKE_ARGC EQUAL 5)
  set(COMPRESSED_FILE "${CMAKE_ARGV3}")
  set(MATHML_DTD_LEN ${CMAKE_ARGV4})
  # Would like to be able to handle GZip compression but at the moment that is a bridge too far.
  # file(ARCHIVE_CREATE OUTPUT "${COMPRESSED_FILE}" FORMAT paxr COMPRESSION GZip PATHS "${CMAKE_ARGV3}")
  file(READ "${COMPRESSED_FILE}" HEX_CONTENTS HEX)

  set(MATHML_DTD_LEN_STATEMENT "static const size_t MATHML_DTD_LEN = ${MATHML_DTD_LEN};")
  string_hex_key_to_c_byte_array("${HEX_CONTENTS}" "COMPRESSED_MATHML_DTD" COMPRESSED_MATHML_DTD_DATA_STATEMENT COMPRESSED_MATHML_DTD_LEN_STATEMENT)
  # Because we are not able to generate this at build configure time we will put it into the source repository itself.
  configure_file("${CMAKE_CURRENT_LIST_DIR}/../src/configure/mathmldtd.in.h" "${CMAKE_CURRENT_LIST_DIR}/../src/mathmldtd.h")
else()
    message(WARNING "Incorrect number of arguments for script, requires four arguments.")
endif()
