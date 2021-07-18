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
#include <cstdint>
#include <cstring>
#include <map>
#include <numeric>
#include <stdexcept>
#include <string>
#include <vector>

#include "units_p.h"
#include "utilities.h"

namespace libcellml {

std::vector<UnitDefinition>::const_iterator Units::UnitsImpl::findUnit(const std::string &reference) const
{
    return std::find_if(mUnitDefinitions.begin(), mUnitDefinitions.end(),
                        [=](const UnitDefinition &u) -> bool { return u.mReference == reference; });
}

Units::UnitsImpl *Units::pFunc()
{
    return reinterpret_cast<Units::UnitsImpl *>(Entity::pFunc());
}

const Units::UnitsImpl *Units::pFunc() const
{
    return reinterpret_cast<Units::UnitsImpl const *>(Entity::pFunc());
}

Units::Units()
    : NamedEntity(new Units::UnitsImpl())
{
    pFunc()->mUnits = this;
}

Units::Units(const std::string &name)
    : NamedEntity(new Units::UnitsImpl())
{
    pFunc()->mUnits = this;
    setName(name);
}

Units::~Units()
{
    delete pFunc();
}

bool Units::UnitsImpl::isBaseUnit(const std::string &name) const
{
    return name == "ampere" || name == "candela" || name == "dimensionless" || name == "kelvin" || name == "kilogram" || name == "metre" || name == "mole" || name == "second";
}

bool Units::UnitsImpl::isBaseUnitWithHistory(History &history, const UnitsConstPtr &units) const
{
    if (mUnits->isImport()) {
        ImportSourcePtr importedSource = mUnits->importSource();
        if (importedSource != nullptr) {
            ModelPtr model = importedSource->model();
            if (model != nullptr) {
                auto h = createHistoryEpoch(units, importeeModelUrl(history, mUnits->importSource()->url()));
                if (checkForImportCycles(history, h)) {
                    return false;
                }
                history.push_back(h);
                if (model->hasUnits(mUnits->importReference())) {
                    auto importedUnits = model->units(mUnits->importReference());
                    // Call isBaseUnit recursively until unit is no longer an import.
                    return importedUnits->pFunc()->isBaseUnitWithHistory(history, importedUnits);
                }
            }
        }
        return false;
    }

    auto unitsName = mUnits->name();
    bool standardUnitCheck = true;
    if (isStandardUnitName(unitsName)) {
        standardUnitCheck = isBaseUnit(unitsName);
    }
    return (mUnits->unitCount() == 0) && standardUnitCheck;
}

bool Units::UnitsImpl::isResolvedWithHistory(History &history, const UnitsConstPtr &units) const
{
    if (!mUnits->isImport()) {
        return true;
    }

    auto model = mUnits->importSource()->model();
    if (model == nullptr) {
        return false;
    }

    auto importedUnits = model->units(mUnits->importReference());
    if (importedUnits == nullptr) {
        return false;
    }

    auto h = createHistoryEpoch(units, importeeModelUrl(history, mUnits->importSource()->url()));
    if (checkForImportCycles(history, h)) {
        return false;
    }

    if (importedUnits->isImport()) {
        history.push_back(h);

        return importedUnits->pFunc()->isResolvedWithHistory(history, importedUnits);
    }

    for (size_t u = 0; (u < importedUnits->unitCount()); ++u) {
        std::string reference;
        std::string prefix;
        std::string id;
        double exponent;
        double multiplier;
        importedUnits->unitAttributes(u, reference, prefix, exponent, multiplier, id);
        if (isStandardUnitName(reference)) {
            continue;
        }

        auto childUnits = model->units(reference);
        if (childUnits == nullptr) {
            return false;
        }

        history.push_back(h);

        if (!childUnits->pFunc()->isResolvedWithHistory(history, childUnits)) {
            return false;
        }
    }

    return true;
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

            bool ok;

            prefixMult = convertPrefixToInt(pre, &ok);
            if (!ok) {
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
                    if (refUnits == nullptr) {
                        return false;
                    }
                    double branchMult = 0.0;
                    // Return false when we can't find a valid prefix.
                    if (!updateUnitMultiplier(refUnits, 1, branchMult)) {
                        return false;
                    }
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
    History history;
    return pFunc()->isBaseUnitWithHistory(history, shared_from_this());
}

bool Units::doEquals(const EntityPtr &other) const
{
    if (!NamedEntity::doEquals(other)) {
        return false;
    }

    auto units = std::dynamic_pointer_cast<Units>(other);

    if ((units == nullptr)
        || (pFunc()->mUnitDefinitions.size() != units->unitCount())
        || !ImportedEntity::doEquals(units)) {
        return false;
    }

    // Check unit definitions match.
    static const auto PTRDIFF_T_MAX = size_t(std::numeric_limits<ptrdiff_t>::max());

    std::string reference;
    std::string prefix;
    double exponent;
    double multiplier;
    std::string id;
    std::vector<size_t> unmatchedUnitIndex(pFunc()->mUnitDefinitions.size());

    std::iota(unmatchedUnitIndex.begin(), unmatchedUnitIndex.end(), 0);

    for (const auto &unitDefinition : pFunc()->mUnitDefinitions) {
        bool unitFound = false;
        size_t index = 0;

        for (index = 0; (index < unmatchedUnitIndex.size()) && !unitFound; ++index) {
            size_t currentIndex = unmatchedUnitIndex.at(index);

            units->unitAttributes(currentIndex, reference, prefix, exponent, multiplier, id);

            if (areNearlyEqual(unitDefinition.mExponent, exponent)
                && (unitDefinition.mId == id)
                && areNearlyEqual(unitDefinition.mMultiplier, multiplier)
                && (unitDefinition.mPrefix == prefix)
                && (unitDefinition.mReference == reference)) {
                unitFound = true;
            }
        }

        if (!unitFound || (index >= PTRDIFF_T_MAX)) {
            return false;
        }

        unmatchedUnitIndex.erase(unmatchedUnitIndex.begin() + ptrdiff_t(index) - 1);
    }

    return true;
}

void Units::addUnit(const std::string &reference, const std::string &prefix, double exponent,
                    double multiplier, const std::string &id)
{
    UnitDefinition ud;
    ud.mReference = reference;

    // Allow all nonzero user-specified prefixes.
    if (isCellMLInteger(prefix)) {
        try {
            int prefixInteger = std::stoi(prefix);
            if (prefixInteger != 0) {
                ud.mPrefix = prefix;
            }
        } catch (std::out_of_range &) {
            ud.mPrefix = prefix;
        }
    } else {
        ud.mPrefix = prefix;
    }

    ud.mExponent = exponent;
    ud.mMultiplier = multiplier;
    ud.mId = id;

    pFunc()->mUnitDefinitions.push_back(ud);
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

void Units::addUnit(StandardUnit standardUnit, const std::string &prefix, double exponent,
                    double multiplier, const std::string &id)
{
    const std::string reference = standardUnitToString.find(standardUnit)->second;
    addUnit(reference, prefix, exponent, multiplier, id);
}

void Units::addUnit(StandardUnit standardUnit, Prefix prefix, double exponent,
                    double multiplier, const std::string &id)
{
    const std::string reference = standardUnitToString.find(standardUnit)->second;
    const std::string prefixString = prefixToString.find(prefix)->second;
    addUnit(reference, prefixString, exponent, multiplier, id);
}

void Units::addUnit(StandardUnit standardUnit, int prefix, double exponent,
                    double multiplier, const std::string &id)
{
    const std::string reference = standardUnitToString.find(standardUnit)->second;
    const std::string prefixString = convertToString(prefix);
    addUnit(reference, prefixString, exponent, multiplier, id);
}

void Units::addUnit(StandardUnit standardUnit, double exponent, const std::string &id)
{
    const std::string reference = standardUnitToString.find(standardUnit)->second;
    addUnit(reference, "0", exponent, 1.0, id);
}

void Units::addUnit(StandardUnit standardUnit)
{
    const std::string reference = standardUnitToString.find(standardUnit)->second;
    addUnit(reference, "0", 1.0, 1.0, "");
}

void Units::unitAttributes(StandardUnit standardUnit, std::string &prefix, double &exponent, double &multiplier, std::string &id) const
{
    std::string dummyReference;
    const std::string reference = standardUnitToString.find(standardUnit)->second;
    auto result = pFunc()->findUnit(reference);
    unitAttributes(size_t(result - pFunc()->mUnitDefinitions.begin()), dummyReference, prefix, exponent, multiplier, id);
}

void Units::unitAttributes(const std::string &reference, std::string &prefix, double &exponent, double &multiplier, std::string &id) const
{
    std::string dummyReference;
    auto result = pFunc()->findUnit(reference);
    unitAttributes(size_t(result - pFunc()->mUnitDefinitions.begin()), dummyReference, prefix, exponent, multiplier, id);
}

void Units::unitAttributes(size_t index, std::string &reference, std::string &prefix, double &exponent, double &multiplier, std::string &id) const
{
    UnitDefinition ud;
    if (index < pFunc()->mUnitDefinitions.size()) {
        ud = pFunc()->mUnitDefinitions.at(index);
    }
    reference = ud.mReference;
    prefix = ud.mPrefix;
    exponent = ud.mExponent;
    multiplier = ud.mMultiplier;
    id = ud.mId;
}

std::string Units::unitAttributeReference(size_t index) const
{
    std::string ref;
    std::string pre;
    double exp;
    double mult;
    std::string id;
    unitAttributes(index, ref, pre, exp, mult, id);
    return ref;
}

std::string Units::unitAttributePrefix(size_t index) const
{
    std::string ref;
    std::string pre;
    double exp;
    double mult;
    std::string id;
    unitAttributes(index, ref, pre, exp, mult, id);
    return pre;
}

double Units::unitAttributeExponent(size_t index) const
{
    std::string ref;
    std::string pre;
    double exp;
    double mult;
    std::string id;
    unitAttributes(index, ref, pre, exp, mult, id);
    return exp;
}

double Units::unitAttributeMultiplier(size_t index) const
{
    std::string ref;
    std::string pre;
    double exp;
    double mult;
    std::string id;
    unitAttributes(index, ref, pre, exp, mult, id);
    return mult;
}

bool Units::setUnitId(size_t index, const std::string &id)
{
    if (index < pFunc()->mUnitDefinitions.size()) {
        pFunc()->mUnitDefinitions[index].mId = id;
        return true;
    }
    return false;
}

std::string Units::unitId(size_t index) const
{
    if (index < pFunc()->mUnitDefinitions.size()) {
        return pFunc()->mUnitDefinitions.at(index).mId;
    }
    return "";
}

bool Units::removeUnit(const std::string &reference)
{
    bool status = false;
    auto result = pFunc()->findUnit(reference);
    if (result != pFunc()->mUnitDefinitions.end()) {
        pFunc()->mUnitDefinitions.erase(result);
        status = true;
    }

    return status;
}

bool Units::removeUnit(size_t index)
{
    bool status = false;
    if (index < pFunc()->mUnitDefinitions.size()) {
        pFunc()->mUnitDefinitions.erase(pFunc()->mUnitDefinitions.begin() + ptrdiff_t(index));
        status = true;
    }

    return status;
}

bool Units::removeUnit(StandardUnit standardUnit)
{
    const std::string reference = standardUnitToString.find(standardUnit)->second;
    return removeUnit(reference);
}

void Units::removeAllUnits()
{
    pFunc()->mUnitDefinitions.clear();
}

void Units::setSourceUnits(ImportSourcePtr &importSource, const std::string &name)
{
    setImportSource(importSource);
    setImportReference(name);
}

size_t Units::unitCount() const
{
    return pFunc()->mUnitDefinitions.size();
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
            unitsMap.emplace(baseUnitsComponent.first, 0.0);
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
                    unitsMap.emplace(ref, uExp * exp);
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
    if (isImport()) {
        return true;
    }

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
            if (child->requiresImports()) {
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

    if (isImport()) {
        units->setImportSource(importSource());
    }

    units->setImportReference(importReference());

    std::string reference;
    std::string prefix;
    std::string id;
    double exponent;
    double multiplier;
    for (size_t index = 0; index < pFunc()->mUnitDefinitions.size(); ++index) {
        unitAttributes(index, reference, prefix, exponent, multiplier, id);
        units->addUnit(reference, prefix, exponent, multiplier, id);
    }

    return units;
}

bool Units::doIsResolved() const
{
    History history;
    return pFunc()->isResolvedWithHistory(history, shared_from_this());
}

} // namespace libcellml
