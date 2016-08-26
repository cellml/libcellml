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
    std::vector<ComponentPtr>::iterator findComponent(const std::string &name);
    std::vector<ComponentPtr>::iterator findComponent(const ComponentPtr &component);
    std::vector<UnitsPtr>::iterator findUnits(const std::string &name);
    std::vector<UnitsPtr>::iterator findUnits(const UnitsPtr &units);
    std::vector<ComponentPtr> mComponents;
    std::vector<UnitsPtr> mUnits;
};

std::vector<ComponentPtr>::iterator ComponentEntity::ComponentEntityImpl::findComponent(const std::string &name)
{
    return std::find_if(mComponents.begin(), mComponents.end(),
                        [=](const ComponentPtr& c) -> bool { return c->getName() == name; });
}

std::vector<ComponentPtr>::iterator ComponentEntity::ComponentEntityImpl::findComponent(const ComponentPtr &component)
{
    return std::find_if(mComponents.begin(), mComponents.end(),
                        [=](const ComponentPtr& c) -> bool { return c == component; });
}

std::vector<UnitsPtr>::iterator ComponentEntity::ComponentEntityImpl::findUnits(const std::string &name)
{
    return std::find_if(mUnits.begin(), mUnits.end(),
                        [=](const UnitsPtr& u) -> bool { return u->getName() == name; });
}

std::vector<UnitsPtr>::iterator ComponentEntity::ComponentEntityImpl::findUnits(const UnitsPtr &units)
{
    return std::find_if(mUnits.begin(), mUnits.end(),
                        [=](const UnitsPtr& u) -> bool { return u == units; });
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

ComponentEntity::ComponentEntity(const ComponentEntity &rhs)
    : ImportedEntity(rhs)
    , mPimpl(new ComponentEntityImpl())
{
    mPimpl->mComponents = rhs.mPimpl->mComponents;
    mPimpl->mUnits = rhs.mPimpl->mUnits;
}

ComponentEntity::ComponentEntity(ComponentEntity &&rhs)
    : ImportedEntity(std::move(rhs))
    , mPimpl(rhs.mPimpl)
{
    rhs.mPimpl = nullptr;
}

ComponentEntity& ComponentEntity::operator=(ComponentEntity c)
{
    ImportedEntity::operator= (c);
    c.swap(*this);
    return *this;
}

void ComponentEntity::swap(ComponentEntity &rhs)
{
    std::swap(this->mPimpl, rhs.mPimpl);
}

std::string ComponentEntity::serialiseUnits(Format format) const
{
    std::string repr = "";

    if (format == Format::XML) {
        for (std::vector<UnitsPtr>::size_type i = 0; i != mPimpl->mUnits.size(); ++i) {
            repr += mPimpl->mUnits[i]->serialise(format);;
        }
    }

    return repr;
}

std::string ComponentEntity::serialiseEncapsulation(Format format) const
{
    const std::string encaps_tag = "<encapsulation>";
    const std::string encaps_end_tag = "</encapsulation>";
    std::string repr = "";
    if (format == Format::XML) {
        std::string componentName = getName();
        std::string encaps = "";
        if (mPimpl->mComponents.size()) {
            encaps += encaps_tag;
            encaps += "<component_ref";
            if (componentName.length()) {
                encaps += " component=\"" + componentName + "\"";
            }
            encaps += ">";
        }
        for (std::vector<Component>::size_type i = 0; i != mPimpl->mComponents.size(); ++i) {
            std::string comp = mPimpl->mComponents[i]->serialise(format);
            std::size_t found = comp.find(encaps_tag);
            if (found == std::string::npos) {
                encaps += "<component_ref";
                if (mPimpl->mComponents[i]->getName().length()) {
                    encaps += " component=\"" + mPimpl->mComponents[i]->getName() + "\"";
                }
                encaps += "/>";
            } else {
                std::string encaps_part = comp.substr(found);
                comp = comp.substr(0, found);
                found = encaps_part.find(encaps_tag);
                encaps_part.replace(found, encaps_tag.length(), "");
                found = encaps_part.find(encaps_end_tag);
                encaps_part.replace(found, encaps_end_tag.length(), "");
                encaps += encaps_part;
            }
            repr += comp;
        }

        if (mPimpl->mComponents.size()) {
            encaps += "</component_ref>" + encaps_end_tag;
        }
        repr += encaps;
    }
    return repr;
}

void ComponentEntity::addUnits(const UnitsPtr & units)
{
    mPimpl->mUnits.push_back(units);
}

void ComponentEntity::removeUnits(size_t index)
{
    if (index < mPimpl->mUnits.size()) {
        mPimpl->mUnits.erase(mPimpl->mUnits.begin() + index);
    } else {
        throw std::out_of_range("Index out of range.");
    }
}

void ComponentEntity::removeUnits(const std::string &name)
{
    auto result = mPimpl->findUnits(name);
    if (result != mPimpl->mUnits.end()) {
        mPimpl->mUnits.erase(result);
    } else {
        throw std::out_of_range("Named units not found.");
    }
}

void ComponentEntity::removeUnits(const UnitsPtr &units)
{
    auto result = mPimpl->findUnits(units);
    if (result != mPimpl->mUnits.end()) {
        mPimpl->mUnits.erase(result);
    } else {
        throw std::out_of_range("Units pointer not found.");
    }
}

void ComponentEntity::removeAllUnits()
{
    mPimpl->mUnits.clear();
}

bool ComponentEntity::hasUnits(const std::string &name) const
{
    return mPimpl->findUnits(name) != mPimpl->mUnits.end();
}

UnitsPtr ComponentEntity::getUnits(size_t index) const
{
    if (index < mPimpl->mUnits.size()) {
        return mPimpl->mUnits.at(index);
    }
    return nullptr;
}

UnitsPtr ComponentEntity::getUnits(const std::string &name) const
{
    auto result = mPimpl->findUnits(name);
    if (result == mPimpl->mUnits.end()) {
        return nullptr;
    }

    return *result;
}

UnitsPtr ComponentEntity::takeUnits(size_t index)
{
    UnitsPtr units = mPimpl->mUnits.at(index);
    removeUnits(index);
    units->clearParent();
    return units;
}

UnitsPtr ComponentEntity::takeUnits(const std::string &name)
{
    return takeUnits(mPimpl->findUnits(name) - mPimpl->mUnits.begin());
}

void ComponentEntity::replaceUnits(size_t index, const UnitsPtr &units)
{
    removeUnits(index);
    mPimpl->mUnits.insert(mPimpl->mUnits.begin() + index, units);
}

void ComponentEntity::replaceUnits(const std::string &name, const UnitsPtr &units)
{
    replaceUnits(mPimpl->findUnits(name) - mPimpl->mUnits.begin(), units);
}

size_t ComponentEntity::unitsCount() const
{
    return mPimpl->mUnits.size();
}

void ComponentEntity::addComponent(const ComponentPtr &c)
{
    doAddComponent(c);
}

void ComponentEntity::doAddComponent(const ComponentPtr &c)
{
    mPimpl->mComponents.push_back(c);
}

void ComponentEntity::removeComponent(size_t index)
{
    if (index < mPimpl->mComponents.size()) {
        mPimpl->mComponents.erase(mPimpl->mComponents.begin() + index);
    } else {
        throw std::out_of_range("Index out of range.");
    }
}

void ComponentEntity::removeComponent(const std::string &name, bool searchEncapsulated)
{
    if (containsComponentInThis(name)) {
        removeComponentInThis(name);
    } else if (searchEncapsulated) {
        for (size_t i = 0; i < componentCount(); ++i) {
            if (getComponent(i)->containsComponent(name, searchEncapsulated)) {
                getComponent(i)->removeComponent(name, searchEncapsulated);
                break;
            }
        }
    }
}

void ComponentEntity::removeComponent(const ComponentPtr &component, bool searchEncapsulated)
{
    if (containsComponentInThis(component)) {
        removeComponentInThis(component);
    } else if (searchEncapsulated) {
        for (size_t i = 0; i < componentCount(); ++i) {
            if (getComponent(i)->containsComponent(component, searchEncapsulated)) {
                getComponent(i)->removeComponent(component, searchEncapsulated);
                break;
            }
        }
    }
}

void ComponentEntity::removeAllComponents()
{
    mPimpl->mComponents.clear();
}

size_t ComponentEntity::componentCount() const
{
    return mPimpl->mComponents.size();
}

bool ComponentEntity::containsComponent(const std::string &name, bool searchEncapsulated) const
{
    bool result = false;
    if (containsComponentInThis(name)) {
        result = true;
    } else if (searchEncapsulated) {
        for (size_t i = 0; i < componentCount(); ++i) {
            result = getComponent(i)->containsComponent(name, searchEncapsulated);
            if (result) {
                break;
            }
        }
    }

    return result;
}

bool ComponentEntity::containsComponent(const ComponentPtr &component, bool searchEncapsulated) const
{
    bool result = false;
    if (containsComponentInThis(component)) {
        result = true;
    } else if (searchEncapsulated) {
        for (size_t i = 0; i < componentCount(); ++i) {
            result = getComponent(i)->containsComponent(component, searchEncapsulated);
            if (result) {
                break;
            }
        }
    }

    return result;
}

ComponentPtr ComponentEntity::getComponent(size_t index) const
{
    if (index < mPimpl->mComponents.size()) {
        return mPimpl->mComponents.at(index);
    }

    return nullptr;
}

ComponentPtr ComponentEntity::getComponent(const std::string &name, bool searchEncapsulated) const
{
    ComponentPtr foundComponent = nullptr;
    if (containsComponentInThis(name)) {
        foundComponent = *(mPimpl->findComponent(name));
    } else if (searchEncapsulated) {
        for (size_t i = 0; i < componentCount(); ++i) {
            foundComponent = getComponent(i)->getComponent(name, searchEncapsulated);
            if (foundComponent) {
                break;
            }
        }
    }

    return foundComponent;
}

ComponentPtr ComponentEntity::takeComponent(size_t index)
{
    ComponentPtr component = nullptr;
    if (index < mPimpl->mComponents.size()) {
        component = mPimpl->mComponents.at(index);
        removeComponent(index);
        component->clearParent();
    }

    return component;
}

ComponentPtr ComponentEntity::takeComponent(const std::string &name, bool searchEncapsulated)
{
    ComponentPtr foundComponent = nullptr;
    if (containsComponentInThis(name)) {
        foundComponent = takeComponentInThis(name);
    } else if (searchEncapsulated) {
        for (size_t i = 0; i < componentCount(); ++i) {
            foundComponent = getComponent(i)->takeComponent(name, searchEncapsulated);
            if (foundComponent) {
                break;
            }
        }
    }

    return foundComponent;
}

void ComponentEntity::replaceComponent(size_t index, const ComponentPtr &c)
{
    removeComponent(index);
    mPimpl->mComponents.insert(mPimpl->mComponents.begin() + index, c);
}

void ComponentEntity::replaceComponent(const std::string &name, const ComponentPtr &component, bool searchEncapsulated)
{
    if (containsComponentInThis(name)) {
        replaceComponentInThis(name, component);
    } else if (searchEncapsulated) {
        for (size_t i = 0; i < componentCount(); ++i) {
            if (getComponent(i)->containsComponent(name, searchEncapsulated)) {
                getComponent(i)->replaceComponent(name, component, searchEncapsulated);
                break;
            }
        }
    }
}

// Begin private component methods.
ComponentPtr ComponentEntity::takeComponentInThis(const std::string &name)
{
    return takeComponent(mPimpl->findComponent(name) - mPimpl->mComponents.begin());
}

void ComponentEntity::replaceComponentInThis(const std::string &name, const ComponentPtr &component)
{
    replaceComponent(mPimpl->findComponent(name) - mPimpl->mComponents.begin(), component);
}

bool ComponentEntity::containsComponentInThis(const ComponentPtr &component) const
{
    return mPimpl->findComponent(component) != mPimpl->mComponents.end();
}

bool ComponentEntity::containsComponentInThis(const std::string &name) const
{
    return mPimpl->findComponent(name) != mPimpl->mComponents.end();
}

void ComponentEntity::removeComponentInThis(const std::string &name)
{
    auto result = mPimpl->findComponent(name);
    if (result != mPimpl->mComponents.end()) {
        mPimpl->mComponents.erase(result);
    }
}

void ComponentEntity::removeComponentInThis(const ComponentPtr &component)
{
    auto result = mPimpl->findComponent(component);
    if (result != mPimpl->mComponents.end()) {
        mPimpl->mComponents.erase(result);
    }
}

}
