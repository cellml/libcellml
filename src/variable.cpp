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
#include "libcellml/variable.h"

#include <sstream>
#include <vector>
#include <algorithm>

#include "libcellml/units.h"


namespace libcellml {

/**
 * @brief Convert a INTERFACE_TYPES into its string form.
 * Private function to convert a Variable INTERFACE_TYPES into its string form.
 *
 * @param interfaceType The interface type to convert.
 * @return A @c std::string form of the given interface type.
 */
EXPORT_FOR_TESTING std::string interfaceTypeToString(Variable::INTERFACE_TYPES interfaceType);

/**
 * @brief The Variable::VariableImpl struct.
 * The private implementation for the Variable class.
 */
struct Variable::VariableImpl
{
    std::vector<VariablePtr>::iterator findEquivalentVariable(const VariablePtr &equivalentVariable);
    std::vector<VariablePtr> mEquivalentVariables; /**< Equivalent variables for this Variable.*/    
    std::string mInitialValue = ""; /**< Initial value for this Variable.*/
    INTERFACE_TYPES mInterfaceType = INTERFACE_TYPE_NONE; /**< Interface type for this Variable. Default to none.*/
    UnitsPtr mUnits; /**< A pointer to the Units defined for this Variable.*/
};

std::vector<VariablePtr>::iterator Variable::VariableImpl::findEquivalentVariable(const VariablePtr &equivalentVariable)
{
    return std::find_if(mEquivalentVariables.begin(), mEquivalentVariables.end(),
                        [=](const VariablePtr& variable) -> bool {return variable == equivalentVariable;});
}

Variable::Variable()
    : mPimpl(new VariableImpl())
{
}

Variable::~Variable()
{
    delete mPimpl;
}

Variable::Variable(const Variable& rhs)
    : NamedEntity(rhs)
    , mPimpl(new VariableImpl())
{
}

Variable::Variable(Variable &&rhs)
    : NamedEntity(std::move(rhs))
    , mPimpl(rhs.mPimpl)
{
    rhs.mPimpl = nullptr;
}

Variable& Variable::operator=(Variable e)
{
    NamedEntity::operator= (e);
    e.swap(*this);
    return *this;
}

void Variable::swap(Variable &rhs)
{
    std::swap(this->mPimpl, rhs.mPimpl);
}

void Variable::addEquivalence(const VariablePtr &equivalentVariable)
{
    setEquivalentTo(equivalentVariable);
    VariablePtr *pV = new VariablePtr(this);
    equivalentVariable->setEquivalentTo(*pV);
}

VariablePtr Variable::getEquivalentVariable(size_t index)
{
    return mPimpl->mEquivalentVariables.at(index);
}

size_t Variable::equivalentVariableCount() const
{
    return mPimpl->mEquivalentVariables.size();
}

bool Variable::hasEquivalentVariable(const VariablePtr &equivalentVariable)
{
    auto result = mPimpl->findEquivalentVariable(equivalentVariable);
    return result != mPimpl->mEquivalentVariables.end();
}

void Variable::setEquivalentTo(const VariablePtr &equivalentVariable)
{
    if (!hasEquivalentVariable(equivalentVariable)) {
        mPimpl->mEquivalentVariables.push_back(equivalentVariable);
    }
}

std::string Variable::doSerialisation(FORMATS format) const
{
    std::string repr = "";
    if (format == FORMAT_XML) {
        repr += "<variable";
        if (getName().length()) {
            repr += " name=\"" + getName() + "\"";
        }
        if (getUnits() != nullptr) {
            repr += " units=\"" + getUnits()->getName() + "\"";
        }
        if (getInitialValue().length()) {
            repr += " initial_value=\"" + getInitialValue() + "\"";
        }
        if (getInterfaceType() != INTERFACE_TYPE_NONE) {
            repr += " interface=\"" + interfaceTypeToString(getInterfaceType()) + "\"";
        }
        repr += "/>";
    }
    return repr;
}

void Variable::setUnits(const UnitsPtr &u)
{
    mPimpl->mUnits = u;
}

UnitsPtr Variable::getUnits() const
{
    return mPimpl->mUnits;
}

void Variable::setInitialValue(const std::string &initialValue)
{
    mPimpl->mInitialValue = initialValue;
}

void Variable::setInitialValue(double initialValue)
{
    std::ostringstream strs;
    strs << initialValue;
    mPimpl->mInitialValue = strs.str();
}

void Variable::setInitialValue(const VariablePtr &v)
{
    mPimpl->mInitialValue = v->getName();
}

std::string Variable::getInitialValue() const
{
    return mPimpl->mInitialValue;
}

void Variable::setInterfaceType(Variable::INTERFACE_TYPES interfaceType)
{
    mPimpl->mInterfaceType = interfaceType;
}

Variable::INTERFACE_TYPES Variable::getInterfaceType() const
{
    return mPimpl->mInterfaceType;
}

EXPORT_FOR_TESTING std::string interfaceTypeToString(Variable::INTERFACE_TYPES interfaceType)
{
    std::string str = "";
    switch (interfaceType) {
    case Variable::INTERFACE_TYPE_NONE: {
        /* Should not ask for the string version of this.
        With the current codebase there is no way to trigger this case. */
        str = "none";
        break;
    }
    case Variable::INTERFACE_TYPE_PRIVATE: {
        str = "private";
        break;
    }
    case Variable::INTERFACE_TYPE_PUBLIC: {
        str = "public";
        break;
    }
    case Variable::INTERFACE_TYPE_PUBLIC_AND_PRIVATE: {
        str = "public_and_private";
        break;
    }
    }
    return str;
}

}
