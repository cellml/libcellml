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

#include "libcellml/units.h"
#include "libcellml/variable.h"

#include <algorithm>
#include <cassert>
#include <map>
#include <sstream>
#include <vector>

namespace libcellml {

/**
 * @brief Map to convert an interface type into its string form.
 *
 * An internal map used to convert a Variable InterfaceType enum class member into its string form.
 */
static const std::map<Variable::InterfaceType, const std::string> interfaceTypeToString = {
    {Variable::InterfaceType::NONE, "none"},
    {Variable::InterfaceType::PRIVATE, "private"},
    {Variable::InterfaceType::PUBLIC, "public"},
    {Variable::InterfaceType::PUBLIC_AND_PRIVATE, "public_and_private"}};

using VariableWeakPtr = std::weak_ptr<Variable>; /**< Type definition for weak variable pointer. */

/**
 * @brief The Variable::VariableImpl struct.
 *
 * The private implementation for the Variable class.
 */
struct Variable::VariableImpl
{
    std::vector<VariableWeakPtr> mEquivalentVariables;
    std::map<VariableWeakPtr, std::string, std::owner_less<VariableWeakPtr>> mMappingIdMap;
    std::map<VariableWeakPtr, std::string, std::owner_less<VariableWeakPtr>> mConnectionIdMap;
    std::string mInitialValue;
    std::string mInterfaceType;
    std::string mUnits;

    void setEquivalentTo(const VariablePtr &equivalentVariable);
    bool unsetEquivalentTo(const VariablePtr &equivalentVariable);

    bool hasEquivalentVariable(const VariablePtr &equivalentVariable) const;

    bool areEquivalentVariables(const Variable *variable1,
                                const Variable *variable2,
                                std::vector<const Variable *> &testedVariables) const;

    void setEquivalentMappingId(const VariablePtr &equivalentVariable, const std::string &id);
    void setEquivalentConnectionId(const VariablePtr &equivalentVariable, const std::string &id);

    std::string getEquivalentMappingId(const VariablePtr &equivalentVariable) const;
    std::string getEquivalentConnectionId(const VariablePtr &equivalentVariable) const;

    std::vector<VariableWeakPtr>::iterator findEquivalentVariable(const VariablePtr &equivalentVariable);
    std::vector<VariableWeakPtr>::const_iterator findEquivalentVariable(const VariablePtr &equivalentVariable) const;
};

std::vector<VariableWeakPtr>::const_iterator Variable::VariableImpl::findEquivalentVariable(const VariablePtr &equivalentVariable) const
{
    return std::find_if(mEquivalentVariables.begin(), mEquivalentVariables.end(),
                        [=](const VariableWeakPtr &variableWeak) -> bool { return equivalentVariable == variableWeak.lock(); });
}

std::vector<VariableWeakPtr>::iterator Variable::VariableImpl::findEquivalentVariable(const VariablePtr &equivalentVariable)
{
    return std::find_if(mEquivalentVariables.begin(), mEquivalentVariables.end(),
                        [=](const VariableWeakPtr &variableWeak) -> bool { return equivalentVariable == variableWeak.lock(); });
}

Variable::Variable()
    : mPimpl(new VariableImpl())
{
}

Variable::~Variable()
{
    delete mPimpl;
}

Variable::Variable(const Variable &rhs)
    : NamedEntity(rhs)
    , mPimpl(new VariableImpl())
{
    mPimpl->mEquivalentVariables = rhs.mPimpl->mEquivalentVariables;
    mPimpl->mConnectionIdMap = rhs.mPimpl->mConnectionIdMap;
    mPimpl->mMappingIdMap = rhs.mPimpl->mMappingIdMap;
    mPimpl->mInitialValue = rhs.mPimpl->mInitialValue;
    mPimpl->mInterfaceType = rhs.mPimpl->mInterfaceType;
    mPimpl->mUnits = rhs.mPimpl->mUnits;
}

Variable::Variable(Variable &&rhs) noexcept
    : NamedEntity(std::move(rhs))
    , mPimpl(rhs.mPimpl)
{
    rhs.mPimpl = nullptr;
}

Variable &Variable::operator=(Variable rhs)
{
    NamedEntity::operator=(rhs);
    rhs.swap(*this);
    return *this;
}

void Variable::swap(Variable &rhs)
{
    std::swap(this->mPimpl, rhs.mPimpl);
}

void Variable::addEquivalence(const VariablePtr &variable1, const VariablePtr &variable2)
{
    variable1->mPimpl->setEquivalentTo(variable2);
    variable2->mPimpl->setEquivalentTo(variable1);
}

void Variable::addEquivalence(const VariablePtr &variable1, const VariablePtr &variable2, const std::string &mappingId, const std::string &connectionId)
{
    Variable::addEquivalence(variable1, variable2);
    variable1->mPimpl->setEquivalentMappingId(variable2, mappingId);
    variable1->mPimpl->setEquivalentConnectionId(variable2, connectionId);
    variable2->mPimpl->setEquivalentMappingId(variable1, mappingId);
    variable2->mPimpl->setEquivalentConnectionId(variable1, connectionId);
}

bool Variable::removeEquivalence(const VariablePtr &variable1, const VariablePtr &variable2)
{
    bool equivalence_1 = variable1->mPimpl->unsetEquivalentTo(variable2);
    bool equivalence_2 = variable2->mPimpl->unsetEquivalentTo(variable1);

    return equivalence_1 && equivalence_2;
}

void Variable::removeAllEquivalences()
{
    mPimpl->mEquivalentVariables.clear();
}

VariablePtr Variable::getEquivalentVariable(size_t index) const
{
    VariablePtr equivalentVariable = nullptr;
    if (index < mPimpl->mEquivalentVariables.size()) {
        VariableWeakPtr weakEquivalentVariable = mPimpl->mEquivalentVariables.at(index);
        equivalentVariable = weakEquivalentVariable.lock();
    }

    return equivalentVariable;
}

size_t Variable::equivalentVariableCount() const
{
    return mPimpl->mEquivalentVariables.size();
}

bool Variable::hasEquivalentVariable(const VariablePtr &equivalentVariable) const
{
    return mPimpl->hasEquivalentVariable(equivalentVariable);
}

bool Variable::isEquivalentVariable(const VariablePtr &equivalentVariable) const
{
    std::vector<const Variable *> testedVariables;

    return mPimpl->areEquivalentVariables(this, equivalentVariable.get(), testedVariables);
}

bool Variable::VariableImpl::hasEquivalentVariable(const VariablePtr &equivalentVariable) const
{
    auto it = findEquivalentVariable(equivalentVariable);
    if (it == mEquivalentVariables.end()) {
        return false;
    }
    return !it->expired();
}

bool Variable::VariableImpl::areEquivalentVariables(const Variable *variable1,
                                                    const Variable *variable2,
                                                    std::vector<const Variable *> &testedVariables) const
{
    if (variable1 == variable2) {
        return true;
    }

    testedVariables.push_back(variable2);

    for (size_t i = 0; i < variable2->equivalentVariableCount(); ++i) {
        Variable *equivalentVariable2 = variable2->getEquivalentVariable(i).get();

        if ((std::find(testedVariables.begin(), testedVariables.end(), equivalentVariable2) == testedVariables.end())
            && areEquivalentVariables(variable1, equivalentVariable2, testedVariables)) {
            return true;
        }
    }

    return false;
}

void Variable::VariableImpl::setEquivalentTo(const VariablePtr &equivalentVariable)
{
    if (!hasEquivalentVariable(equivalentVariable)) {
        VariableWeakPtr weakEquivalentVariable = equivalentVariable;
        mEquivalentVariables.push_back(weakEquivalentVariable);
    }
}

bool Variable::VariableImpl::unsetEquivalentTo(const VariablePtr &equivalentVariable)
{
    bool status = false;
    auto result = findEquivalentVariable(equivalentVariable);
    if (result != mEquivalentVariables.end()) {
        mEquivalentVariables.erase(result);
        auto mappingIdResult = mMappingIdMap.find(equivalentVariable);
        if (mappingIdResult != mMappingIdMap.end()) {
            mMappingIdMap.erase(mappingIdResult);
        }
        auto connectionIdResult = mConnectionIdMap.find(equivalentVariable);
        if (connectionIdResult != mConnectionIdMap.end()) {
            mConnectionIdMap.erase(connectionIdResult);
        }
        status = true;
    }

    return status;
}

void Variable::VariableImpl::setEquivalentMappingId(const VariablePtr &equivalentVariable, const std::string &id)
{
    VariableWeakPtr weakEquivalentVariable = equivalentVariable;
    mMappingIdMap[weakEquivalentVariable] = id;
}

std::string Variable::VariableImpl::getEquivalentMappingId(const VariablePtr &equivalentVariable) const
{
    if (mMappingIdMap.find(equivalentVariable) != mMappingIdMap.end()) {
        return mMappingIdMap.at(equivalentVariable);
    }
    return "";
}

void Variable::VariableImpl::setEquivalentConnectionId(const VariablePtr &equivalentVariable, const std::string &id)
{
    VariableWeakPtr weakEquivalentVariable = equivalentVariable;
    mConnectionIdMap[weakEquivalentVariable] = id;
}

std::string Variable::VariableImpl::getEquivalentConnectionId(const VariablePtr &equivalentVariable) const
{
    if (mConnectionIdMap.find(equivalentVariable) != mConnectionIdMap.end()) {
        return mConnectionIdMap.at(equivalentVariable);
    }
    return "";
}

void Variable::setUnits(const std::string &name)
{
    mPimpl->mUnits = name;
}

void Variable::setUnits(const UnitsPtr &units)
{
    mPimpl->mUnits = units->getName();
}

std::string Variable::getUnits() const
{
    return mPimpl->mUnits;
}

void Variable::setInitialValue(const std::string &initialValue)
{
    mPimpl->mInitialValue = initialValue;
}

void Variable::setInitialValue(double initialValue)
{
    mPimpl->mInitialValue = convertDoubleToString(initialValue);
}

void Variable::setInitialValue(const VariablePtr &variable)
{
    mPimpl->mInitialValue = variable->getName();
}

std::string Variable::getInitialValue() const
{
    return mPimpl->mInitialValue;
}

void Variable::setInterfaceType(const std::string &interfaceType)
{
    mPimpl->mInterfaceType = interfaceType;
}

void Variable::setInterfaceType(Variable::InterfaceType interfaceType)
{
    auto search = interfaceTypeToString.find(interfaceType);
    const std::string interfaceTypeString = search->second;
    setInterfaceType(interfaceTypeString);
}

std::string Variable::getInterfaceType() const
{
    return mPimpl->mInterfaceType;
}

void Variable::setEquivalenceMappingId(const VariablePtr &variable1, const VariablePtr &variable2, const std::string &mappingId)
{
    if (variable1->hasEquivalentVariable(variable2) && variable2->hasEquivalentVariable(variable1)) {
        variable1->mPimpl->setEquivalentMappingId(variable2, mappingId);
        variable2->mPimpl->setEquivalentMappingId(variable1, mappingId);
    }
}

void Variable::setEquivalenceConnectionId(const VariablePtr &variable1, const VariablePtr &variable2, const std::string &connectionId)
{
    if (variable1->hasEquivalentVariable(variable2) && variable2->hasEquivalentVariable(variable1)) {
        variable1->mPimpl->setEquivalentConnectionId(variable2, connectionId);
        variable2->mPimpl->setEquivalentConnectionId(variable1, connectionId);
    }
}

std::string Variable::getEquivalenceMappingId(const VariablePtr &variable1, const VariablePtr &variable2)
{
    std::string id;
    if (variable1->hasEquivalentVariable(variable2) && variable2->hasEquivalentVariable(variable1)) {
        std::string id_1 = variable1->mPimpl->getEquivalentMappingId(variable2);
        std::string id_2 = variable2->mPimpl->getEquivalentMappingId(variable1);
        if (id_1 == id_2) {
            id = id_1;
        }
    }
    return id;
}

std::string Variable::getEquivalenceConnectionId(const VariablePtr &variable1, const VariablePtr &variable2)
{
    std::string id;
    if (variable1->hasEquivalentVariable(variable2) && variable2->hasEquivalentVariable(variable1)) {
        std::string id_1 = variable1->mPimpl->getEquivalentConnectionId(variable2);
        std::string id_2 = variable2->mPimpl->getEquivalentConnectionId(variable1);
        if (id_1 == id_2) {
            id = id_1;
        }
    }
    return id;
}

} // namespace libcellml
