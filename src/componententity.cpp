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
    /**
     * @brief Remove the component with the given @p name from this component entity.
     *
     * Remove the first component found that matches the given @p name from this
     * component entity. If the @p name is not found throw @c std::out_of_range.
     *
     * @param name The name of the component to remove.
     */
    void removeComponentInThis(const std::string &name);

    /**
     * @brief Remove the component with the given pointer from this component entity.
     *
     * Remove the component with the pointer @p component from this component entity.
     * If the component is not found throw @c std::out_of_range.
     *
     * @overload
     *
     * @param component The pointer to the component to remove.
     */
    void removeComponentInThis(const ComponentPtr &component);

    /**
     * @brief Tests to see if the named component is contained within this component entity.
     *
     * Tests to see if the component with the given @p name is contained
     * within this component entity.  Returns @c true if the component is in the component
     * entity and @c false otherwise.
     *
     * @param name The component name to test for existence in this component entity.
     *
     * @return @c true if the named component is in this component entity and @c false otherwise.
     */
    bool containsComponentInThis(const std::string &name) const;

    /**
     * @brief Tests to see if the component pointer is contained within this component entity.
     *
     * Tests to see if the argument component pointer @p component is contained
     * within this component entity.  Returns @c true if the component is in the component
     * entity and @c false otherwise.
     *
     * @overload
     *
     * @param component The component pointer to test for existence in this component entity.
     *
     * @return @c true if the component is in the component entity and @c false otherwise.
     */
    bool containsComponentInThis(const ComponentPtr &component) const;

    /**
     * @brief Get a component with the given @p name in this component entity.
     *
     * Returns a @c const reference to a component with the given @p name in this
     * component entity.  If the @p name is not valid a @c std::out_of_range
     * exception is thrown.
     *
     * @param name The name of the Component to return.
     *
     * @return A @c const reference to the Component with the given @p name.
     */
    const ComponentPtr& getComponentInThis(const std::string &name) const;

    /**
     * @brief Get a component with the given @p name in this component entity.
     *
     * Returns a reference to a component with the given @p name in this
     * component entity.  If the @p name is not valid a @c std::out_of_range
     * exception is thrown.
     *
     * @param name The name of the Component to return.
     *
     * @return A reference to the Component with the given @p name.
     */
    ComponentPtr getComponentInThis(const std::string &name);

    /**
     * @brief Take the component with the given @p name from this component
     * entity and return it.
     *
     * Takes the component with the given @p name from this component entity
     * and returns it. If an invalid @p name is passed to the method a @c std::out_of_range
     * exception is thrown.
     *
     * @param name The name of the Component to take.
     *
     * @return The Component identified with the given @p name.
     */
    ComponentPtr takeComponentInThis(const std::string &name);

    /**
     * @brief Replace a component with the given @p name in this component entity.
     *
     * Replaces the component with the given @p name in this component entity
     * with @p c. @p name must be a valid name of a component in the Component,
     * otherwise a @c std::out_of_range exception is thrown.
     *
     * @param name The name of the Component to replace.
     * @param c The Component to use for replacement.
     */
    void replaceComponentInThis(const std::string &name, const ComponentPtr &c);

    size_t componentCount() const;

    bool containsComponent(const std::string &name, bool searchEncapsulated) const;
    bool containsComponent(const ComponentPtr &component, bool searchEncapsulated) const;

    ComponentPtr getComponent(size_t index);
    const ComponentPtr& getComponent(size_t index) const;
    ComponentPtr getComponent(const std::string &name, bool searchEncapsulated);
    const ComponentPtr getComponent(const std::string &name, bool searchEncapsulated) const;

    ComponentPtr takeComponent(size_t index);
    ComponentPtr takeComponent(const std::string &name, bool searchEncapsulated);

    void replaceComponent(size_t index, const ComponentPtr &c);
    void replaceComponent(const std::string &name, const ComponentPtr &component, bool searchEncapsulated);

    void removeComponent(const std::string &name, bool searchEncapsulated);
    void removeComponent(size_t index);
    void removeComponent(const ComponentPtr &component, bool searchEncapsulated);

    std::vector<ComponentPtr>::const_iterator findComponent(const std::string &name) const;
    std::vector<ComponentPtr>::const_iterator findComponent(const ComponentPtr &component) const;
    std::vector<UnitsPtr>::iterator findUnits(const std::string &name);
    std::vector<UnitsPtr>::iterator findUnits(const UnitsPtr &units);
    std::vector<ComponentPtr> mComponents;
    std::vector<UnitsPtr> mUnits;
};

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
    auto result = mPimpl->findUnits(name);
    return result != mPimpl->mUnits.end();
}

UnitsPtr ComponentEntity::getUnits(size_t index)
{
    return mPimpl->mUnits.at(index);
}

const UnitsPtr& ComponentEntity::getUnits(size_t index) const
{
    return mPimpl->mUnits.at(index);
}

UnitsPtr ComponentEntity::getUnits(const std::string &name)
{
    auto result = mPimpl->findUnits(name);
    size_t index = result - mPimpl->mUnits.begin();
    return mPimpl->mUnits.at(index);
}

const UnitsPtr& ComponentEntity::getUnits(const std::string &name) const
{
    auto result = mPimpl->findUnits(name);
    size_t index = result - mPimpl->mUnits.begin();
    return mPimpl->mUnits.at(index);
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
    auto result = mPimpl->findUnits(name);
    size_t index = result - mPimpl->mUnits.begin();
    return takeUnits(index);
}

void ComponentEntity::replaceUnits(size_t index, const UnitsPtr &units)
{
    removeUnits(index);
    mPimpl->mUnits.insert(mPimpl->mUnits.begin() + index, units);
}

void ComponentEntity::replaceUnits(const std::string &name, const UnitsPtr &units)
{
    auto result = mPimpl->findUnits(name);
    size_t index = result - mPimpl->mUnits.begin();
    replaceUnits(index, units);
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

void ComponentEntity::removeComponent(const std::string &name, bool searchEncapsulated)
{
    mPimpl->removeComponent(name, searchEncapsulated);
}

void ComponentEntity::removeComponent(size_t index)
{
    mPimpl->removeComponent(index);
}

void ComponentEntity::removeComponent(const ComponentPtr &component, bool searchEncapsulated)
{
    mPimpl->removeComponent(component, searchEncapsulated);
}

void ComponentEntity::ComponentEntityImpl::removeComponent(const std::string &name, bool searchEncapsulated)
{
    bool componentFound = false;
    if (containsComponentInThis(name)) {
        removeComponentInThis(name);
        componentFound = true;
    } else if (searchEncapsulated) {
        for (size_t i = 0; i < componentCount(); ++i) {
            if (getComponent(i)->containsComponent(name, searchEncapsulated)) {
                getComponent(i)->removeComponent(name, searchEncapsulated);
                componentFound = true;
                break;
            }
        }
    }
    if (!componentFound) {
        throw std::out_of_range("Named component not found.");
    }
}

void ComponentEntity::ComponentEntityImpl::removeComponent(size_t index)
{
    if (index < mComponents.size()) {
        mComponents.erase(mComponents.begin() + index);
    } else {
        throw std::out_of_range("Index out of range.");
    }
}

void ComponentEntity::ComponentEntityImpl::removeComponent(const ComponentPtr &component, bool searchEncapsulated)
{
    bool componentFound = false;
    if (containsComponentInThis(component)) {
        removeComponentInThis(component);
        componentFound = true;
    } else if (searchEncapsulated) {
        for (size_t i = 0; i < componentCount(); ++i) {
            if (getComponent(i)->containsComponent(component, searchEncapsulated)) {
                getComponent(i)->removeComponent(component, searchEncapsulated);
                componentFound = true;
                break;
            }
        }
    }
    if (!componentFound) {
        throw std::out_of_range("Component pointer not found.");
    }
}

void ComponentEntity::removeAllComponents()
{
    mPimpl->mComponents.clear();
}

size_t ComponentEntity::ComponentEntityImpl::componentCount() const
{
    return mComponents.size();
}

size_t ComponentEntity::componentCount() const
{
    return mPimpl->componentCount();
}

bool ComponentEntity::containsComponent(const std::string &name, bool searchEncapsulated) const
{
    return mPimpl->containsComponent(name, searchEncapsulated);
}

bool ComponentEntity::containsComponent(const ComponentPtr &component, bool searchEncapsulated) const
{
    return mPimpl->containsComponent(component, searchEncapsulated);
}

bool ComponentEntity::ComponentEntityImpl::containsComponent(const std::string &name, bool searchEncapsulated) const
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

bool ComponentEntity::ComponentEntityImpl::containsComponent(const ComponentPtr &component, bool searchEncapsulated) const
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

ComponentPtr ComponentEntity::getComponent(size_t index)
{
    return mPimpl->getComponent(index);
}

const ComponentPtr& ComponentEntity::getComponent(size_t index) const
{
    return mPimpl->mComponents.at(index);
}

ComponentPtr ComponentEntity::getComponent(const std::string &name, bool searchEncapsulated)
{
    return mPimpl->getComponent(name, searchEncapsulated);
}

const ComponentPtr ComponentEntity::getComponent(const std::string &name, bool searchEncapsulated) const
{
    return static_cast<const libcellml::ComponentEntity::ComponentEntityImpl *>(mPimpl)->getComponent(name, searchEncapsulated);
}

ComponentPtr ComponentEntity::ComponentEntityImpl::getComponent(size_t index)
{
    return mComponents.at(index);
}

const ComponentPtr& ComponentEntity::ComponentEntityImpl::getComponent(size_t index) const
{
    return mComponents.at(index);
}

ComponentPtr ComponentEntity::ComponentEntityImpl::getComponent(const std::string &name, bool searchEncapsulated)
{
    ComponentPtr foundComponent = nullptr;
    if (containsComponentInThis(name)) {
        foundComponent = getComponentInThis(name);
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

const ComponentPtr ComponentEntity::ComponentEntityImpl::getComponent(const std::string &name, bool searchEncapsulated) const
{
    if (containsComponent(name, searchEncapsulated)) {
        if (containsComponentInThis(name)) {
            return getComponentInThis(name);
        } else if (searchEncapsulated) {
            for (size_t i = 0; i < componentCount(); ++i) {
                if (getComponent(i)->containsComponent(name, searchEncapsulated)) {
                    return getComponent(i)->getComponent(name, searchEncapsulated);
                }
            }
        }
    }
    throw std::out_of_range("Named component not found.");
}

ComponentPtr ComponentEntity::takeComponent(size_t index)
{
    return mPimpl->takeComponent(index);
}

ComponentPtr ComponentEntity::takeComponent(const std::string &name, bool searchEncapsulated)
{
    return mPimpl->takeComponent(name, searchEncapsulated);
}

ComponentPtr ComponentEntity::ComponentEntityImpl::takeComponent(size_t index)
{
    ComponentPtr c = mComponents.at(index);
    removeComponent(index);
    c->clearParent();
    return c;
}

ComponentPtr ComponentEntity::ComponentEntityImpl::takeComponent(const std::string &name, bool searchEncapsulated)
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
    if (!foundComponent) {
        throw std::out_of_range("Named component not found.");
    }
    return foundComponent;
}

void ComponentEntity::replaceComponent(size_t index, const ComponentPtr &c)
{
    mPimpl->replaceComponent(index, c);
}

void ComponentEntity::replaceComponent(const std::string &name, const ComponentPtr &component, bool searchEncapsulated)
{
    mPimpl->replaceComponent(name, component, searchEncapsulated);
}

void ComponentEntity::ComponentEntityImpl::replaceComponent(size_t index, const ComponentPtr &c)
{
    removeComponent(index);
    mComponents.insert(mComponents.begin() + index, c);
}

void ComponentEntity::ComponentEntityImpl::replaceComponent(const std::string &name, const ComponentPtr &component, bool searchEncapsulated)
{
    bool componentFound = false;
    if (containsComponentInThis(name)) {
        replaceComponentInThis(name, component);
        componentFound = true;
    } else if (searchEncapsulated) {
        for (size_t i = 0; i < componentCount(); ++i) {
            if (getComponent(i)->containsComponent(name, searchEncapsulated)) {
                getComponent(i)->replaceComponent(name, component, searchEncapsulated);
                componentFound = true;
                break;
            }
        }
    }
    if (!componentFound) {
        throw std::out_of_range("Named component not found.");
    }
}

// Begin private component methods.
ComponentPtr ComponentEntity::ComponentEntityImpl::takeComponentInThis(const std::string &name)
{
    auto result = findComponent(name);
    size_t index = result - mComponents.begin();
    return takeComponent(index);
}

void ComponentEntity::ComponentEntityImpl::replaceComponentInThis(const std::string &name, const ComponentPtr &component)
{
    auto result = findComponent(name);
    size_t index = result - mComponents.begin();
    replaceComponent(index, component);
}

bool ComponentEntity::ComponentEntityImpl::containsComponentInThis(const ComponentPtr &component) const
{
    auto result = findComponent(component);
    return result != mComponents.end();
}

bool ComponentEntity::ComponentEntityImpl::containsComponentInThis(const std::string &name) const
{
    return findComponent(name) != mComponents.end();
}

ComponentPtr ComponentEntity::ComponentEntityImpl::getComponentInThis(const std::string &name)
{
    auto result = findComponent(name);
    size_t index = result - mComponents.begin();
    return mComponents.at(index);
}

const ComponentPtr& ComponentEntity::ComponentEntityImpl::getComponentInThis(const std::string &name) const
{
    auto result = findComponent(name);
    size_t index = result - mComponents.begin();
    return mComponents.at(index);
}

void ComponentEntity::ComponentEntityImpl::removeComponentInThis(const std::string &name)
{
    auto result = findComponent(name);
    if (result != mComponents.end()) {
        mComponents.erase(result);
    }
}

void ComponentEntity::ComponentEntityImpl::removeComponentInThis(const ComponentPtr &component)
{
    auto result = findComponent(component);
    if (result != mComponents.end()) {
        mComponents.erase(result);
    }
}

}
