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

#include "libcellml/units.h"
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
    if (mPimpl) {
        for (std::vector<VariablePtr>::iterator iter = mPimpl->mVariables.begin(); iter != mPimpl->mVariables.end(); ++iter) {
            (*iter)->clearParent();
        }
    }
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

void Component::setSourceComponent(const ImportSourcePtr &importSource, const std::string &name)
{
    setImportSource(importSource);
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

bool Component::removeVariable(size_t index)
{
    bool status = false;
    if (index < mPimpl->mVariables.size()) {
        mPimpl->mVariables.erase(mPimpl->mVariables.begin() + index);
        status = true;
    }

    return status;
}

bool Component::removeVariable(const std::string &name)
{
    bool status = false;
    auto result = mPimpl->findVariable(name);
    if (result != mPimpl->mVariables.end()) {
        mPimpl->mVariables.erase(result);
        status = true;
    }

    return status;
}

bool Component::removeVariable(const VariablePtr &variable)
{
    bool status = false;
    auto result = mPimpl->findVariable(variable);
    if (result != mPimpl->mVariables.end()) {
        mPimpl->mVariables.erase(result);
        status = true;
    }

    return status;
}

void Component::removeAllVariables()
{
    mPimpl->mVariables.clear();
}

VariablePtr Component::getVariable(size_t index) const
{
    VariablePtr variable = nullptr;
    if (index < mPimpl->mVariables.size()) {
        variable = mPimpl->mVariables.at(index);
    }

    return variable;
}

VariablePtr Component::getVariable(const std::string &name) const
{
    VariablePtr variable = nullptr;
    auto result = mPimpl->findVariable(name);
    if (result != mPimpl->mVariables.end()) {
        variable = *result;
    }

    return variable;
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

}

