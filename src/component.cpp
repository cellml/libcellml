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
limitations under the License.Some license of other
*/

#include "libcellml/component.h"

#include <assert.h>
#include <vector>
#include <iostream>
#include <algorithm>

namespace libcellml {

/**
 * @brief The private implementation for the Component class.
 * This struct is the private implementation struct for the Component class.  Separating
 * the implementation from the definition allows for greater flexibility when
 * distributing the code.
 */
struct Component::ComponentImpl
{
    std::vector<Component>::iterator findComponent(const std::string& name);
    std::vector<Component> mComponents;
};

std::vector<Component>::iterator Component::ComponentImpl::findComponent(const std::string& name)
{
    return std::find_if(mComponents.begin(), mComponents.end(),
                        [=](const Component& c) -> bool {return c.getName() == name;});
}

// Interface class Model implementation
Component::Component()
    : mPimpl(new ComponentImpl())
{
}

Component::~Component()
{
    delete mPimpl;
}

Component::Component(const Component& rhs)
    : ComponentEntity(rhs)
    , mPimpl(new ComponentImpl())
{
    mPimpl->mComponents = rhs.mPimpl->mComponents;
}

Component& Component::operator=(Component c)
{
    c.swap(*this);
    return *this;
}

void Component::swap(Component &rhs)
{
    std::swap(this->mName, rhs.mName);
    std::swap(this->mPimpl, rhs.mPimpl);
}

Component::Component(Component&& rhs)
    : ComponentEntity()
    , mPimpl(rhs.mPimpl)
{
    mName = std::move(rhs.mName);
    rhs.mPimpl = nullptr;
}

std::string Component::doSerialisation(libcellml::CELLML_FORMATS format) const
{
    const std::string encaps_tag = "<encapsulation>";
    const std::string encaps_end_tag = "</encapsulation>";
    std::string repr = "";
    if (format == CELLML_FORMAT_XML) {
        repr += "<component";
        std::string componentName = getName();
        if (componentName.length()) {
            repr += " name=\"" + componentName + "\"";
        }
        repr += "/>";
        std::string encaps = "";
        if (mPimpl->mComponents.size()) {
            encaps += "<encapsulation>";
            encaps += "<component_ref";
            if (componentName.length()) {
                encaps += " component=\"" + componentName + "\"";
            }
            encaps += ">";
        }
        for(std::vector<Component>::size_type i = 0; i != mPimpl->mComponents.size(); i++) {
            std::string comp = mPimpl->mComponents[i].serialise(format);
            std::size_t found = comp.find(encaps_tag);
            if (found == std::string::npos) {
                encaps += "<component_ref";
                if (mPimpl->mComponents[i].getName().length()) {
                    encaps += " component=\"" + mPimpl->mComponents[i].getName() + "\"";
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

        if(mPimpl->mComponents.size()) {
            encaps += "</component_ref></encapsulation>";
        }

        repr += encaps;

    }

    return repr;
}

void Component::addComponent(const Component &c)
{
    mPimpl->mComponents.push_back(c);
}

void Component::removeComponent(const std::string& name)
{
    auto result = mPimpl->findComponent(name);
    if(result != mPimpl->mComponents.end()) {
        mPimpl->mComponents.erase(result);
    } else {
        throw std::out_of_range("Named component not found.");
    }
}

void Component::removeComponent(size_t index)
{
    if (index < mPimpl->mComponents.size()) {
        mPimpl->mComponents.erase(mPimpl->mComponents.begin() + index);
    } else {
        throw std::out_of_range("Index out of range.");
    }
}

size_t Component::componentCount() const
{
    return mPimpl->mComponents.size();
}

bool Component::containsComponent(const std::string& name)
{
    auto result = mPimpl->findComponent(name);
    return result != mPimpl->mComponents.end();
}

Component& Component::getComponent(size_t index)
{
    return mPimpl->mComponents.at(index);
}

const Component& Component::getComponent(size_t index) const
{
    return mPimpl->mComponents.at(index);
}

Component Component::takeComponent(size_t index)
{
    Component c = mPimpl->mComponents.at(index);
    removeComponent(index);
    return c;
}

Component Component::takeComponent(const std::string & name)
{
    auto result = mPimpl->findComponent(name);
    size_t index = result - mPimpl->mComponents.begin();
    return takeComponent(index);
}

void Component::replaceComponent(size_t index, const Component& c)
{
    removeComponent(index);
    mPimpl->mComponents.insert(mPimpl->mComponents.begin() + index, c);
}

void Component::replaceComponent(const std::string& name, const Component& c)
{
    auto result = mPimpl->findComponent(name);
    size_t index = result - mPimpl->mComponents.begin();
    replaceComponent(index, c);
}

}

