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
limitations under the License.
*/

#include "libcellml/component.h"

#include <algorithm>
#include <string>
#include <vector>

#include "libcellml/variable.h"

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
    std::vector<VariablePtr>::iterator findVariable(const std::string &name);
    std::vector<VariablePtr>::iterator findVariable(const VariablePtr &variable);
    std::vector<VariablePtr> mVariables;
};

std::vector<VariablePtr>::iterator Component::ComponentImpl::findVariable(const std::string &name)
{
    return std::find_if(mVariables.begin(), mVariables.end(),
                        [=](const VariablePtr& v) -> bool { return v->getName() == name; });
}

std::vector<VariablePtr>::iterator Component::ComponentImpl::findVariable(const VariablePtr &variable)
{
    return std::find_if(mVariables.begin(), mVariables.end(),
                        [=](const VariablePtr& v) -> bool { return v == variable; });
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
    mPimpl->mMath = rhs.mPimpl->mMath;
}

Component::Component(Component &&rhs)
    : ComponentEntity(std::move(rhs))
    , mPimpl(rhs.mPimpl)
{
    rhs.mPimpl = nullptr;
}

Component& Component::operator=(Component c)
{
    ComponentEntity::operator= (c);
    c.swap(*this);
    return *this;
}

void Component::swap(Component &rhs)
{
    std::swap(this->mPimpl, rhs.mPimpl);
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

void Component::appendMath(const std::string &math) {
    mPimpl->mMath.append(math);
}

std::string Component::getMath() const{
    return mPimpl->mMath;
}

void Component::setMath(const std::string &math) {
    mPimpl->mMath = math;
}

void Component::addVariable(const VariablePtr &v)
{
    mPimpl->mVariables.push_back(v);
    v->setParent(this);
}

void Component::removeVariable(const std::string &name)
{
    auto result = mPimpl->findVariable(name);
    if (result != mPimpl->mVariables.end()) {
        mPimpl->mVariables.erase(result);
    } else {
        throw std::out_of_range("Named variable not found.");
    }
}

void Component::removeVariable(const VariablePtr &variable)
{
    auto result = mPimpl->findVariable(variable);
    if (result != mPimpl->mVariables.end()) {
        mPimpl->mVariables.erase(result);
    } else {
        throw std::out_of_range("Variable pointer not found.");
    }
}

void Component::removeAllVariables()
{
    mPimpl->mVariables.clear();
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

bool Component::hasVariable(const VariablePtr &variable)
{
    return mPimpl->findVariable(variable) != mPimpl->mVariables.end();
}

std::string Component::doSerialisation(Format format) const
{
    std::string repr = "";
    if (format == Format::XML) {
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
            for (size_t i = 0; i < variableCount(); ++i) {
                repr += getVariable(i)->serialise(format);
            }
        }
        if (getMath().length()) {
            if (!endTag) {
                endTag = true;
                repr += ">";
            }
            repr += getMath();
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

