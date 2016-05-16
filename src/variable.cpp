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
#include "libcellml/variable.h"

#include <algorithm>
#include <assert.h>
#include <map>
#include <sstream>
#include <vector>

#include "libcellml/units.h"


namespace libcellml {

/**
 * @brief Map to convert an INTERFACE_TYPES into its string form.
 * An internal map used to convert a Variable INTERFACE_TYPES into its string form.
 */
std::map<Variable::INTERFACE_TYPES, std::string> interfaceTypeToString =
{
    {Variable::INTERFACE_TYPE_NONE, "none"},
    {Variable::INTERFACE_TYPE_PRIVATE, "private"},
    {Variable::INTERFACE_TYPE_PUBLIC, "public"},
    {Variable::INTERFACE_TYPE_PUBLIC_AND_PRIVATE, "public_and_private"}
};

typedef std::weak_ptr<Variable> VariableWeakPtr; /**< Type definition for weak variable pointer. */

/**
 * @brief The Variable::VariableImpl struct.
 * The private implementation for the Variable class.
 */
struct Variable::VariableImpl
{
    std::vector<VariableWeakPtr>::iterator findEquivalentVariable(const VariablePtr &equivalentVariable);
    std::vector<VariableWeakPtr> mEquivalentVariables; /**< Equivalent variables for this Variable.*/
    std::string mInitialValue; /**< Initial value for this Variable.*/
    std::string mInterfaceType; /**< Interface type for this Variable.*/
    UnitsPtr mUnits; /**< A pointer to the Units defined for this Variable.*/
};

std::vector<VariableWeakPtr>::iterator Variable::VariableImpl::findEquivalentVariable(const VariablePtr &equivalentVariable)
{
    return std::find_if(mEquivalentVariables.begin(), mEquivalentVariables.end(),
                        [=](VariableWeakPtr variableWeak) -> bool { return equivalentVariable == variableWeak.lock(); });
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
    mPimpl->mEquivalentVariables = rhs.mPimpl->mEquivalentVariables;
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

void Variable::addEquivalence(const VariablePtr &variable1, const VariablePtr &variable2)
{
    variable1->setEquivalentTo(variable2);
    variable2->setEquivalentTo(variable1);
}

VariablePtr Variable::getEquivalentVariable(size_t index)
{
    VariableWeakPtr weakEquivalentVariable = mPimpl->mEquivalentVariables.at(index);
    return weakEquivalentVariable.lock();
}

size_t Variable::equivalentVariableCount() const
{
    return mPimpl->mEquivalentVariables.size();
}

bool Variable::hasEquivalentVariable(const VariablePtr &equivalentVariable)
{
    return mPimpl->findEquivalentVariable(equivalentVariable) != mPimpl->mEquivalentVariables.end();
}

void Variable::setEquivalentTo(const VariablePtr &equivalentVariable)
{
    if (!hasEquivalentVariable(equivalentVariable)) {
        VariableWeakPtr weakEquivalentVariable = equivalentVariable;
        mPimpl->mEquivalentVariables.push_back(weakEquivalentVariable);
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
        if (getUnits()) {
            repr += " units=\"" + getUnits()->getName() + "\"";
        }
        if (getInitialValue().length()) {
            repr += " initial_value=\"" + getInitialValue() + "\"";
        }
        if (getInterfaceType().length()) {
            repr += " interface=\"" + getInterfaceType() + "\"";
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

void Variable::setInterfaceType(const std::string &interfaceType)
{
    mPimpl->mInterfaceType = interfaceType;
}

void Variable::setInterfaceType(Variable::INTERFACE_TYPES interfaceType)
{
    auto search = interfaceTypeToString.find(interfaceType);
    assert(search != interfaceTypeToString.end());
    const std::string interfaceTypeString = search->second;
    setInterfaceType(interfaceTypeString);
}

std::string Variable::getInterfaceType() const
{
    return mPimpl->mInterfaceType;
}

}
