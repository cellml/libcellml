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
#include "libcellml/units.h"

#include <algorithm>
#include <cassert>
#include <stdexcept>
#include <map>
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

Units::Units()
    : mPimpl(new UnitsImpl())
{
}

Units::~Units()
{
    delete mPimpl;
}

Units::Units(const Units &rhs)
    : NamedEntity(rhs)
    , ImportedEntity(rhs)
    , mPimpl(new UnitsImpl())
{
    mPimpl->mUnits = rhs.mPimpl->mUnits;
}

Units::Units(Units &&rhs) noexcept
    : NamedEntity(std::move(rhs))
    , ImportedEntity(std::move(rhs))
    , mPimpl(rhs.mPimpl)
{
    rhs.mPimpl = nullptr;
}

Units &Units::operator=(Units rhs)
{
    NamedEntity::operator=(rhs);
    ImportedEntity::operator=(rhs);
    rhs.swap(*this);
    return *this;
}

void Units::swap(Units &rhs)
{
    std::swap(mPimpl, rhs.mPimpl);
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
        u.mExponent = convertDoubleToString(exponent);
    }
    if (multiplier != 1.0) {
        u.mMultiplier = convertDoubleToString(multiplier);
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
    const std::string prefixString = convertIntToString(prefix);
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
    const std::string prefixString = convertIntToString(prefix);
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

} // namespace libcellml
