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
    std::vector<ComponentPtr>::const_iterator findComponent(const std::string &name) const;
    std::vector<ComponentPtr>::const_iterator findComponent(const ComponentPtr &component) const;
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

std::vector<ComponentPtr>::const_iterator ComponentEntity::ComponentEntityImpl::findComponent(const std::string &name) const
{
    return std::find_if(mComponents.begin(), mComponents.end(),
                        [=](const ComponentPtr& c) -> bool { return c->getName() == name; });
}

std::vector<ComponentPtr>::const_iterator ComponentEntity::ComponentEntityImpl::findComponent(const ComponentPtr &component) const
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

bool ComponentEntity::removeUnits(size_t index)
{
    bool status = false;
    if (index < mPimpl->mUnits.size()) {
        mPimpl->mUnits.erase(mPimpl->mUnits.begin() + index);
        status = true;
    }

    return status;
}

bool ComponentEntity::removeUnits(const std::string &name)
{
    bool status = false;
    auto result = mPimpl->findUnits(name);
    if (result != mPimpl->mUnits.end()) {
        mPimpl->mUnits.erase(result);
        status = true;
    }

    return status;
}

bool ComponentEntity::removeUnits(const UnitsPtr &units)
{
    bool status = false;
    auto result = mPimpl->findUnits(units);
    if (result != mPimpl->mUnits.end()) {
        mPimpl->mUnits.erase(result);
        status = true;
    }

    return status;
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
    UnitsPtr units = nullptr;
    if (index < mPimpl->mUnits.size()) {
        units = mPimpl->mUnits.at(index);
    }

    return units;
}

UnitsPtr ComponentEntity::getUnits(const std::string &name) const
{
    UnitsPtr units = nullptr;
    auto result = mPimpl->findUnits(name);
    if (result != mPimpl->mUnits.end()) {
        units = *result;
    }

    return units;
}

UnitsPtr ComponentEntity::takeUnits(size_t index)
{
    UnitsPtr units = nullptr;
    if (index < mPimpl->mUnits.size()) {
        units = mPimpl->mUnits.at(index);
        removeUnits(index);
        units->clearParent();
    }

    return units;
}

UnitsPtr ComponentEntity::takeUnits(const std::string &name)
{
    return takeUnits(mPimpl->findUnits(name) - mPimpl->mUnits.begin());
}

bool ComponentEntity::replaceUnits(size_t index, const UnitsPtr &units)
{
    bool status = false;
    if (index < mPimpl->mUnits.size()) {
        removeUnits(index);
        mPimpl->mUnits.insert(mPimpl->mUnits.begin() + index, units);
        status = true;
    }

    return status;
}

bool ComponentEntity::replaceUnits(const std::string &name, const UnitsPtr &units)
{
    return replaceUnits(mPimpl->findUnits(name) - mPimpl->mUnits.begin(), units);
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

bool ComponentEntity::removeComponent(const std::string &name, bool searchEncapsulated)
{
    bool status = false;
    auto result = mPimpl->findComponent(name);
    if (result != mPimpl->mComponents.end()) {
        mPimpl->mComponents.erase(result);
        status = true;
    } else if (searchEncapsulated) {
        for (size_t i = 0; i < componentCount() && !status; ++i) {
            status = getComponent(i)->removeComponent(name, searchEncapsulated);
        }
    }

    return status;
}

bool ComponentEntity::removeComponent(size_t index)
{
    bool status = false;
    if (index < mPimpl->mComponents.size()) {
        mPimpl->mComponents.erase(mPimpl->mComponents.begin() + index);
        status = true;
    }

    return status;
}

bool ComponentEntity::removeComponent(const ComponentPtr &component, bool searchEncapsulated)
{
    bool status = false;
    auto result = mPimpl->findComponent(component);
    if (result != mPimpl->mComponents.end()) {
        mPimpl->mComponents.erase(result);
        status = true;
    } else if (searchEncapsulated) {
        for (size_t i = 0; i < componentCount() && !status; ++i) {
            status = getComponent(i)->removeComponent(component, searchEncapsulated);
        }
    }

    return status;
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
    bool status = false;
    auto result = mPimpl->findComponent(name);
    if (result != mPimpl->mComponents.end()) {
        status = true;
    } else if (searchEncapsulated) {
        for (size_t i = 0; i < componentCount() && !status; ++i) {
            status = getComponent(i)->containsComponent(name, searchEncapsulated);
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
            status = getComponent(i)->containsComponent(component, searchEncapsulated);
        }
    }

    return status;
}

ComponentPtr ComponentEntity::getComponent(size_t index) const
{
    ComponentPtr component = nullptr;
    if (index < mPimpl->mComponents.size()) {
        component = mPimpl->mComponents.at(index);
    }

    return component;
}

ComponentPtr ComponentEntity::getComponent(const std::string &name, bool searchEncapsulated) const
{
    ComponentPtr foundComponent = nullptr;
    auto result = mPimpl->findComponent(name);
    if (result != mPimpl->mComponents.end()) {
        foundComponent = *result;
    } else if (searchEncapsulated) {
        for (size_t i = 0; i < componentCount() && !foundComponent; ++i) {
            foundComponent = getComponent(i)->getComponent(name, searchEncapsulated);
        }
    }

    return foundComponent;
}

ComponentPtr ComponentEntity::takeComponent(size_t index)
{
    ComponentPtr component = nullptr;
    if (index < mPimpl->mComponents.size()) {
        component = mPimpl->mComponents.at(index);
        mPimpl->mComponents.erase(mPimpl->mComponents.begin() + index);
        component->clearParent();
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
    } else if (searchEncapsulated) {
        for (size_t i = 0; i < componentCount() && !foundComponent; ++i) {
            foundComponent = getComponent(i)->takeComponent(name, searchEncapsulated);
        }
    }

    return foundComponent;
}

bool ComponentEntity::replaceComponent(size_t index, const ComponentPtr &c)
{
    bool status = false;
    if (index < mPimpl->mComponents.size()) {
        removeComponent(index);
        mPimpl->mComponents.insert(mPimpl->mComponents.begin() + index, c);
        status = true;
    }

    return status;
}

bool ComponentEntity::replaceComponent(const std::string &name, const ComponentPtr &component, bool searchEncapsulated)
{
    bool status = replaceComponent(mPimpl->findComponent(name) - mPimpl->mComponents.begin(), component);
    if (searchEncapsulated && !status) {
        for (size_t i = 0; i < componentCount() && !status; ++i) {
            status = getComponent(i)->replaceComponent(name, component, searchEncapsulated);
        }
    }

    return status;
}

}
