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

#include <algorithm>
#include <vector>

#include "libcellml/variable.h"

namespace libcellml {

/**
 * @brief The Component::ComponentImpl struct.
 * This struct is the private implementation struct for the Component class.  Separating
 * the implementation from the definition allows for greater flexibility when
 * distributing the code.
 */
struct Component::ComponentImpl
{
    std::vector<VariablePtr>::iterator findVariable(const std::string &name);
    std::vector<VariablePtr> mVariables;
};

std::vector<VariablePtr>::iterator Component::ComponentImpl::findVariable(const std::string &name)
{
    return std::find_if(mVariables.begin(), mVariables.end(),
                        [=](const VariablePtr& v) -> bool {return v->getName() == name;});
}

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
    mPimpl->mVariables = rhs.mPimpl->mVariables;
}

Component::Component(Component &&rhs)
    : ComponentEntity(std::move(rhs))
    , mPimpl(rhs.mPimpl)
{
    rhs.mPimpl = nullptr;
}

Component& Component::operator=(Component m)
{
    ComponentEntity::operator= (m);
    return *this;
}

void Component::doAddComponent(const ComponentPtr &c)
{
    if (!hasParent(c.get())) {
        c->setParent(this);
        ComponentEntity::doAddComponent(c);
    }
}

void Component::setSourceComponent(const ImportPtr &imp, const std::string &name)
{
    setImport(imp);
    setImportReference(name);
}

void Component::addVariable(const VariablePtr &v)
{
    mPimpl->mVariables.push_back(v);
}

void Component::removeVariable(const std::string &name)
{
    auto result = mPimpl->findVariable(name);
    if(result != mPimpl->mVariables.end()) {
        mPimpl->mVariables.erase(result);
    } else {
        throw std::out_of_range("Named variable not found.");
    }
}

VariablePtr Component::getVariable(size_t index)
{
    return mPimpl->mVariables.at(index);
}

const VariablePtr& Component::getVariable(size_t index) const
{
    return mPimpl->mVariables.at(index);
}

VariablePtr Component::getVariable(const std::string &name)
{
    auto result = mPimpl->findVariable(name);
    size_t index = result - mPimpl->mVariables.begin();
    return mPimpl->mVariables.at(index);
}

const VariablePtr& Component::getVariable(const std::string &name) const
{
    auto result = mPimpl->findVariable(name);
    size_t index = result - mPimpl->mVariables.begin();
    return mPimpl->mVariables.at(index);
}

size_t Component::variableCount() const
{
    return mPimpl->mVariables.size();
}

std::string Component::doSerialisation(FORMATS format) const
{
    std::string repr = "";
    if (format == FORMAT_XML) {
        if (isImport()) {
            return repr;
        }
        repr += "<component";
        bool endTag = false;
        std::string componentName = getName();
        if (componentName.length()) {
            repr += " name=\"" + componentName + "\"";
        }
        if (variableCount() > 0) {
            endTag = true;
            repr += ">";
            for(size_t i = 0; i < variableCount(); i++) {
                repr += getVariable(i)->serialise(format);
            }
        }
        if (endTag) {
            repr += "</component>";
        } else {
            repr += "/>";
        }
        repr += ComponentEntity::serialiseEncapsulation(format);
    }
    return repr;
}

}

