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
#include "libcellml/units.h"

#include <assert.h>
#include <map>
#include <sstream>
#include <vector>

#include "libcellml/import.h"

namespace libcellml {

/**
 * @brief Map PREFIXES to their string forms.
 * An internal map used to convert a PREFIXES into its string form.
 */
std::map<PREFIXES, std::string> prefixToString =
{
    {PREFIX_ATTO, "atto"},
    {PREFIX_CENTI, "centi"},
    {PREFIX_DECA, "deca"},
    {PREFIX_DECI, "deci"},
    {PREFIX_EXA, "exa"},
    {PREFIX_FEMTO, "femto"},
    {PREFIX_GIGA, "giga"},
    {PREFIX_HECTO, "hecto"},
    {PREFIX_KILO, "kilo"},
    {PREFIX_MEGA, "mega"},
    {PREFIX_MICRO, "micro"},
    {PREFIX_MILLI, "milli"},
    {PREFIX_NANO, "nano"},
    {PREFIX_PETA, "peta"},
    {PREFIX_PICO, "pico"},
    {PREFIX_TERA, "tera"},
    {PREFIX_YOCTO, "yocto"},
    {PREFIX_YOTTA, "yotta"},
    {PREFIX_ZEPTO, "zepto"},
    {PREFIX_ZETTA, "zetta"}
};

/**
 * @brief The Unit struct.
 * An internal structure to capture a unit definition.  The
 * prefix can be expressed using either an integer or an enum.
 * The enum structure member is given preference if both are set.
 */
struct Unit
{
    std::string mName; /**< Name for the unit.*/
    std::string mPrefix; /**< String expression of the prefix for the unit.*/
    std::string mExponent; /**< Exponent for the unit.*/
    std::string mMultiplier; /**< Multiplier for the unit.*/
    std::string mOffset; /**< Offset for the unit.*/
};

/**
 * @brief The Units::UnitsImpl struct.
 * The private implementation for the Units class.
 */
struct Units::UnitsImpl
{
    bool mBaseUnit = false; /**< Flag to determine if this Units is a base unit or not.*/
    std::vector<Unit> mUnits; /**< A vector of unit defined for this Units.*/
};

Units::Units()
    : mPimpl(new UnitsImpl())
{
}

Units::~Units()
{
    delete mPimpl;
}

Units::Units(const Units& rhs)
    : ImportedEntity(rhs)
    , mPimpl(new UnitsImpl())
{
    mPimpl->mBaseUnit = rhs.mPimpl->mBaseUnit;
    mPimpl->mUnits = rhs.mPimpl->mUnits;
}

Units::Units(Units &&rhs)
    : ImportedEntity(std::move(rhs))
    , mPimpl(rhs.mPimpl)
{
    rhs.mPimpl = nullptr;
}

Units& Units::operator=(Units e)
{
    ImportedEntity::operator= (e);
    e.swap(*this);
    return *this;
}

void Units::swap(Units &rhs)
{
    std::swap(this->mPimpl, rhs.mPimpl);
}

std::string Units::doSerialisation(FORMATS format) const
{
    std::string repr = "";
    if (format == FORMAT_XML) {
        if (getName().length()) {
            if (isImport()) {
                repr += "<import xlink:href=\"" + getImport()->getSource() + "\" xmlns:xlink=\"http://www.w3.org/1999/xlink\">"
                        "<units units_ref=\"" + getImportReference() + "\" name=\"" + getName() + "\"/>"
                        "</import>";
            } else {
                repr += "<units name=\"" + getName() + "\"";
                if (isBaseUnit()) {
                    repr += " base_unit=\"yes\"";
                    repr += "/>";
                } else {
                    repr += ">";
                    for (std::vector<Unit>::size_type i = 0; i != mPimpl->mUnits.size(); ++i) {
                        repr += "<unit";
                        Unit u = mPimpl->mUnits[i];
                        if (u.mExponent.length()) {
                            repr += " exponent=\"" + u.mExponent + "\"";
                        }
                        if (u.mMultiplier.length()) {
                            repr += " multiplier=\"" + u.mMultiplier + "\"";
                        }
                        if (u.mOffset.length()) {
                            repr += " offset=\"" + u.mOffset + "\"";
                        }
                        if (u.mPrefix.length()) {
                            repr += " prefix=\"" + u.mPrefix + "\"";
                        }
                        repr += " units=\"" + u.mName + "\"";
                        repr += "/>";
                    }
                    repr += "</units>";
                }
            }
        }
    }

    return repr;
}

bool Units::isBaseUnit() const
{
    return mPimpl->mBaseUnit;
}

void Units::setBaseUnit(bool state)
{
    mPimpl->mBaseUnit = state;
}

void Units::addUnit(const std::string &name, const std::string &prefix, double exponent,
             double multiplier, double offset)
{
    Unit u;
    u.mName = name;
    // Allow all nonzero user-specified prefixes
    try
    {
        double prefixDouble = std::stod(prefix);
        if (prefixDouble != 0.0) {
            u.mPrefix = prefix;
        }
    } catch (std::invalid_argument) {
        u.mPrefix = prefix;
    } catch (std::out_of_range) {
        u.mPrefix = prefix;
    }
    if (exponent != 1.0) {
        std::ostringstream strs;
        strs << exponent;
        u.mExponent = strs.str();
    }
    if (multiplier != 1.0) {
        std::ostringstream strs;
        strs << multiplier;
        u.mMultiplier = strs.str();
    }
    if (offset != 0.0) {
        std::ostringstream strs;
        strs << offset;
        u.mOffset = strs.str();
    }
    mPimpl->mUnits.push_back(u);
}

void Units::addUnit(const std::string &name, PREFIXES prefix, double exponent,
             double multiplier, double offset)
{
    auto search = prefixToString.find(prefix);
    assert(search != prefixToString.end());
    const std::string prefixString = search->second;
    addUnit(name, prefixString, exponent, multiplier, offset);
}

void Units::addUnit(const std::string &name, double prefix, double exponent,
             double multiplier, double offset)
{
    std::ostringstream strs;
    strs << prefix;
    const std::string prefixString = strs.str();
    addUnit(name, prefixString, exponent, multiplier, offset);
}

void Units::addUnit(const std::string &name, double exponent)
{
    addUnit(name, "0.0", exponent, 1.0, 0.0);
}

void Units::addUnit(const std::string &name)
{
    addUnit(name, "0.0", 1.0, 1.0, 0.0);
}

void Units::setSourceUnits(const ImportPtr &imp, const std::string &name)
{
    setImport(imp);
    setImportReference(name);
}

}
