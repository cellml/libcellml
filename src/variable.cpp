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

#include "libcellml/variable.h"

#include <algorithm>
#include <cassert>
#include <map>
#include <sstream>
#include <vector>

#include "libcellml/model.h"
#include "libcellml/units.h"

#include "utilities.h"

namespace libcellml {

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
    UnitsPtr mUnits = nullptr; /**< The Units defined for this Variable.*/

    /**
     * @brief Clean expired equivalent variables.
     *
     * Clean away any equivalent variables that have become expired.
     */
    void cleanExpiredVariables();

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
     *
     * @return True if the given variable is added to this variables equivalent variable set.
     */
    bool setEquivalentTo(const VariablePtr &equivalentVariable);

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
    bool hasEquivalentVariable(const VariablePtr &equivalentVariable, bool considerIndirectEquivalences = false) const;

    /**
     * @brief Test whether the argument variable is equivalent to this variable.
     *
     * Tests to see if the argument variable is equivalent to this variable. Returns @c true if
     * the argument variable is equivalent to this variable and @c false otherwise. The test will
     * traverse through the equivalent network to determine if the argument variable is
     * equivalent to this variable.
     *
     * @param equivalentVariable The variable to check for equivalence.
     *
     * @return @c true if the @p equivalentVariable is equivalent to this variable and
     * @c false otherwise.
     */
    bool hasIndirectEquivalentVariable(const VariablePtr &equivalentVariable) const;

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

VariablePtr Variable::create() noexcept
{
    return std::shared_ptr<Variable> {new Variable {}};
}

VariablePtr Variable::create(const std::string &name) noexcept
{
    return std::shared_ptr<Variable> {new Variable {name}};
}

bool Variable::doEqual(const EntityPtr &other) const
{
    if (NamedEntity::doEqual(other)) {
        auto variable = std::dynamic_pointer_cast<libcellml::Variable>(other);
        if (variable != nullptr && mPimpl->mInitialValue == variable->initialValue() && mPimpl->mInterfaceType == variable->interfaceType()) {
            bool equal = true;
            if (mPimpl->mUnits == nullptr && variable->units() != nullptr) {
                equal = false;
            } else if (mPimpl->mUnits != nullptr) {
                equal = mPimpl->mUnits->equal(variable->units());
            }
            return equal;
        }
    }
    return false;
}

bool Variable::addEquivalence(const VariablePtr &variable1, const VariablePtr &variable2)
{
    if ((variable1 != nullptr) && (variable2 != nullptr)) {
        bool canAdd1 = variable1->mPimpl->setEquivalentTo(variable2);
        bool canAdd2 = variable2->mPimpl->setEquivalentTo(variable1);
        if (canAdd1 && !canAdd2) {
            // Remove connection from variable1, since it can't be added to variable2.
            variable1->mPimpl->unsetEquivalentTo(variable2);
        }
        return canAdd1 && canAdd2;
    }
    return false;
}

bool Variable::addEquivalence(const VariablePtr &variable1, const VariablePtr &variable2, const std::string &mappingId, const std::string &connectionId)
{
    bool added = Variable::addEquivalence(variable1, variable2);
    variable1->mPimpl->setEquivalentMappingId(variable2, mappingId);
    variable1->mPimpl->setEquivalentConnectionId(variable2, connectionId);
    variable2->mPimpl->setEquivalentMappingId(variable1, mappingId);
    variable2->mPimpl->setEquivalentConnectionId(variable1, connectionId);

    return added;
}

bool Variable::removeEquivalence(const VariablePtr &variable1, const VariablePtr &variable2)
{
    bool equivalence_1 = variable1 != nullptr ? variable1->mPimpl->unsetEquivalentTo(variable2) : false;
    bool equivalence_2 = variable2 != nullptr ? variable2->mPimpl->unsetEquivalentTo(variable1) : false;

    return equivalence_1 && equivalence_2;
}

void Variable::removeAllEquivalences()
{
    auto thisVariable = shared_from_this();
    for (const auto &variable : mPimpl->mEquivalentVariables) {
        if (!variable.expired()) {
            variable.lock()->mPimpl->unsetEquivalentTo(thisVariable);
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
    mPimpl->cleanExpiredVariables();
    return mPimpl->mEquivalentVariables.size();
}

bool Variable::hasEquivalentVariable(const VariablePtr &equivalentVariable, bool considerIndirectEquivalences) const
{
    return mPimpl->hasEquivalentVariable(equivalentVariable, considerIndirectEquivalences);
}

void Variable::VariableImpl::cleanExpiredVariables()
{
    mEquivalentVariables.erase(std::remove_if(mEquivalentVariables.begin(), mEquivalentVariables.end(), [=](const VariableWeakPtr &variableWeak) -> bool { return variableWeak.expired(); }), mEquivalentVariables.end());
}

bool Variable::VariableImpl::hasEquivalentVariable(const VariablePtr &equivalentVariable, bool considerIndirectEquivalences) const
{
    bool equivalent = false;
    if (considerIndirectEquivalences) {
        equivalent = hasIndirectEquivalentVariable(equivalentVariable);
    } else {
        auto it = findEquivalentVariable(equivalentVariable);
        if (it == mEquivalentVariables.end()) {
            return false;
        }
        equivalent = !it->expired();
    }

    return equivalent;
}

/**
 * @brief Test if the two variables given are equivalent, directly or indirectly.
 *
 * Traverse the variable equivalence network to determine if the two given variables
 * are equivalent.  Returns true if they are equivalent and false otherwise.
 *
 * @param variable1 The first variable to test.
 * @param variable2 The second variable to test.
 * @param testedVariables Vector of previoulsy tested variables.
 *
 * @return True if the two given variables are equivalent, false otherwise.
 */
bool haveEquivalentVariables(const Variable *variable1,
                             const Variable *variable2,
                             std::vector<const Variable *> &testedVariables)
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

bool Variable::VariableImpl::hasIndirectEquivalentVariable(const VariablePtr &equivalentVariable) const
{
    if (mVariable == equivalentVariable.get()) {
        return false;
    }

    std::vector<const Variable *> testedVariables;

    return haveEquivalentVariables(mVariable, equivalentVariable.get(), testedVariables);
}

bool Variable::VariableImpl::setEquivalentTo(const VariablePtr &equivalentVariable)
{
    cleanExpiredVariables();
    if (!hasEquivalentVariable(equivalentVariable)) {
        VariableWeakPtr weakEquivalentVariable = equivalentVariable;
        mEquivalentVariables.push_back(weakEquivalentVariable);
        return true;
    }

    return false;
}

bool Variable::VariableImpl::unsetEquivalentTo(const VariablePtr &equivalentVariable)
{
    cleanExpiredVariables();
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
    mPimpl->mUnits = Units::create(name);
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

bool Variable::hasInterfaceType(InterfaceType interfaceType) const
{
    if (interfaceType == Variable::InterfaceType::NONE && mPimpl->mInterfaceType.empty()) {
        return true;
    }
    return mPimpl->mInterfaceType == interfaceTypeToString.find(interfaceType)->second;
}

bool Variable::permitsInterfaceType(InterfaceType interfaceType) const
{
    std::string testString = interfaceTypeToString.find(interfaceType)->second;

    if ((testString == "none") || testString.empty()) {
        return true;
    }
    if (mPimpl->mInterfaceType == "public_and_private") {
        return true;
    }
    return testString == mPimpl->mInterfaceType;
}

void Variable::setEquivalenceMappingId(const VariablePtr &variable1, const VariablePtr &variable2, const std::string &mappingId)
{
    if (variable1->hasEquivalentVariable(variable2, true) && variable2->hasEquivalentVariable(variable1, true)) {
        variable1->mPimpl->setEquivalentMappingId(variable2, mappingId);
        variable2->mPimpl->setEquivalentMappingId(variable1, mappingId);
    }
}

void Variable::setEquivalenceConnectionId(const VariablePtr &variable1, const VariablePtr &variable2, const std::string &connectionId)
{
    if (variable1->hasEquivalentVariable(variable2, true) && variable2->hasEquivalentVariable(variable1, true)) {
        auto map = createConnectionMap(variable1, variable2);
        for (auto &it : map) {
            it.first->mPimpl->setEquivalentConnectionId(it.second, connectionId);
            it.second->mPimpl->setEquivalentConnectionId(it.first, connectionId);
        }
        if (map.empty()) {
            variable1->mPimpl->setEquivalentConnectionId(variable2, connectionId);
            variable2->mPimpl->setEquivalentConnectionId(variable1, connectionId);
        }
    }
}

std::string Variable::equivalenceMappingId(const VariablePtr &variable1, const VariablePtr &variable2)
{
    std::string id;
    if (variable1->hasEquivalentVariable(variable2, true) && variable2->hasEquivalentVariable(variable1, true)) {
        id = variable1->mPimpl->equivalentMappingId(variable2);
    }
    return id;
}

std::string Variable::equivalenceConnectionId(const VariablePtr &variable1, const VariablePtr &variable2)
{
    std::string id;
    if (variable1->hasEquivalentVariable(variable2, true) && variable2->hasEquivalentVariable(variable1, true)) {
        auto map = createConnectionMap(variable1, variable2);
        for (auto &it : map) {
            id = it.first->mPimpl->equivalentConnectionId(it.second);
        }
        if (id.empty()) {
            id = variable1->mPimpl->equivalentConnectionId(variable2);
        }
    }
    return id;
}

void Variable::removeEquivalenceConnectionId(const VariablePtr &variable1, const VariablePtr &variable2)
{
    if (variable1->hasEquivalentVariable(variable2, true) && variable2->hasEquivalentVariable(variable1, true)) {
        variable1->mPimpl->setEquivalentConnectionId(variable2, "");
        variable2->mPimpl->setEquivalentConnectionId(variable1, "");
    }
}

void Variable::removeEquivalenceMappingId(const VariablePtr &variable1, const VariablePtr &variable2)
{
    if (variable1->hasEquivalentVariable(variable2, true) && variable2->hasEquivalentVariable(variable1, true)) {
        variable1->mPimpl->setEquivalentMappingId(variable2, "");
        variable2->mPimpl->setEquivalentMappingId(variable1, "");
    }
}

VariablePtr Variable::clone() const
{
    auto v = create();

    if (mPimpl->mUnits != nullptr) {
        v->setUnits(mPimpl->mUnits->clone());
    }
    v->setInitialValue(initialValue());
    v->setInterfaceType(interfaceType());
    v->setId(id());
    v->setName(name());

    return v;
}

} // namespace libcellml
