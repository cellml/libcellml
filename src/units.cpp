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

#include "utilities.h"

#include "libcellml/importsource.h"
#include "libcellml/model.h"
#include "libcellml/units.h"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <map>
#include <stdexcept>
#include <string>
#include <vector>

namespace libcellml {

/**
 * @brief Map Prefix to their string forms.
 *
 * An internal map used to convert a Prefix into its string form.
 */
static const std::map<Prefix, const std::string> prefixToString = {
    {Prefix::ATTO, "atto"},
    {Prefix::CENTI, "centi"},
    {Prefix::DECA, "deca"},
    {Prefix::DECI, "deci"},
    {Prefix::EXA, "exa"},
    {Prefix::FEMTO, "femto"},
    {Prefix::GIGA, "giga"},
    {Prefix::HECTO, "hecto"},
    {Prefix::KILO, "kilo"},
    {Prefix::MEGA, "mega"},
    {Prefix::MICRO, "micro"},
    {Prefix::MILLI, "milli"},
    {Prefix::NANO, "nano"},
    {Prefix::PETA, "peta"},
    {Prefix::PICO, "pico"},
    {Prefix::TERA, "tera"},
    {Prefix::YOCTO, "yocto"},
    {Prefix::YOTTA, "yotta"},
    {Prefix::ZEPTO, "zepto"},
    {Prefix::ZETTA, "zetta"}};

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
};

std::vector<Unit>::iterator Units::UnitsImpl::findUnit(const std::string &reference)
{
    return std::find_if(mUnits.begin(), mUnits.end(),
                        [=](const Unit &u) -> bool { return u.mReference == reference; });
}

/*

//TDOD: This code is progress towards checking that units are compatible.
using UnitMultiplierMap = std::map<std::string, double>;

    UnitMultiplierMap unitMap = {};
    for (const auto &baseUnits : baseUnitsList) {
        unitMap[baseUnits] = 0.0;
    }
bool updateUnitMultipliers(UnitMultiplierMap &unitMultiplierMap,
                           double &multiplier,
                           const UnitsPtr &units,
                           double uExp, double logMult,
                           int direction)
{
    bool updated = false;
    auto unitsName = units->name();
    if (!units->isBaseUnit()) {
        std::string ref;
        std::string pre;
        std::string id;
        double exp;
        double mult;
        double expMult;
        for (size_t i = 0; i < units->unitCount(); ++i) {
            units->unitAttributes(i, ref, pre, exp, expMult, id);
            mult = std::log10(expMult);
            if (!isStandardUnitName(ref)) {
                auto model = owningModel(units);
                auto refUnits = model->units(ref);
                updated = updateUnitMultipliers(unitMultiplierMap, multiplier, refUnits, exp * uExp, logMult + mult * uExp + standardPrefixList.at(pre) * uExp, direction);
            } else {
                for (const auto &iter : standardUnitsList.at(ref)) {
                    unitMultiplierMap.at(iter.first) += direction * (iter.second * exp * uExp);
                }
                multiplier += direction * (logMult + (standardMultiplierList.at(ref) + mult + standardPrefixList.at(pre)) * exp);
            }
        }
    } else if (unitMultiplierMap.find(unitsName) == unitMultiplierMap.end()) {
        unitMultiplierMap.emplace(std::pair<std::string, double>(unitsName, direction * uExp));
        multiplier += direction * logMult;
        updated = true;
    } else if (isStandardUnitName(unitsName)) {
        for (const auto &iter : standardUnitsList.at(unitsName)) {
            unitMultiplierMap.at(iter.first) += direction * (iter.second * uExp);
        }
        multiplier += direction * logMult;
        multiplier += direction * standardMultiplierList.at(unitsName);
        updated = true;
    }

    return updated;
}
*/

/** 
* @brief Finds and updates the multiplier of the unit.
* 
* We pass in the unit and use its' attributes to find the relevant multiplier.
* If the units are not base units, we travel up the model hierarchy to find 
* the base units.
*
* @param multiplier The multiplier to find.
* @param units The units to find the multiplier for.
* @param uExp The exponential of the units.
* @param logMult The log multiplier of the units.
* @param direction The direction to update multiplier. Either 1 or -1.
*
* @return Either @c true or @c false, depending if the units were successfully updated.
*/
bool updateUnitMultiplier(double &multiplier,
                          const UnitsPtr &units,
                          double uExp, double logMult,
                          int direction)
{
    bool updated = false;
    auto unitsName = units->name();

    if (units->isBaseUnit()) {
        multiplier += direction * logMult;
        updated = true;
    } else {
        std::string ref;
        std::string pre;
        std::string id;
        double exp;
        double mult;
        double expMult;
        for (size_t i = 0; i < units->unitCount(); ++i) {
            units->unitAttributes(i, ref, pre, exp, expMult, id);
            mult = std::log10(expMult);
            if (isStandardUnitName(ref)) {
                multiplier += direction * (logMult + (standardMultiplierList.at(ref) + mult + standardPrefixList.at(pre)) * exp);
                updated = true;
            } else {
                auto model = owningModel(units);
                if (model != nullptr) {
                    auto refUnits = model->units(ref);
                    if ((refUnits == nullptr) || refUnits->isImport()) {
                        return false;
                    }
                    updated = updateUnitMultiplier(multiplier, refUnits, exp * uExp, logMult + mult * uExp + standardPrefixList.at(pre) * uExp, direction);
                }
            }
        }
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
    return unitCount() == 0;
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
    if (!u.mExponent.empty()) {
        exponent = std::stod(u.mExponent);
    } else {
        exponent = 1.0;
    }
    if (!u.mMultiplier.empty()) {
        multiplier = std::stod(u.mMultiplier);
    } else {
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

void Units::setSourceUnits(const ImportSourcePtr &importSource, const std::string &name)
{
    setImportSource(importSource);
    setImportReference(name);
}

size_t Units::unitCount() const
{
    return mPimpl->mUnits.size();
}

double Units::scalingFactor(const UnitsPtr &units1, const UnitsPtr &units2)
{
    bool updateUnits1 = false;
    bool updateUnits2 = false;

    if ((units1 != nullptr) && (units2 != nullptr)) {
        if ((units1->unitCount() != 0) && (units2->unitCount() != 0)) {
            double multiplier = 0.0;

            updateUnits1 = updateUnitMultiplier(multiplier, units2, 1, 0, 1);
            updateUnits2 = updateUnitMultiplier(multiplier, units1, 1, 0, -1);

            if (updateUnits1 && updateUnits2) {
                return std::pow(10, multiplier);
            }
        }

        if (units1->name() == units2->name()) {
            return 1.0;
        }
    }

    return 0.0;
}

void createUnitMap(const UnitsPtr &units, std::map<std::string, double> &map, double exp = 1.0)
{
    //need a check here to deal with imports

    // First we deal with case if unit is baseUnit
    if (units->isBaseUnit()) {
        // Check for imports, otherwise throw units into the map, with associated exponent

        // Find and check if the base unit already exists in the map. If it does, add the relevant exponent to
        // the current exponent amount
        if (map.find(units->name) == map.end()) {
            map.emplace(std::make_pair(units->name, 1.0));
        } else {
            auto unit = map.find(units->name);
            unit->second += exp;
        }
    } else if (isStandardUnitName(units->name)) {
        // We grab our units through map in utilities
        auto unit = standardUnitsList.find(units->name);
        for (auto u : unit->second) {
            if (map.find(u.first) == map.end()) {
                map.emplace(u);
            } else {
                auto e = map.find(u.first);
                e->second += u.second * exp; // adding associated base exponent (times exp???)
            }
        }

    } else {
        // for loop going through and grabbing base units. probably need to use recursion for this one;
        // recursively call createUnitMap
        for (size_t i = 0; i < units->unitCount(); ++i) {
            std::string ref;
            std::string pre;
            std::string id;
            double mult;
            double expMult;
            units->unitAttributes(i, ref, pre, exp, expMult, id);
            if (isStandardUnitName(ref)) {
                auto unit = standardUnitsList.find(units->name);
                for (auto u : unit->second) {
                    if (map.find(u.first) == map.end()) {
                        map.emplace(u);
                    } else {
                        auto e = map.find(u.first);
                        e->second += u.second * exp; // adding associated base exponent (times exp???)
                    }
                }
            } else {
                auto model = owningModel(units);
                if (model != nullptr) {
                    auto refUnits = model->units(ref);
                    if ((refUnits == nullptr) || refUnits->isImport()) {
                        map.clear();
                        break;
                    }
                    createUnitMap(refUnits, map, exp);
                }
            }
        }
    }
}

bool Units::isEquivalentTo(const UnitsPtr &units1, const UnitsPtr &units2)
{
    // initial checks
    if ((units1 == nullptr) || (units2 == nullptr)) {
        return false;
    }
    if ((units1->isImport()) || (units2->isImport())) {
        return false;
    }

    std::map<std::string, double> units1Map;
    createUnitMap(units1, units1Map);
    std::map<std::string, double> units2Map;
    createUnitMap(units2, units2Map); // creating the maps to compare units over

    if ((units1Map.size() == 0) || (units2Map.size() == 0)) {
        return false;
    }

    if (units1Map.size() == units2Map.size()) {
        auto it = units1Map.begin();

        while (it != units1Map.end()) {
            std::string unit = it->first;
            auto found = units2Map.find(unit);

            if (found == units2Map.end()) {
                return false;
            }
            if ((found->second < it->second) || (found->second > it->second)) {
                return false;
            }

            it++;
        }
        return true;
    }
    return false;
}

bool Units::isDimensionallyEquivalentTo(const UnitsPtr &units1, const UnitsPtr &units2)
{
    if (isEquivalentTo(units1, units2) && scalingFactor(units1, units2) == 1.0) {
        return true;
    }
    return false;
}

} // namespace libcellml
