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

#include "libcellml/exportdefinitions.h"
#include "libcellml/importedentity.h"
#include "libcellml/types.h"

#include <string>
#include <vector>

// MSVC (and some other compilers?) may define PASCAL as __stdcall, resulting in
// some compilation errors for our StandardUnit enum class below. However, that
// macro gets defined for backward compatibility, so we can safely undefine it.
// (See https://stackoverflow.com/questions/2774171/what-is-far-pascal for more
// information.)
#undef PASCAL

namespace libcellml {

/**
 * @brief The Units class.
 * Class for Units.
 */
class LIBCELLML_EXPORT Units: public NamedEntity, public ImportedEntity
{
public:
    ~Units() override; /**< Destructor */
    Units(const Units &rhs) = delete; /**< Copy constructor */
    Units(Units &&rhs) noexcept = delete; /**< Move constructor */
    Units &operator=(Units rhs) = delete; /**< Assignment operator */

    /**
     * @brief Create a @c Units object.
     *
     * Factory method to create a @c Units.  Create a
     * blank units with::
     *
     *   UnitsPtr units = libcellml::Units::create();
     *
     * or a named units with name "Units" with::
     *
     *   UnitsPtr units = libcellml::Units::create(std::string("Units"));
     *
     * @return A smart pointer to a @c Units object.
     */
    static UnitsPtr create() noexcept;

    /**
     * @overload static UnitsPtr create() noexcept
     */
    static UnitsPtr create(const std::string &name) noexcept;

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
        COULOMB, /**< Derived SI unit coulomb. */
        DIMENSIONLESS, /**< Convenience unit dimensionless. */
        FARAD, /**< Derived SI unit farad. */
        GRAM, /**< Convenience unit gram. */
        GRAY, /**< Derived SI unit gray. */
        HENRY, /**< Derived SI unit henry. */
        HERTZ, /**< Derived SI unit hertz. */
        JOULE, /**< Derived SI unit joule. */
        KATAL, /**< Derived SI unit katal. */
        KELVIN, /**< Base SI unit kelvin. */
        KILOGRAM, /**< Base SI unit kilogram. */
        LITRE, /**< Convenience unit litre. */
        LUMEN, /**< Derived SI unit lumen. */
        LUX, /**< Derived SI unit lux. */
        METRE, /**< Base SI unit metre. */
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
     * a base unit and @c false otherwise. A unit is an "irreducible unit"
     * or "base unit" for the model by virtue of the fact that it is not
     * derived from any other unit(s).
     *
     * @return @c true if Units is a base unit, @c false otherwise.
     */
    bool isBaseUnit() const;

    /**
     * @brief Add a unit to this Units.
     *
     * Add a unit as a child of this Units.  This method takes optional arguments
     * @p exponent, and @p multiplier.
     *
     * @param reference The @c std::string units reference to add.
     * @param prefix The string prefix for the unit.
     * @param exponent The exponent.
     * @param multiplier The multiplier.
     * @param id The optional @c std::string id to set for this unit.
     */
    void addUnit(const std::string &reference, const std::string &prefix, double exponent = 1.0,
                 double multiplier = 1.0, const std::string &id = "");

    /**
     * @brief Add a unit to this Units.
     *
     * Add a unit as a child of this Units.  This method takes optional arguments
     * @p exponent, and @p multiplier.
     *
     * @overload void addUnit(const std::string &reference, const std::string &prefix, double exponent = 1.0,
     *           double multiplier = 1.0, const std::string &id = "")
     *
     * @param reference The @c std::string units reference to add.
     * @param prefix The prefix for the unit, one of Prefix.
     * @param exponent The exponent.
     * @param multiplier The multiplier.
     * @param id The optional @c std::string id to set for this unit.
     */
    void addUnit(const std::string &reference, Prefix prefix, double exponent = 1.0,
                 double multiplier = 1.0, const std::string &id = "");

    /**
     * @brief Add a unit to this Units.
     *
     * Add a unit as a child of this Units. This method takes an optional argument
     * @p multiplier.
     *
     * @overload void addUnit(const std::string &reference, const std::string &prefix, double exponent = 1.0,
     *           double multiplier = 1.0, const std::string &id = "")
     *
     * @param reference The @c std::string units reference to add.
     * @param prefix The prefix for the unit expressed as a double.
     * @param exponent The exponent.
     * @param multiplier The multiplier.
     * @param id The optional @c std::string id to set for this unit.
     */
    void addUnit(const std::string &reference, int prefix, double exponent,
                 double multiplier = 1.0, const std::string &id = "");

    /**
     * @brief Add a unit to this Units.
     *
     * Add a unit as a child of this Units. This variant takes the @c std::string
     * units @p reference and an @p exponent only.
     *
     * @overload void addUnit(const std::string &reference, const std::string &prefix, double exponent = 1.0,
     *           double multiplier = 1.0, const std::string &id = "")
     *
     * @param reference The @c std::string units reference to add.
     * @param exponent The exponent for the unit.
     * @param id The optional @c std::string id to set for this unit.
     */
    void addUnit(const std::string &reference, double exponent, const std::string &id = "");

    /**
     * @brief Add a unit to this Units.
     *
     * Add a unit as a child of this Units, this variant specified with only a
     * @c std::string units @p reference.
     *
     * @overload void addUnit(const std::string &reference, const std::string &prefix, double exponent = 1.0,
     *           double multiplier = 1.0, const std::string &id = "")
     *
     * @param reference The @c std::string units reference to add.
     */
    void addUnit(const std::string &reference);

    /**
     * @brief Add a unit to this Units.
     *
     * Add a unit as a child of this Units.  This method takes optional arguments
     * @p exponent, and @p multiplier.
     *
     * @overload void addUnit(const std::string &reference, const std::string &prefix, double exponent = 1.0,
     *           double multiplier = 1.0, const std::string &id = "")
     *
     * @param standardRef The @c StandardUnit enum units reference to add.
     * @param prefix The string prefix for the unit.
     * @param exponent The exponent.
     * @param multiplier The multiplier.
     * @param id The optional @c std::string id to set for this unit.
     */
    void addUnit(StandardUnit standardRef, const std::string &prefix, double exponent = 1.0,
                 double multiplier = 1.0, const std::string &id = "");

    /**
     * @brief Add a unit to this Units.
     *
     * Add a unit as a child of this Units.  This method takes optional arguments
     * @p exponent, and @p multiplier.
     *
     * @overload void addUnit(const std::string &reference, const std::string &prefix, double exponent = 1.0,
     *           double multiplier = 1.0, const std::string &id = "")
     *
     * @param standardRef The @c StandardUnit enum units reference to add.
     * @param prefix The prefix for the unit, one of Prefix.
     * @param exponent The exponent.
     * @param multiplier The multiplier.
     * @param id The optional @c std::string id to set for this unit.
     */
    void addUnit(StandardUnit standardRef, Prefix prefix, double exponent = 1.0,
                 double multiplier = 1.0, const std::string &id = "");

    /**
     * @brief Add a unit to this Units.
     *
     * Add a unit as a child of this Units. This method takes an optional argument
     * @p multiplier.
     *
     * @overload void addUnit(const std::string &reference, const std::string &prefix, double exponent = 1.0,
     *           double multiplier = 1.0, const std::string &id = "")
     *
     * @param standardRef The @c StandardUnit enum units reference to add.
     * @param prefix The prefix for the unit expressed as a double.
     * @param exponent The exponent.
     * @param multiplier The multiplier.
     * @param id The optional @c std::string id to set for this unit.
     */
    void addUnit(StandardUnit standardRef, int prefix, double exponent,
                 double multiplier = 1.0, const std::string &id = "");

    /**
     * @brief Add a unit to this Units.
     *
     * Add a unit as a child of this Units. This variant takes the @c StandardUnit enum
     * units @p reference and an @p exponent only.
     *
     * @overload void addUnit(const std::string &reference, const std::string &prefix, double exponent = 1.0,
     *           double multiplier = 1.0, const std::string &id = "")
     *
     * @param standardRef The @c StandardUnit enum units reference to add.
     * @param exponent The exponent for the unit.
     * @param id The optional @c std::string id to set for this unit.
     */
    void addUnit(StandardUnit standardRef, double exponent, const std::string &id = "");

    /**
     * @brief Add a unit to this Units.
     *
     * Add a unit as a child of this Units, this variant specified with only a
     * @c StandardUnit enum units @p reference.
     *
     * @overload void addUnit(const std::string &reference, const std::string &prefix, double exponent = 1.0,
     *           double multiplier = 1.0, const std::string &id = "")
     *
     * @param standardRef The @c StandardUnit enum units reference to add.
     */
    void addUnit(StandardUnit standardRef);

    /**
     * @brief Get the @c unit attributes at the given @p index of this units.
     *
     * Get the attributes for the @c unit at the index @p index of this units. If
     * no attributes are set, default attribute values will be returned. The index must
     * be in the range [0, \#unit).
     *
     * @param index The index of the @c unit in this units to get attributes for.
     * @param reference The @c std::string reference for this @c unit. Defaults to empty string.
     * @param prefix The prefix for this @c unit. Defaults to empty string.
     * @param exponent The exponent for this @c unit. Defaults to 1.0.
     * @param multiplier The multiplier for this @c unit. Defaults to 1.0.
     * @param id The @c std::string id for this @c unit. Defaults to the empty string.
     */
    void unitAttributes(size_t index, std::string &reference, std::string &prefix, double &exponent,
                        double &multiplier, std::string &id) const;

    /**
     * @brief Get the @c unit attributes for the given @p reference.
     *
     * Get the attributes for the first @c unit that matches the reference @p reference. If
     * no attributes are set, default attribute values will be returned.
     *
     * @overload void unitAttributes(size_t index, std::string &reference, std::string &prefix, double &exponent,
     *                  double &multiplier, std::string &id) const
     *
     * @param reference The @c std::string reference for the @c unit attributes to get.
     * @param prefix The prefix for this @c unit. Defaults to empty string.
     * @param exponent The exponent for this @c unit. Defaults to 1.0.
     * @param multiplier The multiplier for this @c unit. Defaults to 1.0.
     * @param id The @c std::string id for this @c unit. Defaults to the empty string.
     */
    void unitAttributes(const std::string &reference, std::string &prefix, double &exponent, double &multiplier, std::string &id) const;

    /**
     * @brief Get the @c unit attributes for the given @p standardRef.
     *
     * Get the attributes for the first @c unit that matches the reference @p standardRef. If
     * no attributes are set, default attribute values will be returned.
     *
     * @overload void unitAttributes(size_t index, std::string &reference, std::string &prefix, double &exponent,
     *                  double &multiplier, std::string &id) const
     *
     * @param standardRef The @c StandardUnit enum unit reference attributes to get.
     * @param prefix The prefix for this @c unit. Defaults to empty string.
     * @param exponent The exponent for this @c unit. Defaults to 1.0.
     * @param multiplier The multiplier for this @c unit. Defaults to 1.0.
     * @param id The @c std::string id for this @c unit. Defaults to the empty string.
     */
    void unitAttributes(StandardUnit standardRef, std::string &prefix, double &exponent, double &multiplier, std::string &id) const;

    /**
     * @brief Remove the unit at the given @p index.
     *
     * Removes the unit at the given @p index position.
     * @p index must be in the range [0, \#unit).
     *
     * @param index The index of the unit to remove.
     *
     * @return True if the units were replaced, false otherwise.
     */
    bool removeUnit(size_t index);

    /**
     * @brief Remove the unit with the given reference.
     *
     * Remove the first unit found that matches the @c std::string reference @p reference.
     *
     * @overload bool removeUnit(size_t index)
     *
     * @param reference The @c std::string unit reference of the unit to remove.
     *
     * @return True if the units were replaced, false otherwise.
     */
    bool removeUnit(const std::string &reference);

    /**
     * @brief Remove the unit with the given reference.
     *
     * Remove the first unit found that matches @c StandardUnit enum reference @p reference.
     *
     * @overload bool removeUnit(size_t index)
     *
     * @param standardRef The @c StandardUnit enum unit reference of the unit to remove.
     *
     * @return True if the units were replaced, false otherwise.
     */
    bool removeUnit(StandardUnit standardRef);

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
     * @param importSource The import source from which the named Units originates.
     * @param name The name of the Units in the imported model to use.
     */
    void setSourceUnits(const ImportSourcePtr &importSource, const std::string &name);

    /**
     * @brief Get the number of units that compose this units.
     *
     * Returns the number of units contained by this units object.
     *
     * @return The number of units.
     */
    size_t unitCount() const;

    /**
     * @brief Return the scaling factor difference between two units.
     * 
     * This can be interpreted as factor, where units2 = (factor)*units1.  This method
     * does not check to see if the units are compatible.
     * 
     * @param units1 The first units to compare.
     * @param units2 The second units to compare.
     *
     * @return The factor units1/units2.
     */
    static double scalingFactor(const UnitsPtr &units1, const UnitsPtr &units2);

private:
    Units(); /**< Constructor */
    explicit Units(const std::string &name); /**< Constructor with std::string parameter*/

    struct UnitsImpl; /**< Forward declaration for pImpl idiom. */
    UnitsImpl *mPimpl; /**< Private member to implementation pointer */
};

} // namespace libcellml
