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

#include "libcellml/exportdefinitions.h"
#include "libcellml/importedentity.h"
#include "libcellml/types.h"

// MSVC (and some other compilers?) may define PASCAL as __stdcall, resulting in
// some compilation errors for our StandardUnit enum class below. However, that
// macro gets defined for backward compatibility, so we can safely undefine it.
// (See https://stackoverflow.com/questions/2774171/what-is-far-pascal for more
// information.)
#ifdef PASCAL
#    undef PASCAL
#endif

#ifndef SWIG
template class LIBCELLML_EXPORT std::weak_ptr<libcellml::Units>;
#endif

namespace libcellml {

/**
 * @brief The Units class.
 * Class for Units.
 */
class LIBCELLML_EXPORT Units: public NamedEntity, public ImportedEntity
#ifndef SWIG
    ,
                              public std::enable_shared_from_this<Units>
#endif
{
public:
    ~Units() override; /**< Destructor. */
    Units(const Units &rhs) = delete; /**< Copy constructor. */
    Units(Units &&rhs) noexcept = delete; /**< Move constructor. */
    Units &operator=(Units rhs) = delete; /**< Assignment operator. */

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
     *   UnitsPtr units = libcellml::Units::create("Units");
     *
     * @return A smart pointer to a @c Units object.
     */
    static UnitsPtr create() noexcept;

    /**
     * @overload
     */
    static UnitsPtr create(const std::string &name) noexcept;

    /**
     * @brief The Prefix enum class.
     *
     * Enum describing the prefixes that are available for
     * units.
     */
    enum class Prefix
    {
        YOTTA,
        ZETTA,
        EXA,
        PETA,
        TERA,
        GIGA,
        MEGA,
        KILO,
        HECTO,
        DECA,
        DECI,
        CENTI,
        MILLI,
        MICRO,
        NANO,
        PICO,
        FEMTO,
        ATTO,
        ZEPTO,
        YOCTO
    };

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
     * @overload
     *
     * @brief Add a unit to this Units.
     *
     * Add a unit as a child of this Units.  This method takes optional arguments
     * @p exponent, and @p multiplier.
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
     * @overload
     *
     * @brief Add a unit to this Units.
     *
     * Add a unit as a child of this Units. This method takes an optional argument
     * @p multiplier.
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
     * @overload
     *
     * @brief Add a unit to this Units.
     *
     * Add a unit as a child of this Units. This variant takes the @c std::string
     * units @p reference and an @p exponent only.
     *
     * @param reference The @c std::string units reference to add.
     * @param exponent The exponent for the unit.
     * @param id The optional @c std::string id to set for this unit.
     */
    void addUnit(const std::string &reference, double exponent, const std::string &id = "");

    /**
     * @overload
     *
     * @brief Add a unit to this Units.
     *
     * Add a unit as a child of this Units, this variant specified with only a
     * @c std::string units @p reference.
     *
     * @param reference The @c std::string units reference to add.
     */
    void addUnit(const std::string &reference);

    /**
     * @overload
     *
     * @brief Add a unit to this Units.
     *
     * Add a unit as a child of this Units.  This method takes optional arguments
     * @p exponent, and @p multiplier.
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
     * @overload
     *
     * @brief Add a unit to this Units.
     *
     * Add a unit as a child of this Units.  This method takes optional arguments
     * @p exponent, and @p multiplier.
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
     * @overload
     *
     * @brief Add a unit to this Units.
     *
     * Add a unit as a child of this Units. This method takes an optional argument
     * @p multiplier.
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
     * @overload
     *
     * @brief Add a unit to this Units.
     *
     * Add a unit as a child of this Units. This variant takes the @c StandardUnit enum
     * units @p reference and an @p exponent only.
     *
     * @param standardRef The @c StandardUnit enum units reference to add.
     * @param exponent The exponent for the unit.
     * @param id The optional @c std::string id to set for this unit.
     */
    void addUnit(StandardUnit standardRef, double exponent, const std::string &id = "");

    /**
     * @overload
     *
     * @brief Add a unit to this Units.
     *
     * Add a unit as a child of this Units, this variant specified with only a
     * @c StandardUnit enum units @p reference.
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
     * @overload
     *
     * @brief Get the @c unit attributes for the given @p reference.
     *
     * Get the attributes for the first @c unit that matches the reference @p reference. If
     * no attributes are set, default attribute values will be returned.
     *
     * @param reference The @c std::string reference for the @c unit attributes to get.
     * @param prefix The prefix for this @c unit. Defaults to empty string.
     * @param exponent The exponent for this @c unit. Defaults to 1.0.
     * @param multiplier The multiplier for this @c unit. Defaults to 1.0.
     * @param id The @c std::string id for this @c unit. Defaults to the empty string.
     */
    void unitAttributes(const std::string &reference, std::string &prefix, double &exponent, double &multiplier, std::string &id) const;

    /**
     * @overload
     *
     * @brief Get the @c unit attributes for the given @p standardRef.
     *
     * Get the attributes for the first @c unit that matches the reference @p standardRef. If
     * no attributes are set, default attribute values will be returned.
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
     * @return @c true if the units were replaced, false otherwise.
     */
    bool removeUnit(size_t index);

    /**
     * @overload
     *
     * @brief Remove the unit with the given reference.
     *
     * Remove the first unit found that matches the @c std::string reference @p reference.
     *
     * @param reference The @c std::string unit reference of the unit to remove.
     *
     * @return @c true if the units were replaced, @c false otherwise.
     */
    bool removeUnit(const std::string &reference);

    /**
     * @overload
     *
     * @brief Remove the unit with the given reference.
     *
     * Remove the first unit found that matches @c StandardUnit enum reference @p reference.
     *
     * @param standardRef The @c StandardUnit enum unit reference of the unit to remove.
     *
     * @return @c true if the units were replaced, @c false otherwise.
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
     * from which to extract the named Units.  This Units will be added to the
     * importSource's list of dependent entities.
     *
     * @param importSource The import source from which the named Units originates.
     * @param name The name of the Units in the imported model to use.
     */
    void setSourceUnits(ImportSourcePtr &importSource, const std::string &name);

    /**
     * @brief Get the number of units that compose this units.
     *
     * Returns the number of units contained by this units object.
     *
     * @return The number of units.
     */
    size_t unitCount() const;

    /**
     * @brief Check whether there are any imported child @c Units.
     *
     * Test to determine whether this units has any imported units.
     *
     * @return @c true when this @c Units relies on @c Units which are imported,
     * @c false otherwise.
     */
    bool requiresImports() const;

    /**
     * @brief Return the scaling factor difference between two @c Units.
     *
     * This can be interpreted as `factor`, where units2 = factor*units1.  If compatibility checking is
     * turned on and the units are not compatible the factor returned is 0.0.
     *
     * @param units1 The first units to compare.
     * @param units2 The second units to compare.
     * @param checkCompatibility Set @c true for compatibility checking, or @c false to ignore base units.
     * The default is @c true.
     *
     * @return The factor units2/units1.  Where the units are incompatible and @p checkCompatibility
     * is @c true then the factor returned is 0.0.
     */
    static double scalingFactor(const UnitsPtr &units1, const UnitsPtr &units2, bool checkCompatibility = true);

    /**
     * @brief Test to determine whether two @c Units are compatible or not.
     *
     * Two @c Units are considered to be compatible if they share the same units,
     * independently of their scaling (e.g. volt and volt are compatible as are
     * volt and millivolt).
     *
     * @param1 units1 The first units to compare.
     * @param2 units2 The second units to compare.
     *
     * @return @c true if the two @c Units are compatible, @c false otherwise.
     */
    static bool compatible(const UnitsPtr &units1, const UnitsPtr &units2);

    /**
     * @brief Test to determine whether two @c Units are equivalent or not.
     *
     * Two @c Units are considered to be equivalent if they share the
     * same unit base as well as a scaling factor of 1.0 (e.g. volt and volt are equivalent but
     * volt and millivolt are not).
     *
     * @param1 units1 The first units to compare.
     * @param2 units2 The second units to compare.
     *
     * @return @c true if the two @c Units are equivalent, @c false
     * otherwise.
     */
    static bool equivalent(const UnitsPtr &units1, const UnitsPtr &units2);

    /**
     * @brief Create a clone of this units.
     *
     * Creates a full separate copy of this units without copying
     * the parent. Thus the cloned (returned) version of this units
     * will not have a parent set even if this units does.
     *
     * @return a new @c UnitsPtr to the cloned units.
     */
    UnitsPtr clone() const;

    /**
     * @brief Set the id of the unit at the given @p index.
     *
     *  The operation will return @c true if the id is assigned, or @c false
     *  if the @p index is out of range.
     *
     * @return @c true if successful, @c false otherwise.
     */
    bool setUnitId(size_t index, const std::string &id) const;

    /**
     * @brief Return the id string of the unit at the given @p index.
     *
     * Return the id string of the unit at the given @p index.  If the
     * given index is out of range then the empty string is returned.
     *
     * @return An id string.
     */
    std::string unitId(size_t index);

private:
    Units(); /**< Constructor, @private. */
    explicit Units(const std::string &name); /**< Constructor with std::string parameter, @private. */

    /**
     * @brief Set the import source of this units.
     *
     * Virtual method implementing ImportedEntity::setImportSource, @private.
     * If these units are already located in a Model instance, then the
     * import source is added to the Model too.
     *
     * @param importSource The @c ImportSourcePtr to add to this @ref Units.
     */
    void doSetImportSource(const ImportSourcePtr &importSource) override;

    bool doIsResolved() const override; /**< Virtual method for implementing isResolved, @private. */

    bool doEqual(const EntityPtr &other) const override; /**< Virtual implementation method for equals, @private. */

    struct UnitsImpl; /**< Forward declaration for pImpl idiom, @private. */
    UnitsImpl *mPimpl; /**< Private member to implementation pointer, @private. */
};

} // namespace libcellml
