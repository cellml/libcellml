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
#include <iterator>
#include <numeric>
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
    Component *mQ = nullptr;
    std::string mMath;
    std::vector<ResetPtr> mResets;
    std::vector<VariablePtr> mVariables;

    std::vector<ResetPtr>::const_iterator findReset(const ResetPtr &reset) const;
    std::vector<VariablePtr>::const_iterator findVariable(const std::string &name) const;
    std::vector<VariablePtr>::const_iterator findVariable(const VariablePtr &variable) const;

    bool equalVariables(const ComponentPtr &other) const;
    bool equalResets(const ComponentPtr &other) const;

    bool isResovledWithHistory(ImportHistory &history) const;
};

std::vector<VariablePtr>::const_iterator Component::ComponentImpl::findVariable(const std::string &name) const
{
    return std::find_if(mVariables.begin(), mVariables.end(),
                        [=](const VariablePtr &v) -> bool { return v->name() == name; });
}

std::vector<VariablePtr>::const_iterator Component::ComponentImpl::findVariable(const VariablePtr &variable) const
{
    return std::find_if(mVariables.begin(), mVariables.end(),
                        [=](const VariablePtr &v) -> bool { return v->equals(variable); });
}

std::vector<ResetPtr>::const_iterator Component::ComponentImpl::findReset(const ResetPtr &reset) const
{
    return std::find_if(mResets.begin(), mResets.end(),
                        [=](const ResetPtr &r) -> bool { return r->equals(reset); });
}

bool Component::ComponentImpl::equalVariables(const ComponentPtr &other) const
{
    std::vector<EntityPtr> entities;
    std::copy(mVariables.begin(), mVariables.end(), std::back_inserter(entities));
    return equalEntities(other, entities);
}

bool Component::ComponentImpl::equalResets(const ComponentPtr &other) const
{
    std::vector<EntityPtr> entities;
    std::copy(mResets.begin(), mResets.end(), std::back_inserter(entities));
    return equalEntities(other, entities);
}

Component::Component()
    : mPimpl(new ComponentImpl())
{
    mPimpl->mQ = this;
}

Component::Component(const std::string &name)
    : mPimpl(new ComponentImpl())
{
    mPimpl->mQ = this;
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

bool Component::ComponentImpl::isResovledWithHistory(ImportHistory &history) const
{
    bool resolved = true;
    if (mQ->isImport()) {
        auto model = mQ->importSource()->model();
        if (model == nullptr) {
            resolved = false;
        } else {
            auto importedComponent = model->component(mQ->importReference());
            if (importedComponent == nullptr) {
                resolved = false;
            } else {
                ImportHistoryEntry h = std::make_pair(model, mQ->name());
                if (std::find(history.begin(), history.end(), h) != history.end()) {
                    resolved = false;
                } else {
                    history.push_back(h);
                    resolved = importedComponent->mPimpl->isResovledWithHistory(history);
                }
            }
        }
    }
    for (size_t i = 0; (i < mQ->componentCount()) && resolved; ++i) {
        resolved = mQ->component(i)->mPimpl->isResovledWithHistory(history);
    }

    return resolved;
}

bool Component::doAddComponent(const ComponentPtr &component)
{
    auto newParent = shared_from_this();
    bool hasParent = component->hasParent();
    if (hasParent) {
        if (hasAncestor(component)) {
            return false;
        }
        auto parent = component->parent();
        if (parent != newParent) {
            removeComponentFromEntity(parent, component);
        }
    } else if (!hasParent && hasAncestor(component)) {
        return false;
    } else if (newParent == component) {
        return false;
    }
    component->setParent(newParent);

    return ComponentEntity::doAddComponent(component);
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

    // Prevent adding to multiple components.
    auto thisComponent = shared_from_this();
    if (variable->hasParent() && (thisComponent != variable->parent())) {
        auto otherParent = std::dynamic_pointer_cast<Component>(variable->parent());
        otherParent->removeVariable(variable);
    }

    variable->setParent(thisComponent);
    mPimpl->mVariables.push_back(variable);
    return true;
}

bool Component::removeVariable(size_t index)
{
    if (index < mPimpl->mVariables.size()) {
        auto variable = mPimpl->mVariables[index];
        mPimpl->mVariables.erase(mPimpl->mVariables.begin() + ptrdiff_t(index));
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

    // Prevent adding to multiple components.
    auto thisComponent = shared_from_this();
    if (reset->hasParent() && (thisComponent != reset->parent())) {
        auto otherParent = std::dynamic_pointer_cast<Component>(reset->parent());
        otherParent->removeReset(reset);
    }
    reset->setParent(thisComponent);
    mPimpl->mResets.push_back(reset);
    return true;
}

bool Component::removeReset(size_t index)
{
    if (index < mPimpl->mResets.size()) {
        mPimpl->mResets.at(index)->removeParent();
        mPimpl->mResets.erase(mPimpl->mResets.begin() + ptrdiff_t(index));
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

ComponentPtr Component::clone() const
{
    auto c = create();

    c->setId(id());
    c->setName(name());
    c->setMath(math());

    if (isImport()) {
        c->setImportSource(importSource());
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
        size_t variableIndex = indexOf(r->variable(), shared_from_this());
        if (variableIndex < variableCount()) {
            auto v = c->variable(variableIndex);
            rClone->setVariable(v);
        }
        size_t testVariableIndex = indexOf(r->testVariable(), shared_from_this());
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

bool doRequiresImport(const ComponentPtr &thisComponent)
{
    if (thisComponent->isImport()) {
        return true;
    }
    for (size_t c = 0; c < thisComponent->componentCount(); ++c) {
        if (doRequiresImport(thisComponent->component(c))) {
            return true;
        }
    }
    return false;
}

bool Component::requiresImports()
{
    return doRequiresImport(shared_from_this());
}

bool Component::doIsResolved() const
{
    ImportHistory history;
    return mPimpl->isResovledWithHistory(history);
}

bool Component::doEquals(const EntityPtr &other) const
{
    if (ComponentEntity::doEquals(other)) {
        auto component = std::dynamic_pointer_cast<Component>(other);
        return (component != nullptr) && areEqual(mPimpl->mMath, component->math())
               && mPimpl->equalResets(component) && mPimpl->equalVariables(component)
               && ImportedEntity::doEquals(component);
    }
    return false;
}

} // namespace libcellml
