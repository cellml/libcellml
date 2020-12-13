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

#include "libcellml/componententity.h"

#include <algorithm>
#include <memory>
#include <vector>

#include "libcellml/component.h"
#include "libcellml/units.h"

namespace libcellml {

/**
 * @brief The ComponentEntity::ComponentEntityImpl struct.
 *
 * This struct is the private implementation struct for the ComponentEntity class.  Separating
 * the implementation from the definition allows for greater flexibility when
 * distributing the code.
 */
struct ComponentEntity::ComponentEntityImpl
{
    std::vector<ComponentPtr> mComponents;
    std::string mEncapsulationId;

    std::vector<ComponentPtr>::iterator findComponent(const std::string &name);
    std::vector<ComponentPtr>::iterator findComponent(const ComponentPtr &component);
};

std::vector<ComponentPtr>::iterator ComponentEntity::ComponentEntityImpl::findComponent(const std::string &name)
{
    return std::find_if(mComponents.begin(), mComponents.end(),
                        [=](const ComponentPtr &c) -> bool { return c->name() == name; });
}

std::vector<ComponentPtr>::iterator ComponentEntity::ComponentEntityImpl::findComponent(const ComponentPtr &component)
{
    return std::find_if(mComponents.begin(), mComponents.end(),
                        [=](const ComponentPtr &c) -> bool { return c->equal(component); });
}

// Interface class Model implementation
ComponentEntity::ComponentEntity()
    : mPimpl(new ComponentEntityImpl())
{
}

ComponentEntity::~ComponentEntity()
{
    delete mPimpl;
}

bool ComponentEntity::addComponent(const ComponentPtr &component)
{
    if (component == nullptr) {
        return false;
    }

    if (std::find(mPimpl->mComponents.begin(), mPimpl->mComponents.end(), component) != mPimpl->mComponents.end()) {
        return false;
    }

    return doAddComponent(component);
}

bool ComponentEntity::doAddComponent(const ComponentPtr &component)
{
    mPimpl->mComponents.push_back(component);
    return true;
}

bool ComponentEntity::removeComponent(const std::string &name, bool searchEncapsulated)
{
    bool status = false;
    auto result = mPimpl->findComponent(name);
    if (result != mPimpl->mComponents.end()) {
        (*result)->removeParent();
        mPimpl->mComponents.erase(result);
        status = true;
    } else if (searchEncapsulated) {
        for (size_t i = 0; i < componentCount() && !status; ++i) {
            status = component(i)->removeComponent(name, searchEncapsulated);
        }
    }

    return status;
}

bool ComponentEntity::removeComponent(size_t index)
{
    bool status = false;
    if (index < mPimpl->mComponents.size()) {
        auto component = mPimpl->mComponents[index];
        mPimpl->mComponents.erase(mPimpl->mComponents.begin() + ptrdiff_t(index));
        component->removeParent();
        status = true;
    }

    return status;
}

bool ComponentEntity::removeComponent(const ComponentPtr &component, bool searchEncapsulated)
{
    bool status = false;
    auto result = mPimpl->findComponent(component);
    if (result != mPimpl->mComponents.end()) {
        (*result)->removeParent();
        mPimpl->mComponents.erase(result);
        status = true;
    } else if (searchEncapsulated) {
        for (size_t i = 0; i < componentCount() && !status; ++i) {
            status = ComponentEntity::component(i)->removeComponent(component, searchEncapsulated);
        }
    }

    return status;
}

void ComponentEntity::removeAllComponents()
{
    for (const auto &component : mPimpl->mComponents) {
        component->removeParent();
    }
    mPimpl->mComponents.clear();
}

size_t ComponentEntity::componentCount() const
{
    return mPimpl->mComponents.size();
}

bool ComponentEntity::containsComponent(const std::string &name, bool searchEncapsulated) const
{
    bool status = false;
    auto result = mPimpl->findComponent(name);
    if (result != mPimpl->mComponents.end()) {
        status = true;
    } else if (searchEncapsulated) {
        for (size_t i = 0; i < componentCount() && !status; ++i) {
            status = component(i)->containsComponent(name, searchEncapsulated);
        }
    }

    return status;
}

bool ComponentEntity::containsComponent(const ComponentPtr &component, bool searchEncapsulated) const
{
    bool status = false;
    auto result = mPimpl->findComponent(component);
    if (result != mPimpl->mComponents.end()) {
        status = true;
    } else if (searchEncapsulated) {
        for (size_t i = 0; i < componentCount() && !status; ++i) {
            status = ComponentEntity::component(i)->containsComponent(component, searchEncapsulated);
        }
    }

    return status;
}

ComponentPtr ComponentEntity::component(size_t index) const
{
    ComponentPtr component = nullptr;
    if (index < mPimpl->mComponents.size()) {
        component = mPimpl->mComponents.at(index);
    }

    return component;
}

ComponentPtr ComponentEntity::component(const std::string &name, bool searchEncapsulated) const
{
    ComponentPtr foundComponent = nullptr;
    auto result = mPimpl->findComponent(name);
    if (result != mPimpl->mComponents.end()) {
        foundComponent = *result;
    } else if (searchEncapsulated) {
        for (size_t i = 0; i < componentCount() && !foundComponent; ++i) {
            foundComponent = component(i)->component(name, searchEncapsulated);
        }
    }

    return foundComponent;
}

ComponentPtr ComponentEntity::takeComponent(size_t index)
{
    ComponentPtr component = nullptr;
    if (index < mPimpl->mComponents.size()) {
        component = mPimpl->mComponents.at(index);
        mPimpl->mComponents.erase(mPimpl->mComponents.begin() + ptrdiff_t(index));
        component->removeParent();
    }

    return component;
}

ComponentPtr ComponentEntity::takeComponent(const std::string &name, bool searchEncapsulated)
{
    ComponentPtr foundComponent = nullptr;
    auto result = mPimpl->findComponent(name);
    if (result != mPimpl->mComponents.end()) {
        foundComponent = *result;
        mPimpl->mComponents.erase(result);
        foundComponent->removeParent();
    } else if (searchEncapsulated) {
        for (size_t i = 0; i < componentCount() && !foundComponent; ++i) {
            foundComponent = component(i)->takeComponent(name, searchEncapsulated);
        }
    }

    return foundComponent;
}

bool ComponentEntity::replaceComponent(size_t index, const ComponentPtr &component)
{
    bool status = false;
    ComponentEntityPtr oldComponent = ComponentEntity::component(index);
    EntityPtr parent = nullptr;
    if (oldComponent != nullptr && oldComponent->hasParent()) {
        parent = oldComponent->parent();
    }
    if (removeComponent(index)) {
        mPimpl->mComponents.insert(mPimpl->mComponents.begin() + ptrdiff_t(index), component);
        component->setParent(parent);
        status = true;
    }

    return status;
}

bool ComponentEntity::replaceComponent(const std::string &name, const ComponentPtr &component, bool searchEncapsulated)
{
    bool status = replaceComponent(size_t(mPimpl->findComponent(name) - mPimpl->mComponents.begin()), component);
    if (searchEncapsulated && !status) {
        for (size_t i = 0; i < componentCount() && !status; ++i) {
            status = ComponentEntity::component(i)->replaceComponent(name, component, searchEncapsulated);
        }
    }

    return status;
}

bool ComponentEntity::replaceComponent(const ComponentPtr &oldComponent, const ComponentPtr &newComponent, bool searchEncapsulated)
{
    bool status = replaceComponent(size_t(mPimpl->findComponent(oldComponent) - mPimpl->mComponents.begin()), newComponent);
    if (searchEncapsulated && !status) {
        for (size_t i = 0; i < componentCount() && !status; ++i) {
            status = component(i)->replaceComponent(oldComponent, newComponent, searchEncapsulated);
        }
    }

    return status;
}

void ComponentEntity::setEncapsulationId(const std::string &id)
{
    mPimpl->mEncapsulationId = id;
}

std::string ComponentEntity::encapsulationId() const
{
    return mPimpl->mEncapsulationId;
}

bool ComponentEntity::doEqual(const EntityPtr &other) const
{
    if (NamedEntity::doEqual(other)) {
        auto componentEntity = std::dynamic_pointer_cast<ComponentEntity>(other);
        if (componentEntity != nullptr &&
                mPimpl->mEncapsulationId == componentEntity->encapsulationId() &&
                mPimpl->mComponents.size() == componentEntity->componentCount()) {
            for (const auto &component : mPimpl->mComponents) {
                if (!componentEntity->containsComponent(component, false)) {
                    return false;
                }
            }
        }
        return true;
    }

    return false;
}

} // namespace libcellml
