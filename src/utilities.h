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

#include <algorithm>
#include <cctype>
#include <map>
#include <string>
#include <vector>

#include "libcellml/types.h"
#include "libcellml/variable.h"

#include "commonutils.h"
#include "internaltypes.h"

namespace libcellml {

/**
 * Base URLs of specification and example sites from which the Issue::url() will be constructed.
 */
static const std::string baseSpecificationUrl = "https://cellml-specification.readthedocs.io/en/latest/reference/formal_and_informative/";

/**
 * Vector of base units.
 */
static const std::vector<std::string> baseUnitsList = {
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
static const std::map<std::string, std::map<std::string, double>> standardUnitsList = {
    {"ampere", {{"ampere", 1.0}}},
    {"becquerel", {{"second", -1.0}}},
    {"candela", {{"candela", 1.0}}},
    {"coulomb", {{"ampere", 1.0}, {"second", 1.0}}},
    {"dimensionless", {{"dimensionless", 1.0}}},
    {"farad", {{"ampere", 2.0}, {"kilogram", -1.0}, {"metre", -2.0}, {"second", 4.0}}},
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
static const std::map<std::string, double> standardMultiplierList = {
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
static const std::map<std::string, int> standardPrefixList = {
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

/**
 * List of MathML elements supported by CellML.
 */
static const std::vector<std::string> supportedMathMLElements = {
    "ci", "cn", "sep", "apply", "piecewise", "piece", "otherwise", "eq", "neq", "gt", "lt", "geq", "leq", "and", "or",
    "xor", "not", "plus", "minus", "times", "divide", "power", "root", "abs", "exp", "ln", "log", "floor",
    "ceiling", "min", "max", "rem", "diff", "bvar", "logbase", "degree", "sin", "cos", "tan", "sec", "csc",
    "cot", "sinh", "cosh", "tanh", "sech", "csch", "coth", "arcsin", "arccos", "arctan", "arcsec", "arccsc",
    "arccot", "arcsinh", "arccosh", "arctanh", "arcsech", "arccsch", "arccoth", "pi", "exponentiale",
    "notanumber", "infinity", "true", "false"};

/**
 * @brief Map to convert an interface type into its string form.
 *
 * An internal map used to convert a Variable InterfaceType enum class member into its string form.
 */
static const std::map<Variable::InterfaceType, std::string> interfaceTypeToString = {
    {Variable::InterfaceType::NONE, "none"},
    {Variable::InterfaceType::PRIVATE, "private"},
    {Variable::InterfaceType::PUBLIC, "public"},
    {Variable::InterfaceType::PUBLIC_AND_PRIVATE, "public_and_private"}};

/**
 * @brief Convert the @p in @c std::string to the @p out @c double.
 *
 * Convert the @p in @c std::string to a @c double. If @p in can be converted
 * using @c std::stod, return @c true and update @p out, otherwise return
 * @c false. To avoid returning @c false, @p in must be known to be convertible
 * to a @c double before calling this function.
 *
 * @sa isCellMLReal
 *
 * @param in The @c std::string value to convert to a @c double.
 * @param out The @c double value resulting in the conversion.
 *
 * @return @c true if @in represents a @c double, @c false otherwise.
 */
bool convertToDouble(const std::string &in, double &out);

/**
 * @brief Convert the @p in @c std::string to the @p out @c int.
 *
 * Convert the @p in @c std::string to an @c int. If @p in can be converted
 * using @c std::stoi, return @c true and update @p out, otherwise return
 * @c false. To avoid returning @c false, @p in must be known to be convertible
 * to an @c int before calling this function.
 *
 * @sa isCellMLInteger
 *
 * @param in The @c std::string value to convert to an @c int.
 * @param out The @c int value resulting in the conversion.
 *
 * @return @c true if @in represents an @c int, @c false otherwise.
 */
bool convertToInt(const std::string &in, int &out);

/**
 * @brief Convert a @c int to @c std::string format.
 *
 * Convert the @p value to @c std::string representation.
 *
 * @param value The @c int value of the integer to convert.
 *
 * @return @c std::string representation of the @p value.
 */
std::string convertToString(int value);

/**
 * @brief Convert a @c size_t to @c std::string format.
 *
 * Convert the @p value to @c std::string representation.
 *
 * @overload std::string convertToString(int value)
 *
 * @param value The @c size_t value of the integer to convert.
 *
 * @return @c std::string representation of the @p value.
 */
std::string convertToString(size_t value);

/**
 * @brief Convert a @c double to @c std::string format.
 *
 * Convert the @p value to @c std::string representation.
 *
 * @overload std::string convertToString(int value)
 *
 * @param value The @c double value number to convert.
 *
 * @return @c std::string representation of the @p value.
 */
std::string convertToString(double value);

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
 * @brief Remove the given component from the given entity.
 *
 * The entity given can be either a @c Model or @c Component and as such is
 * expected to be derived from @c ComponentEntity.  The component to be removed
 * is expected to be a direct child of the given entity.  That is to say the component
 * will only be removed if it is a direct child of the entity itself, the component
 * hierarchy of the entity will *not* be searched for the location of the component.
 *
 * @param entity The entity to remove the component from.
 * @param component The component to remove from the entity.
 */
void removeComponentFromEntity(const EntityPtr &entity, const ComponentPtr &component);

/**
 * @brief Check if the provided @p name is a standard unit.
 *
 * Checks if the provided @p name is one of the standard units in the
 * @c Units::StandardUnit @c enum. Returns @c true if @p name is a standard unit
 * and @c false otherwise.
 *
 * @param name The @c std::string name to check against the list of standard units.
 *
 * @return @c true if @name is a standard unit and @c false otherwise.
 */
bool isStandardUnitName(const std::string &name);

/**
 * @brief Test if the provided @c Units is a standard unit.
 *
 * Tests to determine if the provided @p units is equivalent to
 * a standard unit.  Returns @c true if the @p units is a standard unit
 * and @c false otherwise.
 *
 * @param units The @c Units to test.
 *
 * @return @c true if @p units is a standard unit, @c false otherwise.
 */
bool isStandardUnit(const UnitsPtr &units);

/**
 * @brief Check if the provided @p name is a standard prefix.
 *
 * Checks if the provided @p name is one of the standard prefixes in the
 * @c Prefix @c enum. Returns @c true if @name is a standard prefix
 * and @c false otherwise.
 *
 * @param name The @c std::string name to check against the list of standard prefixes.
 *
 * @return @c true if @name is a standard prefix and @c false otherwise.
 */
bool isStandardPrefixName(const std::string &name);

/**
 * @brief Get the index of the @p variable in the @p component.
 *
 * Searches through the @p component for the @p variable returning the index
 * of the @p variable if it was found.  If the @p variable was not found then
 * the number of variables in the @p component is returned.
 *
 * @param component The @c ComponentPtr to search for the @c VariablePtr in.
 * @param variable The @c VariablePtr to return the index of.
 * @return The index of the @p variable found in the component.  Returns the
 * number of variables in the component if the variable was not found.
 */
size_t getVariableIndexInComponent(const ComponentPtr &component, const VariablePtr &variable);

/**
 * @brief Test to determine if @p variable1 and @p variable2 are equivalent.
 *
 * Test to see if @p variable1 is the same as or equivalent to @p variable2.
 * Returns @c true if @p variable1 is the same as or equivalent to @p variable2
 * and @c false otherwise.
 *
 * @param variable1 The @c Variable to test if it is equivalent to @p variable2.
 * @param variable2 The @c Variable that is potentially equivalent to
 * @p variable1.
 *
 * @return @c true if @p variable1 is equivalent to @p variable2 and @c false
 * otherwise.
 */
bool areEquivalentVariables(const VariablePtr &variable1,
                            const VariablePtr &variable2);

/**
 * @brief Test to determine if @p entity1 is a child of @p entity2.
 *
 * Test to see if @p entity1 is a child of @p entity2.  Returns @c true if
 * @p entity1 is a child of @p entity2 and @c false otherwise.
 *
 * @param entity1 The @c Entity to test if it is a child of @p entity2.
 * @param entity2 The @c Entity that is potentially the parent of @p entity1.
 *
 * @return @c true if @p entity1 is a child of @p entity2 and @c false otherwise.
 */
bool isEntityChildOf(const EntityPtr &entity1, const EntityPtr &entity2);

/**
 * @brief Test to determine if @p entity1 and @p entity2 are siblings.
 *
 * Test to determine if @p entity1 and @p entity2 are siblings.  Returns
 * @c true if @p entity1 and @p entity2 are siblings, @c false otherwise.
 *
 * @param entity1 An @c Entity to test if it is a sibling to @p entity2.
 * @param entity2 An @c Entity to test if it is a sibling to @p entity1.
 *
 * @return @c true if @p entity1 and @p entity2 are siblings, @c false otherwise.
 */
bool areEntitiesSiblings(const EntityPtr &entity1, const EntityPtr &entity2);

/**
 * @brief Determine the interface type of the @p variable.
 *
 * Determine the interface type of the given @p variable. For variables with
 * at least one equivalent variable, returning an interface type of
 * Variable::InterfaceType::NONE indicates an error.
 *
 * @param variable The variable to determine the interface type for.
 *
 * @return The @p variable's interface type.
 */
Variable::InterfaceType determineInterfaceType(const VariablePtr &variable);

/**
 * @brief Traverse the component tree looking for variables with equivalences.
 *
 * Search through the component tree starting at @p component looking for variables
 * with equivalences.  Variables found in the component tree with equivalences are added
 * to the @p variables list.
 *
 * @param component The @c Component to search.
 * @param variables The list of equivalent variables found.
 */
void findAllVariablesWithEquivalences(const ComponentPtr &component, VariablePtrs &variables);

/**
 * @brief Trim whitespace from the front of a string (in place).
 *
 * Remove whitespace from the front of a string, modifying the passed string.
 *
 * @param s The @c std::string to trim.
 */
static inline void leftTrim(std::string &s)
{
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
                return std::isspace(ch) == 0;
            }));
}

/**
 * @brief Trim whitespace from the end of a string (in place).
 *
 * Remove whitespace from the end of a string, modifying the passed string.
 *
 * @param s The @c std::string to trim.
 */
static inline void rightTrim(std::string &s)
{
    s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
                return std::isspace(ch) == 0;
            }).base(),
            s.end());
}

/**
 * @brief Trim whitespace from the beginning and end of a string(in place).
 *
 * Remove whitespace from the beginning and end of a string, modifying the passed
 * string.
 *
 * @param s The @c std::string to trim.
 */
static inline void trim(std::string &s)
{
    leftTrim(s);
    rightTrim(s);
}

/**
 * @brief Trim whitespace from the beginning and end of a string.
 *
 * Remove whitespace from the beginning and end of a string
 * returning the result.
 *
 * @param s The @c std::string to trim.
 *
 * @return The trimmed string.
 */
static inline std::string trimCopy(std::string s)
{
    trim(s);
    return s;
}

/**
 * @brief Collect all existing id attributes within the given model.
 *
 * @param model The @c ModelPtr to interrogate.
 *
 * @return An @c IdList collection of existing ids.
 */
IdList listIds(const ModelPtr &model);

/**
 * @brief Creates an id string for a "type" object, unique in the context of @p idList.
 *
 * The id format is a 6-digit hexadecimal string.
 *
 * @return A string representing a unique id.
 */
std::string makeUniqueId(IdList &idList);

/**
 * Function to support linking units names to their corresponding @c Units items.
 *
 * @param component The component to check.
 * @param issueList A vector of @c IssuePtr items in which unlinked units are recorded for reporting.
 *
 * @return @c true if all variables have been successfully linked to units, @c false otherwise.
 */
bool linkComponentVariableUnits(const ComponentPtr &component, std::vector<IssuePtr> &issueList);

/**
 * @overload
 *
 * @brief Utility function used when linking units names to their corresponding @c Units items.
 *
 * Returns @c true if all variables in the component can be linked to their units, or
 * @c false otherwise.
 *
 * @param componentEntity The component entity to check.
 *
 * @return @c true upon success; @c false if not all variables could be linked to units.
 */
bool traverseComponentEntityTreeLinkingUnits(const ComponentEntityPtr &componentEntity);

/**
 * @overload
 *
 *  Utility function used when linking units names to their corresponding @c Units items.
 *
 * @param componentEntity The component entity to check.
 * @param issueList An optional @c std::vector of @c IssuePtr items which is used to record cases of missing units.
 *
 * @return @c true upon success; @c false if not all variables could be linked to units.
 * */
bool traverseComponentEntityTreeLinkingUnits(const ComponentEntityPtr &componentEntity, std::vector<IssuePtr> &issueList);

/**
 * @brief Test whether a component contains variables naming units which have not yet
 *        been linked to @c Units items.
 *
 * Utility function used when linking units names to their corresponding @c Units items. It
 * will return a value of @c true when there are variables without linked units, or @c false
 * otherwise.
 *
 * @param component The component to check.
 *
 * @return @c true when unlinked variables are found, @c false otherwise.
 */
bool areComponentVariableUnitsUnlinked(const ComponentPtr &component);

void recordVariableEquivalences(const ComponentPtr &component, EquivalenceMap &equivalenceMap, IndexStack &indexStack);
void generateEquivalenceMap(const ComponentPtr &component, EquivalenceMap &map, IndexStack &indexStack);
void applyEquivalenceMapToModel(const EquivalenceMap &map, const ModelPtr &model);
NameList componentNames(const ModelPtr &model);
NameList unitsNamesUsed(const ComponentPtr &component);
IndexStack reverseEngineerIndexStack(const ComponentPtr &component);
EquivalenceMap rebaseEquivalenceMap(const EquivalenceMap &map, const IndexStack &originStack, const IndexStack &destinationStack);
std::vector<UnitsPtr> unitsUsed(const ModelPtr &model, const ComponentPtr &component);
ComponentNameMap createComponentNamesMap(const ComponentPtr &component);
void findAndReplaceComponentsCnUnitsNames(const ComponentPtr &component, const StringStringMap &replaceMap);
std::string replace(std::string string, const std::string &from, const std::string &to);

/**
 * @brief Create a connection map for the given variables.
 *
 * Create a map of variables that belong to the same connection as
 * the connection created by the equivalent variables @p variable1 and @p variable2.
 *
 * @param variable1 A variable in the connection.
 * @param variable2 A variable in the connection.
 *
 * @return A map of connections.
 */
ConnectionMap createConnectionMap(const VariablePtr &variable1, const VariablePtr &variable2);

/**
 * @brief Make a list of all variables equivalent to the given variable.
 *
 * Collect all the equivalent variables of the given @p variable and return
 * them as a list of @ref VariablePtr.
 *
 * @param variable The variable to find equivalent variables of.
 *
 * @return A @c std::vector of @ref VariablePtr.
 */
std::vector<VariablePtr> equivalentVariables(const VariablePtr &variable);

} // namespace libcellml
