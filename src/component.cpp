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

#include "libcellml/component.h"

#include <algorithm>
#include <string>
#include <vector>

#include "libcellml/importsource.h"
#include "libcellml/model.h"
#include "libcellml/reset.h"
#include "libcellml/units.h"
#include "libcellml/variable.h"

#include "utilities.h"

namespace libcellml {

/**
 * @brief The Component::ComponentImpl struct.
 *
 * This struct is the private implementation struct for the Component class.  Separating
 * the implementation from the definition allows for greater flexibility when
 * distributing the code.
 */
struct Component::ComponentImpl
{
    std::string mMath;
    std::vector<ResetPtr> mResets;
    std::vector<VariablePtr> mVariables;

    std::vector<ResetPtr>::iterator findReset(const ResetPtr &reset);
    std::vector<VariablePtr>::iterator findVariable(const std::string &name);
    std::vector<VariablePtr>::iterator findVariable(const VariablePtr &variable);
};

std::vector<VariablePtr>::iterator Component::ComponentImpl::findVariable(const std::string &name)
{
    return std::find_if(mVariables.begin(), mVariables.end(),
                        [=](const VariablePtr &v) -> bool { return v->name() == name; });
}

std::vector<VariablePtr>::iterator Component::ComponentImpl::findVariable(const VariablePtr &variable)
{
    return std::find_if(mVariables.begin(), mVariables.end(),
                        [=](const VariablePtr &v) -> bool { return v == variable; });
}

std::vector<ResetPtr>::iterator Component::ComponentImpl::findReset(const ResetPtr &reset)
{
    return std::find_if(mResets.begin(), mResets.end(),
                        [=](const ResetPtr &r) -> bool { return r == reset; });
}

Component::Component()
    : mPimpl(new ComponentImpl())
{
}

Component::Component(const std::string &name)
    : mPimpl(new ComponentImpl())
{
    setName(name);
}

Component::~Component()
{
    if (mPimpl != nullptr) {
        for (const auto &variable : mPimpl->mVariables) {
            variable->removeParent();
        }
    }
    delete mPimpl;
}

ComponentPtr Component::create() noexcept
{
    return std::shared_ptr<Component> {new Component {}};
}

ComponentPtr Component::create(const std::string &name) noexcept
{
    return std::shared_ptr<Component> {new Component {name}};
}

bool Component::doAddComponent(const ComponentPtr &component)
{
    bool hasParent = component->hasParent();
    if (hasParent) {
        if (hasAncestor(component)) {
            return false;
        }
        auto parent = component->parent();
        removeComponentFromEntity(parent, component);
    } else if (!hasParent && hasAncestor(component)) {
        return false;
    } else if (shared_from_this() == component) {
        return false;
    }
    component->setParent(shared_from_this());

    if (component->isImport()) {
        auto model = owningModel(shared_from_this());
        if (model != nullptr) {
            model->addImportSource(component->importSource());
        }
    }

    return ComponentEntity::doAddComponent(component);
}

void Component::setImportSource(ImportSourcePtr &importSource)
{
    auto component = shared_from_this();
    auto oldImportSource = component->importSource();

    if (importSource != nullptr) {
        importSource->addComponent(component);
    }

    auto model = owningModel(component);
    if (model != nullptr) {
        model->addImportSource(importSource);
    }

    if (oldImportSource != nullptr) {
        oldImportSource->removeComponent(component, false);
    }

    ImportedEntity::setImportSource(importSource);
}

void Component::setSourceComponent(ImportSourcePtr &importSource, const std::string &name)
{
    setImportSource(importSource);
    setImportReference(name);
}

void Component::appendMath(const std::string &math)
{
    mPimpl->mMath.append(math);
}

std::string Component::math() const
{
    return mPimpl->mMath;
}

void Component::setMath(const std::string &math)
{
    mPimpl->mMath = math;
}

void Component::removeMath()
{
    mPimpl->mMath.clear();
}

bool Component::addVariable(const VariablePtr &variable)
{
    // Prevent adding null pointer.
    if (variable == nullptr) {
        return false;
    }

    // Prevent adding multiple times to list.
    if (hasVariable(variable)) {
        return false;
    }

    // Prevent adding to multiple components.
    if (variable->hasParent()) {
        auto otherParent = std::dynamic_pointer_cast<Component>(variable->parent());
        otherParent->removeVariable(variable);
    }

    mPimpl->mVariables.push_back(variable);
    variable->setParent(shared_from_this());
    return true;
}

bool Component::removeVariable(size_t index)
{
    if (index < mPimpl->mVariables.size()) {
        auto variable = mPimpl->mVariables[index];
        mPimpl->mVariables.erase(mPimpl->mVariables.begin() + int64_t(index));
        variable->removeParent();
        return true;
    }

    return false;
}

bool Component::removeVariable(const std::string &name)
{
    auto result = mPimpl->findVariable(name);
    if (result != mPimpl->mVariables.end()) {
        (*result)->removeParent();
        mPimpl->mVariables.erase(result);
        return true;
    }

    return false;
}

bool Component::removeVariable(const VariablePtr &variable)
{
    auto result = mPimpl->findVariable(variable);
    if (result != mPimpl->mVariables.end()) {
        mPimpl->mVariables.erase(result);
        variable->removeParent();
        return true;
    }

    return false;
}

void Component::removeAllVariables()
{
    for (const auto &variable : mPimpl->mVariables) {
        variable->removeParent();
    }
    mPimpl->mVariables.clear();
}

VariablePtr Component::variable(size_t index) const
{
    if (index < mPimpl->mVariables.size()) {
        return mPimpl->mVariables.at(index);
    }

    return nullptr;
}

VariablePtr Component::variable(const std::string &name) const
{
    auto result = mPimpl->findVariable(name);
    if (result != mPimpl->mVariables.end()) {
        return *result;
    }

    return nullptr;
}

VariablePtr Component::takeVariable(size_t index)
{
    VariablePtr variable = nullptr;
    if (index < mPimpl->mVariables.size()) {
        variable = mPimpl->mVariables.at(index);
        removeVariable(index);
        variable->removeParent();
    }

    return variable;
}

VariablePtr Component::takeVariable(const std::string &name)
{
    VariablePtr res = variable(name);
    removeVariable(name);

    return res;
}

size_t Component::variableCount() const
{
    return mPimpl->mVariables.size();
}

bool Component::hasVariable(const VariablePtr &variable) const
{
    return mPimpl->findVariable(variable) != mPimpl->mVariables.end();
}

bool Component::hasVariable(const std::string &name) const
{
    return mPimpl->findVariable(name) != mPimpl->mVariables.end();
}

bool Component::addReset(const ResetPtr &reset)
{
    // Prevent adding null pointer.
    if (reset == nullptr) {
        return false;
    }

    // Prevent adding multiple times to list.
    if (hasReset(reset)) {
        return false;
    }

    // Prevent adding to multiple components.
    if (reset->hasParent()) {
        auto otherParent = std::dynamic_pointer_cast<Component>(reset->parent());
        otherParent->removeReset(reset);
    }
    reset->setParent(shared_from_this());
    mPimpl->mResets.push_back(reset);
    return true;
}

bool Component::removeReset(size_t index)
{
    if (index < mPimpl->mResets.size()) {
        mPimpl->mResets.at(index)->removeParent();
        mPimpl->mResets.erase(mPimpl->mResets.begin() + int64_t(index));
        return true;
    }
    return false;
}

bool Component::removeReset(const ResetPtr &reset)
{
    auto result = mPimpl->findReset(reset);
    if (result != mPimpl->mResets.end()) {
        (*result)->removeParent();
        mPimpl->mResets.erase(result);
        return true;
    }
    return false;
}

void Component::removeAllResets()
{
    for (const auto &reset : mPimpl->mResets) {
        reset->removeParent();
    }
    mPimpl->mResets.clear();
}

ResetPtr Component::takeReset(size_t index)
{
    ResetPtr reset = nullptr;
    if (index < mPimpl->mResets.size()) {
        reset = mPimpl->mResets.at(index);
        removeReset(index);
        reset->removeParent();
    }

    return reset;
}

ResetPtr Component::reset(size_t index) const
{
    if (index < mPimpl->mResets.size()) {
        return mPimpl->mResets.at(index);
    }

    return nullptr;
}

size_t Component::resetCount() const
{
    return mPimpl->mResets.size();
}

bool Component::hasReset(const ResetPtr &reset) const
{
    return mPimpl->findReset(reset) != mPimpl->mResets.end();
}

size_t getVariableIndexInComponent(const std::shared_ptr<const Component> &component, const VariablePtr &variable)
{
    size_t index = 0;
    bool found = false;
    while (index < component->variableCount() && !found) {
        if (component->variable(index) == variable) {
            found = true;
        } else {
            ++index;
        }
    }

    return index;
}

ComponentPtr Component::clone() const
{
    auto c = create();

    c->setId(id());
    c->setName(name());
    c->setMath(math());

    if (isImport()) {
        auto imp = importSource()->clone();
        c->setImportSource(imp);
    }

    c->setImportReference(importReference());

    for (size_t index = 0; index < variableCount(); ++index) {
        auto v = variable(index);
        c->addVariable(v->clone());
    }

    for (size_t index = 0; index < resetCount(); ++index) {
        auto r = reset(index);
        auto rClone = r->clone();
        c->addReset(rClone);
        size_t variableIndex = getVariableIndexInComponent(shared_from_this(), r->variable());
        if (variableIndex < variableCount()) {
            auto v = c->variable(variableIndex);
            rClone->setVariable(v);
        }
        size_t testVariableIndex = getVariableIndexInComponent(shared_from_this(), r->testVariable());
        if (testVariableIndex < variableCount()) {
            auto v = c->variable(testVariableIndex);
            rClone->setTestVariable(v);
        }
    }

    for (size_t index = 0; index < componentCount(); ++index) {
        auto cChild = component(index);
        c->addComponent(cChild->clone());
    }

    return c;
}

} // namespace libcellml
