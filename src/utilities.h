/*
Copyright libCellML Contributors

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#pragma once

#include <string>

#include "libcellml/exportdefinitions.h"

namespace libcellml {

/**
 * @brief Try to convert the @p candidate @c std::string to a @c double.
 *
 * Try to convert the @p candidate @c std::string to a @c double. If @p candidate
 * cannot be converted using @c std::stod, catch the exception and return
 * @c false. If @p input can be converted, return @c true.  The value of the
 * converted candidate will be set to @p value.
 *
 * @param candidate The @c std::string value to try to convert to a @c double.
 * @param value The @c double value of the candidate if valid.
 *
 * @return @c false if @p input cannot be converted to a @c double using
 * @c std::stod and @c true otherwise.
 *
 */
bool convertToDouble(const std::string &candidate, double *value=nullptr);

/**
 * @brief Convert a @c double to @c std::string format.
 *
 * Convert the @p value to @c std::string representation.
 *
 * @param value The @c double value number to convert.
 *
 * @return @c std::string representation of the @p value.
 */
std::string convertDoubleToString(double value);

/**
 * @brief Check if the @p input @c std::string has any non-whitespace characters.
 *
 * If the @p input @c std::string has any non-whitespace characters, return
 * @c true, otherwise return @c false.
 *
 * @param input The string to check for non-whitespace characters.
 *
 * @return @c true if @p input contains non-whitespace characters and @c false otherwise.
 */
bool hasNonWhitespaceCharacters(const std::string &input);

}
