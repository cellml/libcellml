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
limitations under the License.
*/

#ifndef LIBCELLML_LIBCELLML_UNITS_H
#define LIBCELLML_LIBCELLML_UNITS_H

#include <string>

#include "libcellml/libcellml_export.h"
#include "libcellml/types.h"
#include "libcellml/importedentity.h"

namespace libcellml {

/**
 * @file
 * @brief The STANDARD_UNITS.
 *
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
class LIBCELLML_EXPORT Units: public ImportedEntity
{
public:
    Units(); /**< Constructor */
    ~Units(); /**< Destructor */
    Units(const Units &rhs); /**< Copy constructor */
    Units(Units &&rhs); /**< Move constructor */
    Units& operator=(Units n); /**< Assignment operator */

    /**
     * @brief Test to determine if Units is a base unit.
     *
     * Test to determine if Units is a base unit, return @c true if it is
     * a base unit and @c false otherwise.
     *
     * @return @c true if Units is a base unit, @c false otherwise.
     */
    bool isBaseUnit() const;

    /**
     * @brief Set whether this unit is a base unit or not.
     *
     * Set the base unit flag to signify whether this Units is a base unit
     * or not.  This flag cannot be set if this Units is a compound unit.
     *
     * @param state Boolean value to set the base unit flag to.
     */
    void setBaseUnit(bool state=true);

    /**
     * @brief Add a unit to this Units.
     *
     * Add a unit as a child of this Units.  This method takes optional arguments
     * exponent, multiplier and offset.
     *
     * @param name The name of the unit to add.
     * @param prefix The string prefix for the unit.
     * @param exponent The exponent.
     * @param multiplier The multiplier.
     * @param offset The offset.
     */
    void addUnit(const std::string &name, const std::string &prefix, double exponent=1.0,
                 double multiplier=1.0, double offset=0.0);

    /**
     * @brief Add a unit to this Units.
     *
     * Add a unit as a child of this Units.  This method takes optional arguments
     * exponent, multiplier and offset.
     *
     * @overload
     *
     * @param name The name of the unit to add.
     * @param prefix The prefix for the unit, one of Prefix.
     * @param exponent The exponent.
     * @param multiplier The multiplier.
     * @param offset The offset.
     */
    void addUnit(const std::string &name, Prefix prefix, double exponent=1.0,
                 double multiplier=1.0, double offset=0.0);

    /**
     * @brief Add a unit to this Units.
     *
     * Add a unit as a child of this Units.  This method takes optional arguments
     * multiplier and offset.
     *
     * @overload
     *
     * @param name The name of the unit to add.
     * @param prefix The prefix for the unit expressed as a double.
     * @param exponent The exponent.
     * @param multiplier The multiplier.
     * @param offset The offset.
     */
    void addUnit(const std::string &name, double prefix, double exponent,
                 double multiplier=1.0, double offset=0.0);

    /**
     * @brief Add a unit to this Units.
     *
     * Add a unit as a child of this Units. This variant takes the units name
     * and an exponent only.
     *
     * @overload
     *
     * @param name The name of the unit to add.
     * @param exponent The exponent for the unit.
     */
    void addUnit(const std::string &name, double exponent);

    /**
     * @brief Add a unit to this Units.
     *
     * Add a unit as a child of this Units, this variant specified with only a name.
     *
     * @overload
     *
     * @param name The name of the unit to add.
     */
    void addUnit(const std::string &name);

    /**
     * @brief Remove the unit with the given name.
     *
     * Remove the first unit found that matches the name @p name.  If the
     * name is not found throw @c std::out_of_range.
     *
     * @param name The name of the unit to remove.
     */
    void removeUnit(const std::string &name);

    /**
     * @brief Remove all units stored in this units object.
     *
     * Clears all units that have been added to this units object.
     */
    void removeAllUnits();

    /**
     * @brief Set the source of the units for this Units.
     *
     * Make this Units an imported units by defining an import model
     * from which to extract the named Units from.
     *
     * @param imp The import from which the named Units originates.
     * @param name The name of the Units in the imported model to use.
     */
    void setSourceUnits(const ImportPtr &imp, const std::string &name);

    /**
     * @brief Get the number of units that compose this units.
     *
     * Returns the number of units contained by this units object.
     *
     * @return The number of units.
     */
    size_t unitCount() const;

private:
    void swap(Units &rhs); /**< Swap method required for C++ 11 move semantics. */

    std::string doSerialisation(Format format) const;

    struct UnitsImpl; /**< Forward declaration for pImpl idiom. */
    UnitsImpl* mPimpl; /**< Private member to implementation pointer */
};

}

#endif /* LIBCELLML_LIBCELLML_UNITS_H */
