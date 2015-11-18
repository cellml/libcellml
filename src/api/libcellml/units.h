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
    void addUnit(const std::string &units, PREFIXES prefix, double exponent,
                 double multiplier=1.0, double offset=0.0);

    /**
     * @brief Add a unit to this Units.
     * Add a unit as a child of this Units.  This method takes optional arguments
     * multiplier and offset.
     *
     * @overload
     * @param units The enum representing the unit to add.
     * @param prefix The prefix for the unit, one of PREFIXES.
     * @param exponent The exponent.
     * @param multiplier The multiplier.
     * @param offset The offset.
     */
    void addUnit(STANDARD_UNITS units, PREFIXES prefix, double exponent,
                 double multiplier=1.0, double offset=0.0);

    /**
     * @brief Add a unit to this Units.
     * Add a unit as a child of this Units. This variant takes the units name
     * and prefix only.
     *
     * @overload
     * @param units The name of the unit to add.
     * @param prefix The prefix for the unit, one of PREFIXES.
     */
    void addUnit(const std::string &units, PREFIXES prefix);

    /**
     * @brief Add a unit to this Units.
     * Add a unit as a child of this Units. This variant takes the units name
     * specified as an enum and a prefix only.
     *
     * @overload
     * @param units The enum representing the unit to add.
     * @param prefix The prefix for the unit, one of PREFIXES.
     */
    void addUnit(STANDARD_UNITS units, PREFIXES prefix);

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
     * Add a unit as a child of this Units. This variant takes the units
     * name specified with an enum and an exponent.
     *
     * @overload
     * @param units The enum representing the unit to add.
     * @param exponent The exponent for the unit.
     */
    void addUnit(STANDARD_UNITS units, double exponent);

    /**
     * @brief Add a unit to this Units.
     * Add a unit as a child of this Units, this variant specified with only a name.
     *
     * @overload
     * @param units The name of the unit to add.
     */
    void addUnit(const std::string &units);

    /**
     * @brief Add a unit to this Units.
     * Add a unit as a child of this Units, this variant specified with only an enum
     * representing the name.
     *
     * @overload
     * @param units The enum representing the unit to add.
     */
    void addUnit(STANDARD_UNITS units);

private:
    void swap(Units &rhs); /**< Swap method required for C++ 11 move semantics. */

    struct UnitsImpl; /**< Forward declaration for pImpl idiom. */
    UnitsImpl* mPimpl; /**< Private member to implementation pointer */
};

}

#endif /* LIBCELLML_LIBCELLML_UNITS_H */
