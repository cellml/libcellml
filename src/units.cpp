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
#include "libcellml/units.h"

#include <vector>
#include <sstream>

#include "libcellml/import.h"

namespace libcellml {

/**
 * @brief Convert a PREFIXES into its string form.
 * Private function to convert a PREFIXES into its string form.
 *
 * @param prefix The prefix to convert.
 * @return A std::string form of the given prefix.
 */
std::string prefixToString(PREFIXES prefix);

/**
 * @brief The Unit struct.
 * An internal structure to capture a unit definition.  The
 * prefix can be expressed using either an integer or an enum.
 * The enum structure member is given preference if both are set.
 */
struct Unit
{
    std::string mUnits = ""; /**< Name for the unit.*/
    int mPrefixInt = 0; /**< Integer expression of the prefix for the unit.*/
    PREFIXES mPrefixEnum = PREFIX_UNIT; /**< Enum expression of the prefix for the unit.*/
    double mExponent = 1.0; /**< Exponent for the unit.*/
    double mMultiplier = 1.0; /**< Multiplier for the unit.*/
    double mOffset = 0.0; /**< Offset for the unit.*/
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

std::string Units::doSerialisation(libcellml::FORMATS format) const
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
                        if (u.mExponent != 1.0) {
                            std::ostringstream strs;
                            strs << u.mExponent;
                            repr += " exponent=\"" + strs.str() + "\"";
                        }
                        if (u.mMultiplier != 1.0) {
                            std::ostringstream strs;
                            strs << u.mMultiplier;
                            repr += " multiplier=\"" + strs.str() + "\"";
                        }
                        if (u.mOffset != 0.0) {
                            std::ostringstream strs;
                            strs << u.mOffset;
                            repr += " offset=\"" + strs.str() + "\"";
                        }
                        if (u.mPrefixEnum != PREFIX_UNIT) {
                            repr += " prefix=\"" + prefixToString(u.mPrefixEnum) + "\"";
                        } else if (u.mPrefixInt != 0) {
                            std::ostringstream strs;
                            strs << u.mPrefixInt;
                            repr += " prefix=\"" + strs.str() + "\"";
                        }
                        repr += " units=\"" + u.mUnits + "\"";
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

void Units::addUnit(const std::string & units, PREFIXES prefix, double exponent,
             double multiplier, double offset)
{
    Unit u;
    u.mUnits = units;
    u.mPrefixEnum = prefix;
    u.mExponent = exponent;
    u.mMultiplier = multiplier;
    u.mOffset = offset;

    mPimpl->mUnits.push_back(u);
}

void Units::addUnit(const std::string & units, int prefix, double exponent,
             double multiplier, double offset)
{
    Unit u;
    u.mUnits = units;
    u.mPrefixInt = prefix;
    u.mExponent = exponent;
    u.mMultiplier = multiplier;
    u.mOffset = offset;

    mPimpl->mUnits.push_back(u);
}

void Units::addUnit(const std::string &units, double exponent)
{
    addUnit(units, PREFIX_UNIT, exponent, 1.0, 0.0);
}

void Units::addUnit(const std::string &units)
{
    addUnit(units, PREFIX_UNIT, 1.0, 1.0, 0.0);

}

void Units::setSourceUnits(const ImportPtr &imp, const std::string &name)
{
    setImport(imp);
    setImportReference(name);
}

std::string prefixToString(PREFIXES prefix)
{
    std::string str;
    switch (prefix) {
    case PREFIX_ATTO: {
        str = "atto";
        break;
    }
    case PREFIX_CENTI: {
        str = "centi";
        break;
    }
    case PREFIX_DECA: {
        str = "deca";
        break;
    }
    case PREFIX_DECI: {
        str = "deci";
        break;
    }
    case PREFIX_EXA: {
        str = "exa";
        break;
    }
    case PREFIX_FEMTO: {
        str = "femto";
        break;
    }
    case PREFIX_GIGA: {
        str = "giga";
        break;
    }
    case PREFIX_HECTO: {
        str = "hecto";
        break;
    }
    case PREFIX_KILO: {
        str = "kilo";
        break;
    }
    case PREFIX_MEGA: {
        str = "mega";
        break;
    }
    case PREFIX_MICRO: {
        str = "micro";
        break;
    }
    case PREFIX_MILLI: {
        str = "milli";
        break;
    }
    case PREFIX_NANO: {
        str = "nano";
        break;
    }
    case PREFIX_PETA: {
        str = "peta";
        break;
    }
    case PREFIX_PICO: {
        str = "pico";
        break;
    }
    case PREFIX_TERA: {
        str = "tera";
        break;
    }
    case PREFIX_UNIT: /* Should not ask for the string version of this.
With the current codebase there is no way to trigger this case. */
    case PREFIX_YOCTO: {
        str = "yocto";
        break;
    }
    case PREFIX_YOTTA: {
        str = "yotta";
        break;
    }
    case PREFIX_ZEPTO: {
        str = "zepto";
        break;
    }
    case PREFIX_ZETTA: {
        str = "zetta";
        break;
    }
    }

    return str;
}

}
