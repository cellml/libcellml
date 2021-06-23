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

#include "libcellml/units.h"

#include "namedentity_p.h"
#include "utilities.h"

namespace libcellml {

/**
 * @brief Map Prefix to their string forms.
 *
 * An internal map used to convert a Prefix into its string form.
 */
static const std::map<Units::Prefix, const std::string> prefixToString = {
    {Units::Prefix::ATTO, "atto"},
    {Units::Prefix::CENTI, "centi"},
    {Units::Prefix::DECA, "deca"},
    {Units::Prefix::DECI, "deci"},
    {Units::Prefix::EXA, "exa"},
    {Units::Prefix::FEMTO, "femto"},
    {Units::Prefix::GIGA, "giga"},
    {Units::Prefix::HECTO, "hecto"},
    {Units::Prefix::KILO, "kilo"},
    {Units::Prefix::MEGA, "mega"},
    {Units::Prefix::MICRO, "micro"},
    {Units::Prefix::MILLI, "milli"},
    {Units::Prefix::NANO, "nano"},
    {Units::Prefix::PETA, "peta"},
    {Units::Prefix::PICO, "pico"},
    {Units::Prefix::TERA, "tera"},
    {Units::Prefix::YOCTO, "yocto"},
    {Units::Prefix::YOTTA, "yotta"},
    {Units::Prefix::ZEPTO, "zepto"},
    {Units::Prefix::ZETTA, "zetta"}};

/**
 * @brief Map StandardUnit to their string forms.
 *
 * An internal map used to convert a standard unit into its string form.
 */
static const std::map<Units::StandardUnit, const std::string> standardUnitToString = {
    {Units::StandardUnit::AMPERE, "ampere"},
    {Units::StandardUnit::BECQUEREL, "becquerel"},
    {Units::StandardUnit::CANDELA, "candela"},
    {Units::StandardUnit::COULOMB, "coulomb"},
    {Units::StandardUnit::DIMENSIONLESS, "dimensionless"},
    {Units::StandardUnit::FARAD, "farad"},
    {Units::StandardUnit::GRAM, "gram"},
    {Units::StandardUnit::GRAY, "gray"},
    {Units::StandardUnit::HENRY, "henry"},
    {Units::StandardUnit::HERTZ, "hertz"},
    {Units::StandardUnit::JOULE, "joule"},
    {Units::StandardUnit::KATAL, "katal"},
    {Units::StandardUnit::KELVIN, "kelvin"},
    {Units::StandardUnit::KILOGRAM, "kilogram"},
    {Units::StandardUnit::LITRE, "litre"},
    {Units::StandardUnit::LUMEN, "lumen"},
    {Units::StandardUnit::LUX, "lux"},
    {Units::StandardUnit::METRE, "metre"},
    {Units::StandardUnit::MOLE, "mole"},
    {Units::StandardUnit::NEWTON, "newton"},
    {Units::StandardUnit::OHM, "ohm"},
    {Units::StandardUnit::PASCAL, "pascal"},
    {Units::StandardUnit::RADIAN, "radian"},
    {Units::StandardUnit::SECOND, "second"},
    {Units::StandardUnit::SIEMENS, "siemens"},
    {Units::StandardUnit::SIEVERT, "sievert"},
    {Units::StandardUnit::STERADIAN, "steradian"},
    {Units::StandardUnit::TESLA, "tesla"},
    {Units::StandardUnit::VOLT, "volt"},
    {Units::StandardUnit::WATT, "watt"},
    {Units::StandardUnit::WEBER, "weber"}};

/**
 * @brief The UnitDefinition struct.
 *
 * An internal structure to capture a unit definition.  The
 * prefix can be expressed using either an integer or an enum.
 * The enum structure member is given preference if both are set.
 */
struct UnitDefinition
{
    std::string mReference; /**< Reference to the units for the unit.*/
    std::string mPrefix; /**< String expression of the prefix for the unit.*/
    double mExponent = 1.0; /**< Exponent for the unit.*/
    double mMultiplier = 1.0; /**< Multiplier for the unit.*/
    std::string mId; /**< Identifier for the unit.*/
};

/**
 * @brief The Units::UnitsImpl struct.
 *
 * The private implementation for the Units class.
 */
class Units::UnitsImpl : public NamedEntityImpl
{
public:
    std::vector<UnitDefinition> mUnitDefinitions; /**< A vector of unit defined for this Units.*/

    std::vector<UnitDefinition>::const_iterator findUnit(const std::string &reference) const;

    /**
     * @brief Test if this units is a standard unit that is a base unit.
     *
     * Only tests if the name of the units matches a standard unit name
     * that is a base units.  Returns @c true if the unit name does match
     * a base units name and @c false otherwise.
     *
     * @param name The name of the units.
     *
     * @return @c true if the name of the units is one of: "ampere",
     * "candela", "dimensionless", "kelvin", "kilogram", "metre", "mole" , "second".
     */
    bool isBaseUnit(const std::string &name) const;

    bool isBaseUnitWithHistory(History &history, const UnitsConstPtr &units) const;

    bool isResolvedWithHistory(History &history, const UnitsConstPtr &units) const;

    Units *mUnits = nullptr;
};

} // namespace libcellml
