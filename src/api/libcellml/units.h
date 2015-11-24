/*
Copyright 2015 University of Auckland

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.Some license of other
*/

#ifndef LIBCELLML_LIBCELLML_UNITS_H
#define LIBCELLML_LIBCELLML_UNITS_H

#include <string>

#include "libcellml/libcellml_export.h"
#include "libcellml/types.h"
#include "libcellml/namedentity.h"

namespace libcellml {

/**
 * @brief The STANDARD_UNITS.
 * Strings describing the standard units that are suitable for variable declarations
 * or attached to bare numbers in mathematics.  The list of strings comprises of
 * the SI base units, the SI derived units with special names and symbols, and
 * some additional units commonly used in the types of biological models likely
 * to be defined using CellML.
 */

const std::string STANDARD_UNIT_AMPERE = "ampere"; /**< Base SI unit ampere. */
const std::string STANDARD_UNIT_BECQUEREL = "becquerel"; /**< Derived SI unit becquerel. */
const std::string STANDARD_UNIT_CANDELA = "candela"; /**< Base SI unit candela. */
const std::string STANDARD_UNIT_CELSIUS = "celsius"; /**< Derived SI unit celsius. */
const std::string STANDARD_UNIT_COULOMB = "coulomb"; /**< Derived SI unit coulomb. */
const std::string STANDARD_UNIT_DIMENSIONLESS = "dimensionless"; /**< Convenience unit dimensionless. */
const std::string STANDARD_UNIT_FARAD = "farad"; /**< Derived SI unit farad. */
const std::string STANDARD_UNIT_GRAM = "gram"; /**< Convenience unit gram. */
const std::string STANDARD_UNIT_GRAY = "gray"; /**< Derived SI unit gray. */
const std::string STANDARD_UNIT_HENRY = "henry"; /**< Derived SI unit henry. */
const std::string STANDARD_UNIT_HERTZ = "hertz"; /**< Derived SI unit hertz. */
const std::string STANDARD_UNIT_JOULE = "joule"; /**< Derived SI unit joule. */
const std::string STANDARD_UNIT_KATAL = "katal"; /**< Derived SI unit katal. */
const std::string STANDARD_UNIT_KELVIN = "kelvin"; /**< Base SI unit kelvin. */
const std::string STANDARD_UNIT_KILOGRAM = "kilogram"; /**< Base SI unit kilogram. */
const std::string STANDARD_UNIT_LITER = "liter"; /**< Convenience unit liter (alternative spelling). */
const std::string STANDARD_UNIT_LITRE = "litre"; /**< Convenience unit litre. */
const std::string STANDARD_UNIT_LUMEN = "lumen"; /**< Derived SI unit lumen. */
const std::string STANDARD_UNIT_LUX = "lux"; /**< Derived SI unit lux. */
const std::string STANDARD_UNIT_METER = "meter"; /**< Base SI unit meter. */
const std::string STANDARD_UNIT_METRE = "metre"; /**< Base SI unit metre (alternative spelling). */
const std::string STANDARD_UNIT_MOLE = "mole"; /**< Base SI unit mole. */
const std::string STANDARD_UNIT_NEWTON = "newton"; /**< Derived SI unit newton. */
const std::string STANDARD_UNIT_OHM = "ohm"; /**< Derived SI unit ohm. */
const std::string STANDARD_UNIT_PASCAL = "pascal"; /**< Derived SI unit pascal. */
const std::string STANDARD_UNIT_RADIAN = "radian"; /**< Derived SI unit radian. */
const std::string STANDARD_UNIT_SECOND = "second"; /**< Base SI unit second. */
const std::string STANDARD_UNIT_SIEMENS = "siemens"; /**< Derived SI unit siemens. */
const std::string STANDARD_UNIT_SIEVERT = "sievert"; /**< Derived SI unit sievert. */
const std::string STANDARD_UNIT_STERADIAN = "steradian"; /**< Derived SI unit steradian. */
const std::string STANDARD_UNIT_TESLA = "tesla"; /**< Derived SI unit tesla. */
const std::string STANDARD_UNIT_VOLT = "volt"; /**< Derived SI unit volt. */
const std::string STANDARD_UNIT_WATT = "watt"; /**< Derived SI unit watt. */
const std::string STANDARD_UNIT_WEBER = "weber"; /**< Derived SI unit weber. */

/**
 * @brief The Units class.
 * Class for Units.
 */
class LIBCELLML_EXPORT Units: public NamedEntity
{
public:
    Units(); /**< Constructor */
    ~Units(); /**< Destructor */
    Units(const Units &rhs); /**< Copy constructor */
    Units(Units &&rhs); /**< Move constructor */
    Units& operator=(Units n); /**< Assignment operator */

    /**
     * @brief Test to determine if Units is a base unit.
     * Test to determine if Units is a base unit, return True if it is
     * a base unit and False otherwise.
     * @return True if Units is a base unit, False otherwise.
     */
    bool isBaseUnit() const;

    /**
     * @brief Set whether this unit is a base unit or not.
     * Set the base unit flag to signify whether this Units is a base unit
     * or not.  This flag cannot be set if this Units is a compound unit.
     * @param state boolean value to set the base unit flag to.
     */
    void setBaseUnit(bool state=true);

    /**
     * @brief Add a unit to this Units.
     * Add a unit as a child of this Units.  This method takes optional arguments
     * multiplier and offset.
     * @param units The name of the unit to add.
     * @param prefix The prefix for the unit, one of PREFIXES.
     * @param exponent The exponent.
     * @param multiplier The multiplier.
     * @param offset The offset.
     */
    void addUnit(const std::string &units, PREFIXES prefix, double exponent=1.0,
                 double multiplier=1.0, double offset=0.0);

    /**
     * @brief Add a unit to this Units.
     * Add a unit as a child of this Units.  This method takes optional arguments
     * multiplier and offset.
     *
     * @overload
     * @param units The name of the unit to add.
     * @param prefix The prefix for the unit expressed as an integer.
     * @param exponent The exponent.
     * @param multiplier The multiplier.
     * @param offset The offset.
     */
    void addUnit(const std::string &units, int prefix, double exponent=1.0,
                 double multiplier=1.0, double offset=0.0);

    /**
     * @brief Add a unit to this Units.
     * Add a unit as a child of this Units. This variant takes the units name
     * and an exponent only.
     *
     * @overload
     * @param units The name of the unit to add.
     * @param exponent The exponent for the unit.
     */
    void addUnit(const std::string &units, double exponent);

    /**
     * @brief Add a unit to this Units.
     * Add a unit as a child of this Units, this variant specified with only a name.
     *
     * @overload
     * @param units The name of the unit to add.
     */
    void addUnit(const std::string &units);

private:
    void swap(Units &rhs); /**< Swap method required for C++ 11 move semantics. */

    std::string doSerialisation(libcellml::FORMATS format) const;

    struct UnitsImpl; /**< Forward declaration for pImpl idiom. */
    UnitsImpl* mPimpl; /**< Private member to implementation pointer */
};

}

#endif /* LIBCELLML_LIBCELLML_UNITS_H */
