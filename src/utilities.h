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

#include "libcellml/types.h"

#include <map>
#include <string>
#include <vector>

namespace libcellml {

/**
* Vector of base units.
*/
const std::vector<std::string> baseUnitsList = {
    "ampere",
    "candela",
    "dimensionless",
    "kelvin",
    "kilogram",
    "metre",
    "mole",
    "second"};

/**
*  Map connecting standard built-in units to their base unit components and their exponents.
*/
const std::map<std::string, std::map<std::string, double>> standardUnitsList = {
    {"ampere", {{"ampere", 1.0}}},
    {"becquerel", {{"second", -1.0}}},
    {"candela", {{"candela", 1.0}}},
    {"coulomb", {{"ampere", -1.0}, {"second", 1.0}}},
    {"dimensionless", {{"dimensionless", 1.0}}},
    {"farad", {{"ampere", 2.0}, {"kilogram", -1.0}, {"metre", -2.0}, {"second", -4.0}}},
    {"gram", {{"kilogram", 1.0}}},
    {"gray", {{"metre", 2.0}, {"second", -2.0}}},
    {"henry", {{"ampere", -2.0}, {"kilogram", 1.0}, {"metre", 2.0}, {"second", -2.0}}},
    {"hertz", {{"second", -1.0}}},
    {"joule", {{"kilogram", 1.0}, {"metre", 2.0}, {"second", -2.0}}},
    {"katal", {{"mole", 1.0}, {"second", -1.0}}},
    {"kelvin", {{"kelvin", 1.0}}},
    {"kilogram", {{"kilogram", 1.0}}},
    {"litre", {{"metre", 3.0}}},
    {"lumen", {{"candela", 1.0}}},
    {"lux", {{"candela", 1.0}, {"metre", -2.0}}},
    {"metre", {{"metre", 1.0}}},
    {"mole", {{"mole", 1.0}}},
    {"newton", {{"kilogram", 1.0}, {"metre", 1.0}, {"second", -2.0}}},
    {"ohm", {{"ampere", -2.0}, {"kilogram", 1.0}, {"metre", 2.0}, {"second", -3.0}}},
    {"pascal", {{"kilogram", 1.0}, {"metre", -1.0}, {"second", -2.0}}},
    {"radian", {{"dimensionless", 1.0}}},
    {"second", {{"second", 1.0}}},
    {"siemens", {{"ampere", 2.0}, {"kilogram", -1.0}, {"metre", -2.0}, {"second", 3.0}}},
    {"sievert", {{"metre", 2.0}, {"second", -2.0}}},
    {"steradian", {{"dimensionless", 1.0}}},
    {"tesla", {{"ampere", -1.0}, {"kilogram", 1.0}, {"second", -2.0}}},
    {"volt", {{"ampere", -1.0}, {"kilogram", 1.0}, {"metre", 2.0}, {"second", -3.0}}},
    {"watt", {{"kilogram", 1.0}, {"metre", 2.0}, {"second", -3.0}}},
    {"weber", {{"ampere", -1.0}, {"kilogram", 1.0}, {"metre", 2.0}, {"second", -2.0}}}};

/**
* Map connecting standard built-in units to the multiplier exponent of their base unit components.
*/
const std::map<std::string, double> standardMultiplierList = {
    {"ampere", 0.0},
    {"becquerel", 0.0},
    {"candela", 0.0},
    {"coulomb", 0.0},
    {"dimensionless", 0.0},
    {"farad", 0.0},
    {"gram", -3.0},
    {"gray", 0.0},
    {"henry", 0.0},
    {"hertz", 0.0},
    {"joule", 0.0},
    {"katal", 0.0},
    {"kelvin", 0.0},
    {"kilogram", 0.0},
    {"litre", -3.0},
    {"lumen", 0.0},
    {"lux", 0.0},
    {"metre", 0.0},
    {"mole", 0.0},
    {"newton", 0.0},
    {"ohm", 0.0},
    {"pascal", 0.0},
    {"radian", 0.0},
    {"second", 0.0},
    {"siemens", 0.0},
    {"sievert", 0.0},
    {"steradian", 0.0},
    {"tesla", 0.0},
    {"volt", 0.0},
    {"watt", 0.0},
    {"weber", 0.0}};

/**
* Map connecting prefix strings to their exponent (eg: "kilo" -> 10^3).
*/
const std::map<std::string, int> standardPrefixList = {
    {"yotta", 24},
    {"zetta", 21},
    {"exa", 18},
    {"peta", 15},
    {"tera", 12},
    {"giga", 9},
    {"mega", 6},
    {"kilo", 3},
    {"hecto", 2},
    {"deca", 1},
    {"", 0},
    {"deci", -1},
    {"centi", -2},
    {"milli", -3},
    {"micro", -6},
    {"nano", -9},
    {"pico", -12},
    {"femto", -15},
    {"atto", -18},
    {"zepto", -21},
    {"yocto", -24},
    {"24", 24},
    {"23", 23},
    {"22", 22},
    {"21", 21},
    {"20", 20},
    {"19", 19},
    {"18", 18},
    {"17", 17},
    {"16", 16},
    {"15", 15},
    {"14", 14},
    {"13", 13},
    {"12", 12},
    {"11", 11},
    {"10", 10},
    {"9", 9},
    {"8", 8},
    {"7", 7},
    {"6", 6},
    {"5", 5},
    {"4", 4},
    {"3", 3},
    {"2", 2},
    {"1", 1},
    {"0", 0},
    {"-1", -1},
    {"-2", -2},
    {"-3", -3},
    {"-4", -4},
    {"-5", -5},
    {"-6", -6},
    {"-7", -7},
    {"-8", -8},
    {"-9", -9},
    {"-10", -10},
    {"-11", -11},
    {"-12", -12},
    {"-13", -13},
    {"-14", -14},
    {"-15", -15},
    {"-16", -16},
    {"-17", -17},
    {"-18", -18},
    {"-19", -19},
    {"-20", -20},
    {"-21", -21},
    {"-22", -22},
    {"-23", -23},
    {"-24", -24}};

/*
* List of MathML elements supported by CellML.
*/
const std::vector<std::string> supportedMathMLElements = {
    "ci", "cn", "sep", "apply", "piecewise", "piece", "otherwise", "eq", "neq", "gt", "lt", "geq", "leq", "and", "or",
    "xor", "not", "plus", "minus", "times", "divide", "power", "root", "abs", "exp", "ln", "log", "floor",
    "ceiling", "min", "max", "rem", "diff", "bvar", "logbase", "degree", "sin", "cos", "tan", "sec", "csc",
    "cot", "sinh", "cosh", "tanh", "sech", "csch", "coth", "arcsin", "arccos", "arctan", "arcsec", "arccsc",
    "arccot", "arcsinh", "arccosh", "arctanh", "arcsech", "arccsch", "arccoth", "pi", "exponentiale",
    "notanumber", "infinity", "true", "false"};

/**
 * @brief Convert the @p candidate @c std::string to a @c double.
 *
 * Convert the @p candidate @c std::string to a @c double. If @p candidate
 * cannot be converted using @c std::stod an exception will be raised.  To
 * avoid raising an exception the candidate string must be known to be convertible
 * to a double before calling this function.
 *
 * @sa isCellMLReal
 *
 * @param candidate The @c std::string value to convert to a @c double.
 *
 * @return The @c double value of the candidate.
 *
 */
double convertToDouble(const std::string &candidate);

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
 * Convert the @p candidate @c std::string to an @c int. If @p candidate
 * cannot be converted using @c std::stoi an exception will be raised.  To
 * avoid raising an exception the candidate string must be known to be convertible
 * to an int before calling this function.
 *
 * @sa isCellMLInteger
 *
 * @param candidate The @c std::string value to convert to an @c int.
 *
 * @return The @c int value of the candidate.
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

/**
 * @brief Test if the @p candidate @c std::string is in the form of a CellML real.
 *
 * The candidate string must consist of european numeric characters.  It may optionally
 * have a basic Latin hyphen character '-' to indicate sign.  It may also optianally
 * use the basic Latin fullstop character '.' to indicate a decimal point.  The candidate
 * string must represent a number in base 10.  The basic Latin 'e' or 'E' character
 * may be used to indicate the exponent.  The exponent must be described as a
 * CellML integer.
 *
 * @param candidate The string to test and determine whether or not it is a CellML real.
 * @return @c true if the @p candidate is a CellML real and @c false otherwise.
 */
bool isCellMLReal(const std::string &candidate);

/**
 * @brief Test if @p value1 @c double and @p value2 @c double are equal.
 *
 * Return @c true if @p value1 @c double and @p value2 @c double are equal,
 * otherwise return @c false.
 *
 * @param value1 The first @c double value to test.
 * @param value2 The second @c double value to test.
 *
 * @return @c true if @p value1 and @p value2 are equal and @c false otherwise.
 */
bool areEqual(double value1, double value2);

/**
 * @brief Compute the SHA-1 value of the @p string @c std::string.
 *
 * Compute and return the SHA-1 value of the @p string @c std::string.
 *
 * @param string The @c std::string value for which we want the SHA-1 value.
 *
 * @return The @c std::string SHA-1 value.
 */
std::string sha1(const std::string &string);

/**
 * @brief Get the name of the entity.
 *
 * If the entity is a @c NamedEntity then the name of the entity will
 * be returned (which could be the empty string).  If the entity is not
 * a @c NamedEntity then the empty string will be returned.
 *
 * @param entity The entity to get the name for.
 * @return The @c std::string name of the entity.
 */
std::string getEntityName(const EntityPtr &entity);

/**
 * @brief Get the @c Model that the entity is owned by.
 *
 * Travel up the entities hierarchy to find the owning model. If
 * the entity doesn't have an owning model return the @c nullptr.
 *
 * @param entity The entity to get the owning model for.
 * @return The owning @c Model or the @c nullptr if no model owns this entity.
 */
ModelPtr parentModel(const EntityPtr & entity);

} // namespace libcellml
