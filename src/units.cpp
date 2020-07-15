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

#include "libcellml/units.h"

#include "libcellml/importsource.h"
#include "libcellml/model.h"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <map>
#include <stdexcept>
#include <string>
#include <vector>

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
 * @brief The Unit struct.
 *
 * An internal structure to capture a unit definition.  The
 * prefix can be expressed using either an integer or an enum.
 * The enum structure member is given preference if both are set.
 */
struct Unit
{
    std::string mReference; /**< Reference to the units for the unit.*/
    std::string mPrefix; /**< String expression of the prefix for the unit.*/
    std::string mExponent; /**< Exponent for the unit.*/
    std::string mMultiplier; /**< Multiplier for the unit.*/
    std::string mId; /**< Id for the unit.*/
};

/**
 * @brief The Units::UnitsImpl struct.
 *
 * The private implementation for the Units class.
 */
struct Units::UnitsImpl
{
    std::vector<Unit> mUnits; /**< A vector of unit defined for this Units.*/

    std::vector<Unit>::iterator findUnit(const std::string &reference);

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
};

std::vector<Unit>::iterator Units::UnitsImpl::findUnit(const std::string &reference)
{
    return std::find_if(mUnits.begin(), mUnits.end(),
                        [=](const Unit &u) -> bool { return u.mReference == reference; });
}

bool Units::UnitsImpl::isBaseUnit(const std::string &name) const
{
    return name == "ampere" || name == "candela" || name == "dimensionless" || name == "kelvin" || name == "kilogram" || name == "metre" || name == "mole" || name == "second";
}

/**
 * @brief Finds and updates the multiplier of the unit.
 *
 * We pass in the unit and use its attributes to find the relevant multiplier.
 * If the units are not base units, we travel up the model hierarchy to find
 * the base units.
 *
 * @param units The units to find the multiplier for.
 * @param direction The direction to update multiplier. Either 1 or -1.
 * @param multiplier The multiplier to find.
 *
 * @return Either @c true or @c false, depending if the units were successfully updated.
 */
bool updateUnitMultiplier(const UnitsPtr &units, int direction, double &multiplier)
{
    double localMultiplier = 0;
    bool updated = false;

    if (units->unitCount() == 0) {
        updated = true;
    } else {
        std::string ref;
        std::string pre;
        std::string id;
        double exp;
        double mult;
        double expMult;
        double standardMult = 0.0;
        double prefixMult = 0.0;
        for (size_t i = 0; i < units->unitCount(); ++i) {
            units->unitAttributes(i, ref, pre, exp, expMult, id);
            mult = std::log10(expMult);

            if (isStandardPrefixName(pre)) {
                prefixMult = standardPrefixList.at(pre);
            } else {
                return false;
            }

            if (isStandardUnitName(ref)) {
                standardMult = standardMultiplierList.at(ref);
                // Combine the information into a single local multiplier: exponent only applies to standard multiplier.
                localMultiplier += mult + standardMult * exp + prefixMult;
            } else {
                auto model = owningModel(units);
                if (model != nullptr) {
                    auto refUnits = model->units(ref);
                    double branchMult = 0.0;
                    updated = updateUnitMultiplier(refUnits, 1, branchMult);
                    // Make the direction positive on all branches, direction is only applied at the end.
                    localMultiplier += mult + branchMult * exp + prefixMult;
                } else {
                    return false;
                }
            }
        }
        multiplier += localMultiplier * direction;
        updated = true;
    }
    return updated;
}

Units::Units()
    : mPimpl(new UnitsImpl())
{
}

Units::Units(const std::string &name)
    : mPimpl(new UnitsImpl())
{
    setName(name);
}

Units::~Units()
{
    delete mPimpl;
}

UnitsPtr Units::create() noexcept
{
    return std::shared_ptr<Units> {new Units {}};
}

UnitsPtr Units::create(const std::string &name) noexcept
{
    return std::shared_ptr<Units> {new Units {name}};
}

bool Units::isBaseUnit() const
{
    if (isImport()) {
        ImportSourcePtr importedSource = importSource();
        if (importedSource != nullptr) {
            ModelPtr model = importedSource->model();
            if (model != nullptr && model->hasUnits(importReference())) {
                auto unit = model->units(importReference());
                return unit->isBaseUnit(); // Call isBaseUnit recursively until unit is no longer an import
            }
        }
        return false;
    }

    auto unitsName = name();
    bool standardUnitCheck = true;
    if (isStandardUnitName(unitsName)) {
        standardUnitCheck = mPimpl->isBaseUnit(unitsName);
    }
    return unitCount() == 0 && standardUnitCheck;
}

void Units::addUnit(const std::string &reference, const std::string &prefix, double exponent,
                    double multiplier, const std::string &id)
{
    Unit u;
    u.mReference = reference;
    // Allow all nonzero user-specified prefixes
    try {
        int prefixInteger = std::stoi(prefix);
        if (prefixInteger != 0.0) {
            u.mPrefix = prefix;
        }
    } catch (std::invalid_argument &) {
        u.mPrefix = prefix;
    } catch (std::out_of_range &) {
        u.mPrefix = prefix;
    }
    if (exponent != 1.0) {
        u.mExponent = convertToString(exponent);
    }
    if (multiplier != 1.0) {
        u.mMultiplier = convertToString(multiplier);
    }
    if (!id.empty()) {
        u.mId = id;
    }
    mPimpl->mUnits.push_back(u);
}

void Units::addUnit(const std::string &reference, Prefix prefix, double exponent,
                    double multiplier, const std::string &id)
{
    auto search = prefixToString.find(prefix);
    const std::string prefixString = search->second;
    addUnit(reference, prefixString, exponent, multiplier, id);
}

void Units::addUnit(const std::string &reference, int prefix, double exponent,
                    double multiplier, const std::string &id)
{
    const std::string prefixString = convertToString(prefix);
    addUnit(reference, prefixString, exponent, multiplier, id);
}

void Units::addUnit(const std::string &reference, double exponent, const std::string &id)
{
    addUnit(reference, "0", exponent, 1.0, id);
}

void Units::addUnit(const std::string &reference)
{
    addUnit(reference, "0", 1.0, 1.0, "");
}

void Units::addUnit(StandardUnit standardRef, const std::string &prefix, double exponent,
                    double multiplier, const std::string &id)
{
    const std::string reference = standardUnitToString.find(standardRef)->second;
    addUnit(reference, prefix, exponent, multiplier, id);
}

void Units::addUnit(StandardUnit standardRef, Prefix prefix, double exponent,
                    double multiplier, const std::string &id)
{
    const std::string reference = standardUnitToString.find(standardRef)->second;
    const std::string prefixString = prefixToString.find(prefix)->second;
    addUnit(reference, prefixString, exponent, multiplier, id);
}

void Units::addUnit(StandardUnit standardRef, int prefix, double exponent,
                    double multiplier, const std::string &id)
{
    const std::string reference = standardUnitToString.find(standardRef)->second;
    const std::string prefixString = convertToString(prefix);
    addUnit(reference, prefixString, exponent, multiplier, id);
}

void Units::addUnit(StandardUnit standardRef, double exponent, const std::string &id)
{
    const std::string reference = standardUnitToString.find(standardRef)->second;
    addUnit(reference, "0", exponent, 1.0, id);
}

void Units::addUnit(StandardUnit standardRef)
{
    const std::string reference = standardUnitToString.find(standardRef)->second;
    addUnit(reference, "0", 1.0, 1.0, "");
}

void Units::unitAttributes(StandardUnit standardRef, std::string &prefix, double &exponent, double &multiplier, std::string &id) const
{
    std::string dummyReference;
    const std::string reference = standardUnitToString.find(standardRef)->second;
    auto result = mPimpl->findUnit(reference);
    unitAttributes(size_t(result - mPimpl->mUnits.begin()), dummyReference, prefix, exponent, multiplier, id);
}

void Units::unitAttributes(const std::string &reference, std::string &prefix, double &exponent, double &multiplier, std::string &id) const
{
    std::string dummyReference;
    auto result = mPimpl->findUnit(reference);
    unitAttributes(size_t(result - mPimpl->mUnits.begin()), dummyReference, prefix, exponent, multiplier, id);
}

void Units::unitAttributes(size_t index, std::string &reference, std::string &prefix, double &exponent, double &multiplier, std::string &id) const
{
    Unit u;
    if (index < mPimpl->mUnits.size()) {
        u = mPimpl->mUnits.at(index);
    }
    reference = u.mReference;
    prefix = u.mPrefix;
    if (u.mExponent.empty() || !convertToDouble(u.mExponent, exponent)) {
        exponent = 1.0;
    }
    if (u.mMultiplier.empty() || !convertToDouble(u.mMultiplier, multiplier)) {
        multiplier = 1.0;
    }
    id = u.mId;
}

bool Units::removeUnit(const std::string &reference)
{
    bool status = false;
    auto result = mPimpl->findUnit(reference);
    if (result != mPimpl->mUnits.end()) {
        mPimpl->mUnits.erase(result);
        status = true;
    }

    return status;
}

bool Units::removeUnit(size_t index)
{
    bool status = false;
    if (index < mPimpl->mUnits.size()) {
        mPimpl->mUnits.erase(mPimpl->mUnits.begin() + int64_t(index));
        status = true;
    }

    return status;
}

bool Units::removeUnit(StandardUnit standardRef)
{
    const std::string reference = standardUnitToString.find(standardRef)->second;
    return removeUnit(reference);
}

void Units::removeAllUnits()
{
    mPimpl->mUnits.clear();
}

void Units::setImportSource(ImportSourcePtr &importSource)
{
    auto model = owningModel(shared_from_this());
    auto units = shared_from_this();

    auto oldImportSource = units->importSource();

    if (model != nullptr) {
        model->addImportSource(importSource);
    }
    if (importSource != nullptr) {
        importSource->addUnits(units);
    }
    if (oldImportSource != nullptr) {
        oldImportSource->removeUnits(units, false);
    }
    ImportedEntity::setImportSource(importSource);
}

void Units::setSourceUnits(ImportSourcePtr &importSource, const std::string &name)
{
    setImportSource(importSource);
    setImportReference(name);
}

size_t Units::unitCount() const
{
    return mPimpl->mUnits.size();
}

double Units::scalingFactor(const UnitsPtr &units1, const UnitsPtr &units2, bool checkCompatibility)
{
    if (checkCompatibility && !Units::compatible(units1, units2)) {
        return 0.0;
    }

    bool updateUnits1 = false;
    bool updateUnits2 = false;

    if ((units1 != nullptr) && (units2 != nullptr)) {
        double multiplier = 0.0;

        updateUnits1 = updateUnitMultiplier(units1, -1, multiplier);
        updateUnits2 = updateUnitMultiplier(units2, 1, multiplier);

        if (updateUnits1 && updateUnits2) {
            return std::pow(10, multiplier);
        }

        if (units1->name() == units2->name()) {
            return 1.0;
        }
    }

    return 0.0;
}

using UnitsMap = std::map<std::string, double>;

void updateUnitsMapWithStandardUnit(const std::string &name, UnitsMap &unitsMap, double exp)
{
    auto unitsListIter = standardUnitsList.find(name);
    for (const auto &baseUnitsComponent : unitsListIter->second) {
        auto unitsMapIter = unitsMap.find(baseUnitsComponent.first);
        if (unitsMapIter == unitsMap.end()) {
            unitsMap[baseUnitsComponent.first] = 0.0;
        }
        unitsMap[baseUnitsComponent.first] += baseUnitsComponent.second * exp;
    }
}

bool updateUnitsMap(const UnitsPtr &units, UnitsMap &unitsMap, double exp = 1.0)
{
    if (units->isBaseUnit()) {
        auto unitsName = units->name();
        auto found = unitsMap.find(unitsName);
        if (found == unitsMap.end()) {
            unitsMap.emplace(unitsName, exp);
        } else {
            found->second += exp;
        }
    } else if (isStandardUnit(units)) {
        updateUnitsMapWithStandardUnit(units->name(), unitsMap, exp);
    } else {
        for (size_t i = 0; i < units->unitCount(); ++i) {
            std::string ref;
            std::string pre;
            std::string id;
            double expMult;
            double uExp;
            units->unitAttributes(i, ref, pre, uExp, expMult, id);
            if (isStandardUnitName(ref)) {
                updateUnitsMapWithStandardUnit(ref, unitsMap, uExp * exp);
            } else {
                auto model = owningModel(units);
                if (model == nullptr) {
                    // We cannot resolve the reference for this units so we add
                    // what we do know.
                    unitsMap[ref] = uExp * exp;
                } else {
                    auto refUnits = model->units(ref);
                    if ((refUnits == nullptr) || refUnits->isImport()) {
                        return false;
                    }
                    if (!updateUnitsMap(refUnits, unitsMap, uExp * exp)) {
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

UnitsMap createUnitsMap(const UnitsPtr &units, bool &isValid)
{
    UnitsMap unitsMap;
    isValid = true;
    if (!updateUnitsMap(units, unitsMap)) {
        isValid = false;
        return unitsMap;
    }

    // Checking for exponents of zero in the map, which can be removed.
    auto it = unitsMap.begin();
    while (it != unitsMap.end()) {
        if (it->second == 0.0) {
            it = unitsMap.erase(it);
        } else if (it->first == "dimensionless") {
            it = unitsMap.erase(it);
        } else {
            ++it;
        }
    }
    return unitsMap;
}

bool Units::requiresImports() const
{
    // Function to check child unit dependencies for imports.

    auto model = owningModel(shared_from_this());
    if (model != nullptr) {
        std::string ref;
        std::string prefix;
        double exponent;
        double multiplier;
        std::string id;

        for (size_t u = 0; u < unitCount(); ++u) {
            unitAttributes(u, ref, prefix, exponent, multiplier, id);
            auto child = model->units(ref);
            if (child == nullptr) {
                continue;
            }
            if (child->isImport() || child->requiresImports()) {
                return true;
            }
        }
    }
    return false;
}

bool Units::compatible(const UnitsPtr &units1, const UnitsPtr &units2)
{
    // Initial checks.
    if ((units1 == nullptr) || (units2 == nullptr)) {
        return false;
    }
    if ((units1->isImport()) || (units2->isImport())) {
        return false;
    }
    if ((units1->requiresImports()) || (units2->requiresImports())) {
        return false;
    }
    bool isValid;
    auto units1Map = createUnitsMap(units1, isValid);
    if (!isValid) {
        return false;
    }
    auto units2Map = createUnitsMap(units2, isValid);
    if (!isValid) {
        return false;
    }

    if (units1Map.size() == units2Map.size()) {
        for (const auto &units : units1Map) {
            std::string unit = units.first;
            auto found = units2Map.find(unit);

            if (found == units2Map.end()) {
                return false;
            }
            if (!areEqual(found->second, units.second)) {
                return false;
            }
        }
        return true;
    }
    return false;
}

bool Units::equivalent(const UnitsPtr &units1, const UnitsPtr &units2)
{
    // Units must be compatible and return a scaling factor of 1.0.
    return Units::scalingFactor(units1, units2) == 1.0;
}

UnitsPtr Units::clone() const
{
    auto units = create();

    units->setId(id());
    units->setName(name());

    auto i = importSource();
    units->setImportSource(i);
    units->setImportReference(importReference());

    std::string reference;
    std::string prefix;
    std::string id;
    double exponent;
    double multiplier;
    for (size_t index = 0; index < mPimpl->mUnits.size(); ++index) {
        unitAttributes(index, reference, prefix, exponent, multiplier, id);
        units->addUnit(reference, prefix, exponent, multiplier, id);
    }

    return units;
}

} // namespace libcellml
