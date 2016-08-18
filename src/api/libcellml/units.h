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
#include <vector>

#include "libcellml/importedentity.h"
#include "libcellml/exportdefinitions.h"
#include "libcellml/types.h"

namespace libcellml { 

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
     * @brief The Standard Unit enum class.
     *
     * Standard units that are suitable for variable declarations
     * or attached to bare numbers in mathematics.  This list of comprises
     * the SI base units, the SI derived units with special names and symbols, and
     * some additional units commonly used in the types of biological models likely
     * to be defined using CellML.
     */
    enum class StandardUnit
    {
        AMPERE, /**< Base SI unit ampere. */
        BECQUEREL, /**< Derived SI unit becquerel. */
        CANDELA, /**< Base SI unit candela. */
        CELSIUS, /**< Derived SI unit celsius. */
        COULOMB, /**< Derived SI unit coulomb. */
        DIMENSIONLESS, /**< Convenience unit dimensionless. */
        FARAD, /**< Derived SI unit farad. */
        GRAM, /**< Convenience unit gram. */
        GRAY, /**< Derived SI unit gray. */
        HENRY, /**< Derived SI unit henry. */
        HERTZ, /**< Derived SI unit hertz. */
        JOULE, /**< Derived SI unit joule. */
        KATAL,  /**< Derived SI unit katal. */
        KELVIN, /**< Base SI unit kelvin. */
        KILOGRAM, /**< Base SI unit kilogram. */
        LITER, /**< Convenience unit liter (alternative spelling). */
        LITRE, /**< Convenience unit litre. */
        LUMEN, /**< Derived SI unit lumen. */
        LUX, /**< Derived SI unit lux. */
        METER, /**< Base SI unit meter. */
        METRE, /**< Base SI unit metre (alternative spelling). */
        MOLE, /**< Base SI unit mole. */
        NEWTON, /**< Derived SI unit newton. */
        OHM, /**< Derived SI unit ohm. */
        PASCAL, /**< Derived SI unit pascal. */
        RADIAN, /**< Derived SI unit radian. */
        SECOND, /**< Base SI unit second. */
        SIEMENS, /**< Derived SI unit siemens. */
        SIEVERT, /**< Derived SI unit sievert. */
        STERADIAN, /**< Derived SI unit steradian. */
        TESLA, /**< Derived SI unit tesla. */
        VOLT, /**< Derived SI unit volt. */
        WATT, /**< Derived SI unit watt. */
        WEBER /**< Derived SI unit weber. */
    };

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
     * @p exponent, @p multiplier and @p offset.
     *
     * @param reference The @c std::string units reference to add.
     * @param prefix The string prefix for the unit.
     * @param exponent The exponent.
     * @param multiplier The multiplier.
     * @param offset The offset.
     */
    void addUnit(const std::string &reference, const std::string &prefix, double exponent=1.0,
                 double multiplier=1.0, double offset=0.0);

    /**
     * @brief Add a unit to this Units.
     *
     * Add a unit as a child of this Units.  This method takes optional arguments
     * @p exponent, @p multiplier and @p offset.
     *
     * @overload
     *
     * @param reference The @c std::string units reference to add.
     * @param prefix The prefix for the unit, one of Prefix.
     * @param exponent The exponent.
     * @param multiplier The multiplier.
     * @param offset The offset.
     */
    void addUnit(const std::string &reference, Prefix prefix, double exponent=1.0,
                 double multiplier=1.0, double offset=0.0);

    /**
     * @brief Add a unit to this Units.
     *
     * Add a unit as a child of this Units. This method takes optional arguments
     * @p multiplier and @p offset.
     *
     * @overload
     *
     * @param reference The @c std::string units reference to add.
     * @param prefix The prefix for the unit expressed as a double.
     * @param exponent The exponent.
     * @param multiplier The multiplier.
     * @param offset The offset.
     */
    void addUnit(const std::string &reference, double prefix, double exponent,
                 double multiplier=1.0, double offset=0.0);

    /**
     * @brief Add a unit to this Units.
     *
     * Add a unit as a child of this Units. This variant takes the @c std::string
     * units @p reference and an @p exponent only.
     *
     * @overload
     *
     * @param reference The @c std::string units reference to add.
     * @param exponent The exponent for the unit.
     */
    void addUnit(const std::string &reference, double exponent);

    /**
     * @brief Add a unit to this Units.
     *
     * Add a unit as a child of this Units, this variant specified with only a
     * @c std::string units @p reference.
     *
     * @overload
     *
     * @param reference The @c std::string units reference to add.
     */
    void addUnit(const std::string &reference);

    /**
     * @brief Add a unit to this Units.
     *
     * Add a unit as a child of this Units.  This method takes optional arguments
     * @p exponent, @p multiplier and @p offset.
     *
     * @overload
     *
     * @param standardRef The @c StandardUnit enum units reference to add.
     * @param prefix The string prefix for the unit.
     * @param exponent The exponent.
     * @param multiplier The multiplier.
     * @param offset The offset.
     */
    void addUnit(StandardUnit standardRef, const std::string &prefix, double exponent=1.0,
                 double multiplier=1.0, double offset=0.0);

    /**
     * @brief Add a unit to this Units.
     *
     * Add a unit as a child of this Units.  This method takes optional arguments
     * @p exponent, @p multiplier and @p offset.
     *
     * @overload
     *
     * @param standardRef The @c StandardUnit enum units reference to add.
     * @param prefix The prefix for the unit, one of Prefix.
     * @param exponent The exponent.
     * @param multiplier The multiplier.
     * @param offset The offset.
     */
    void addUnit(StandardUnit standardRef, Prefix prefix, double exponent=1.0,
                 double multiplier=1.0, double offset=0.0);

    /**
     * @brief Add a unit to this Units.
     *
     * Add a unit as a child of this Units. This method takes optional arguments
     * @p multiplier and @p offset.
     *
     * @overload
     *
     * @param standardRef The @c StandardUnit enum units reference to add.
     * @param prefix The prefix for the unit expressed as a double.
     * @param exponent The exponent.
     * @param multiplier The multiplier.
     * @param offset The offset.
     */
    void addUnit(StandardUnit standardRef, double prefix, double exponent,
                 double multiplier=1.0, double offset=0.0);

    /**
     * @brief Add a unit to this Units.
     *
     * Add a unit as a child of this Units. This variant takes the @c StandardUnit enum
     * units @p reference and an @p exponent only.
     *
     * @overload
     *
     * @param standardRef The @c StandardUnit enum units reference to add.
     * @param exponent The exponent for the unit.
     */
    void addUnit(StandardUnit standardRef, double exponent);

    /**
     * @brief Add a unit to this Units.
     *
     * Add a unit as a child of this Units, this variant specified with only a
     * @c StandardUnit enum units @p reference.
     *
     * @overload
     *
     * @param standardRef The @c StandardUnit enum units reference to add.
     */
    void addUnit(StandardUnit standardRef);

    /**
     * @brief Get the @c unit attributes at the given @p index of this units.
     *
     * Get the attributes for the @c unit at the index @p index of this units. If
     * no attributes are set, default attribute values will be returned.
     *
     * @param index The index of the @c unit in this units to get attributes for.
     * @param reference The @c std::string reference for this @c unit. Defaults to empty string.
     * @param prefix The prefix for this @c unit. Defaults to empty string.
     * @param exponent The exponent for this @c unit. Defaults to 1.0.
     * @param multiplier The multiplier for this @c unit. Defaults to 1.0.
     * @param offset The offset for this @c unit. Defaults to 0.0.
     */
    void getUnit(size_t index, std::string& reference, std::string &prefix, double &exponent, double &multiplier, double &offset);

    /**
     * @brief Remove the unit with the given reference.
     *
     * Remove the first unit found that matches the @c std::string reference @p reference.
     * If the @p reference is not found throw @c std::out_of_range.
     *
     * @param reference The @c std::string units reference to remove.
     */
    void removeUnit(const std::string &reference);

    /**
     * @brief Remove the unit with the given reference.
     *
     * Remove the first unit found that matches @c StandardUnit enum reference @p reference.
     * If the @p reference is not found throw @c std::out_of_range.
     *
     * @param reference The @c StandardUnit enum units reference to remove.
     */
    void removeUnit(StandardUnit standardRef);

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
    UnitsImpl *mPimpl; /**< Private member to implementation pointer */
};

}
