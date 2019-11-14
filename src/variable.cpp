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
    Variable *mVariable = nullptr;
    std::vector<VariableWeakPtr> mEquivalentVariables; /**< Equivalent variables for this Variable.*/
    std::map<VariableWeakPtr, std::string, std::owner_less<VariableWeakPtr>> mMappingIdMap; /**< Mapping id map for equivalent variable.*/
    std::map<VariableWeakPtr, std::string, std::owner_less<VariableWeakPtr>> mConnectionIdMap; /**< Connection id map for equivalent variable.*/
    std::string mInitialValue; /**< Initial value for this Variable.*/
    std::string mInterfaceType; /**< Interface type for this Variable.*/
    UnitsPtr mUnits = nullptr; /**< The units defined for this Variable.*/

    /**
     * @brief Private function to add an equivalent variable to the set for this variable.
     *
     * Add the argument equivalent variable to the set of equivalent variables for this
     * variable if it is not already present. If the equivalent variable is present,
     * do nothing.
     *
     * @sa addEquivalence, unsetEquivalentTo
     *
     * @param equivalentVariable The variable to add to this variable's equivalent
     * variable set if not already present.
     */
    void setEquivalentTo(const VariablePtr &equivalentVariable);

    /**
     * @brief Private function to remove an equivalent variable from the set for this variable.
     *
     * Remove the @p equivalentVariable from the set of equivalent variables for this
     * variable if it is present.
     *
     * @sa removeEquivalence, setEquivalentTo
     *
     * @param equivalentVariable The variable to remove from this variable's equivalent
     * variable set if it is present.
     *
     * @return True if the @p equivalentVariable is removed from set of equivalent variables, false otherwise.
     */
    bool unsetEquivalentTo(const VariablePtr &equivalentVariable);

    /**
     * @brief Test if the given variable is directly equivalent to this one.
     *
     * The two variables are considered directly equivalent if this variable holds a valid reference to the
     * given variable.  Returns @c true if this variable holds a reference to the given variable
     * and that that reference is a valid reference to the given variable.
     *
     * @param equivalentVariable The variable to test for equivalence to this one.
     * @return @c true if the variables are equivalent @c false otherwise.
     */
    bool hasDirectEquivalentVariable(const VariablePtr &equivalentVariable) const;

    bool haveEquivalentVariables(const Variable *variable1, const Variable *variable2,
                                 std::vector<const Variable *> &testedVariables) const;
    bool hasEquivalentVariable(const VariablePtr &equivalentVariable) const;

    /**
     * @brief Set the equivalent mapping id for this equivalence.
     *
     * Record the given id as the mapping id for the equivalence defined with this variable
     * and the given one.  This id appears in the 'map_variables' element of the model when
     * serialised.
     *
     * To clear an equivalence mapping id set it to the empty string. If the two variables are
     * not equivalent the mapping id is not set.
     *
     * @param equivalentVariable The equivalent variable the id refers to.
     * @param id @c std::string id to set.
     */
    void setEquivalentMappingId(const VariablePtr &equivalentVariable, const std::string &id);

    /**
     * @brief Set the equivalent connection id for this equivalence.
     *
     * Record the given id as the connection id for the equivalence defined with this variable
     * and the given one.  This id appears in the 'connection' element of the model when serialised.
     *
     * Where the same component pair has multiple equivalent variables only the last connection id
     * found in the set will be serialised.
     *
     * To clear an equivalence connection id set it to the empty string.  If the two variables are not
     * equivalent the connection id is not set.
     *
     * @param equivalentVariable The equivalent variable the id refers to.
     * @param id @c std::string id to set.
     */
    void setEquivalentConnectionId(const VariablePtr &equivalentVariable, const std::string &id);

    /**
     * @brief Get the equivalent mapping id for this equivalence.
     *
     * Get the mapping id set for the equivalence defined by the this variable and the given one.
     * If no mapping id is set the empty string is returned.
     *
     * If the two variables are not equivalent the empty string is returned.
     *
     * @param equivalentVariable The variable this variable is equivalent to.
     * @return The @c std::string id of the equivalence if found otherwise returns the empty string.
     */
    std::string equivalentMappingId(const VariablePtr &equivalentVariable) const;

    /**
     * @brief Get the equivalent connection id for this equivalence.
     *
     * Get the connection id set for the equivalence defined by the this variable and the given one.
     * If no connection id is set the empty string is returned.
     *
     * If the two variables are not equivalent the empty string is returned.
     *
     * @param equivalentVariable The variable this variable is equivalent to.
     * @return The @c std::string id of the equivalence if found otherwise returns the empty string.
     */
    std::string equivalentConnectionId(const VariablePtr &equivalentVariable) const;

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
    mPimpl->mVariable = this;
}

Variable::Variable(const std::string &name)
    : mPimpl(new VariableImpl())
{
    mPimpl->mVariable = this;
    setName(name);
}

Variable::~Variable()
{
    delete mPimpl;
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
    auto thisVariable = shared_from_this();
    for (const auto &variable : mPimpl->mEquivalentVariables) {
        if (!variable.expired()) {
            removeEquivalence(thisVariable, variable.lock());
        }
    }
    mPimpl->mEquivalentVariables.clear();
}

VariablePtr Variable::equivalentVariable(size_t index) const
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

bool Variable::hasDirectEquivalentVariable(const VariablePtr &equivalentVariable) const
{
    return mPimpl->hasDirectEquivalentVariable(equivalentVariable);
}

bool Variable::VariableImpl::hasDirectEquivalentVariable(const VariablePtr &equivalentVariable) const
{
    auto it = findEquivalentVariable(equivalentVariable);
    if (it == mEquivalentVariables.end()) {
        return false;
    }
    return !it->expired();
}

bool Variable::hasEquivalentVariable(const VariablePtr &equivalentVariable) const
{
    return mPimpl->hasEquivalentVariable(equivalentVariable);
}

bool Variable::VariableImpl::hasEquivalentVariable(const VariablePtr &equivalentVariable) const
{
    if (mVariable == equivalentVariable.get()) {
        return false;
    }

    std::vector<const Variable *> testedVariables;

    return haveEquivalentVariables(mVariable, equivalentVariable.get(), testedVariables);
}

bool Variable::VariableImpl::haveEquivalentVariables(const Variable *variable1,
                                                     const Variable *variable2,
                                                     std::vector<const Variable *> &testedVariables) const
{
    if (variable1 == variable2) {
        return true;
    }

    if (variable2 == nullptr) {
        return false;
    }

    testedVariables.push_back(variable2);

    for (size_t i = 0; i < variable2->equivalentVariableCount(); ++i) {
        Variable *equivalentVariable2 = variable2->equivalentVariable(i).get();

        if ((std::find(testedVariables.begin(), testedVariables.end(), equivalentVariable2) == testedVariables.end())
            && haveEquivalentVariables(variable1, equivalentVariable2, testedVariables)) {
            return true;
        }
    }

    return false;
}

void Variable::VariableImpl::setEquivalentTo(const VariablePtr &equivalentVariable)
{
    if (!hasDirectEquivalentVariable(equivalentVariable)) {
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

std::string Variable::VariableImpl::equivalentMappingId(const VariablePtr &equivalentVariable) const
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

std::string Variable::VariableImpl::equivalentConnectionId(const VariablePtr &equivalentVariable) const
{
    if (mConnectionIdMap.find(equivalentVariable) != mConnectionIdMap.end()) {
        return mConnectionIdMap.at(equivalentVariable);
    }
    return "";
}

void Variable::setUnits(const std::string &name)
{
    libcellml::UnitsPtr u = libcellml::Units::create();
    u->setName(name);
    mPimpl->mUnits = u;
}

void Variable::setUnits(const UnitsPtr &units)
{
    mPimpl->mUnits = units;
}

void Variable::removeUnits()
{
    mPimpl->mUnits = nullptr;
}

UnitsPtr Variable::units() const
{
    return mPimpl->mUnits;
}

void Variable::setInitialValue(const std::string &initialValue)
{
    mPimpl->mInitialValue = initialValue;
}

void Variable::setInitialValue(double initialValue)
{
    mPimpl->mInitialValue = convertToString(initialValue);
}

void Variable::setInitialValue(const VariablePtr &variable)
{
    mPimpl->mInitialValue = variable->name();
}

std::string Variable::initialValue() const
{
    return mPimpl->mInitialValue;
}

void Variable::removeInitialValue()
{
    mPimpl->mInitialValue.clear();
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

std::string Variable::interfaceType() const
{
    return mPimpl->mInterfaceType;
}

void Variable::removeInterfaceType()
{
    mPimpl->mInterfaceType.clear();
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

std::string Variable::equivalenceMappingId(const VariablePtr &variable1, const VariablePtr &variable2)
{
    std::string id;
    if (variable1->hasEquivalentVariable(variable2) && variable2->hasEquivalentVariable(variable1)) {
        std::string id_1 = variable1->mPimpl->equivalentMappingId(variable2);
        std::string id_2 = variable2->mPimpl->equivalentMappingId(variable1);
        if (id_1 == id_2) {
            id = id_1;
        }
    }
    return id;
}

std::string Variable::equivalenceConnectionId(const VariablePtr &variable1, const VariablePtr &variable2)
{
    std::string id;
    if (variable1->hasEquivalentVariable(variable2) && variable2->hasEquivalentVariable(variable1)) {
        std::string id_1 = variable1->mPimpl->equivalentConnectionId(variable2);
        std::string id_2 = variable2->mPimpl->equivalentConnectionId(variable1);
        if (id_1 == id_2) {
            id = id_1;
        }
    }
    return id;
}

void Variable::removeEquivalenceConnectionId(const VariablePtr &variable1, const VariablePtr &variable2)
{
    if (variable1->hasEquivalentVariable(variable2) && variable2->hasEquivalentVariable(variable1)) {
        variable1->mPimpl->setEquivalentConnectionId(variable2, "");
        variable2->mPimpl->setEquivalentConnectionId(variable1, "");
    }
}

void Variable::removeEquivalenceMappingId(const VariablePtr &variable1, const VariablePtr &variable2)
{
    if (variable1->hasEquivalentVariable(variable2) && variable2->hasEquivalentVariable(variable1)) {
        variable1->mPimpl->setEquivalentMappingId(variable2, "");
        variable2->mPimpl->setEquivalentMappingId(variable1, "");
    }
}

} // namespace libcellml
