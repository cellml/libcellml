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
 * @c false. If @p candidate can be converted, return @c true.  The value of the
 * converted candidate will be set to @p value.
 *
 * @param candidate The @c std::string value to try to convert to a @c double.
 * @param value The @c double value of the candidate if valid.
 *
 * @return @c false if @p candidate cannot be converted to a @c double using
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
 * @brief Convert the @p candidate @c std::string to an @c int.
 *
 * Try to convert the @p candidate @c std::string to an @c int. If @p candidate
 * cannot be converted using @c std::stoi an exception will be raised.  To
 * avoid raising an exception the candidate string must be known to be convertible
 * to an int before calling this function.
 *
 * @param candidate The @c std::string value to try to convert to an @c int.
 *
 * @return The @c int value of the candidate.
 *
 */
int convertToInt(const std::string &candidate);

/**
 * @brief Convert a @c int to @c std::string format.
 *
 * Convert the @p value to @c std::string representation.
 *
 * @param value The @c int value of the integer to convert.
 *
 * @return @c std::string representation of the @p value.
 */
std::string convertIntToString(int value);

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

/**
 * @brief Test if the @p candidate @c std::string is a valid non-negative CellML integer.
 *
 * The candidate string must consist entirely of european numeric characters and it must also be
 * expressed in base 10 if it is to be considered a non-negative CellML integer.
 *
 * @param candidate The string to check if it is a non-negative CellML integer.
 * @return @c true if the @p candidate is a non-negative CellML integer and @c false otherwise.
 */
bool isNonNegativeCellMLInteger(const std::string &candidate);

/**
 * @brief Test if the @p candidate @c std::string is a valid CellML integer.
 *
 * The candidate string must consist of european numeric characters and optionally the
 * basic Latin hyphen character '-'.  When the integer being represented is negative
 * the candidate string must start with the '-' character followed by the absolute
 * value of the integer.
 *
 * @param candidate The string to test and determine whether or not it is a CellML integer.
 * @return @c true if the @p candidate is a CellML integer and @c false otherwise.
 */
bool isCellMLInteger(const std::string &candidate);

}
