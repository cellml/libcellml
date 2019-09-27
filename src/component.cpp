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

#include "libcellml/units.h"
#include "libcellml/variable.h"

#include <algorithm>
#include <string>
#include <vector>

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

Component::~Component()
{
    if (mPimpl != nullptr) {
        for (const auto &variable : mPimpl->mVariables) {
            variable->clearParent();
        }
    }
    delete mPimpl;
}

Component::Component(const Component &rhs)
    : ComponentEntity(rhs)
    , ImportedEntity(rhs)
#ifndef SWIG
    , std::enable_shared_from_this<Component>(rhs)
#endif
    , mPimpl(new ComponentImpl())
{
    mPimpl->mVariables = rhs.mPimpl->mVariables;
    mPimpl->mResets = rhs.mPimpl->mResets;
    mPimpl->mMath = rhs.mPimpl->mMath;
}

Component::Component(Component &&rhs) noexcept
    : ComponentEntity(std::move(rhs))
    , ImportedEntity(std::move(rhs))
    , mPimpl(rhs.mPimpl)
{
    rhs.mPimpl = nullptr;
}

Component &Component::operator=(Component rhs)
{
    ComponentEntity::operator=(rhs);
    ImportedEntity::operator=(rhs);
    rhs.swap(*this);
    return *this;
}

void Component::swap(Component &rhs)
{
    std::swap(mPimpl, rhs.mPimpl);
}

void Component::doAddComponent(const ComponentPtr &component)
{
    if (!hasAncestor(component)) {
        component->setParent(shared_from_this());
        ComponentEntity::doAddComponent(component);
    }
}

void Component::setSourceComponent(const ImportSourcePtr &importSource, const std::string &name)
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

void Component::addVariable(const VariablePtr &variable)
{
    mPimpl->mVariables.push_back(variable);
    variable->setParent(shared_from_this());
}

bool Component::removeVariable(size_t index)
{
    if (index < mPimpl->mVariables.size()) {
        mPimpl->mVariables.erase(mPimpl->mVariables.begin() + int64_t(index));
        return true;
    }

    return false;
}

bool Component::removeVariable(const std::string &name)
{
    auto result = mPimpl->findVariable(name);
    if (result != mPimpl->mVariables.end()) {
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
        return true;
    }

    return false;
}

void Component::removeAllVariables()
{
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
    VariablePtr res = nullptr;
    res = variable(index);
    removeVariable(index);

    return res;
}

VariablePtr Component::takeVariable(const std::string &name)
{
    VariablePtr res = nullptr;
    res = variable(name);
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

void Component::addReset(const ResetPtr &reset)
{
    mPimpl->mResets.push_back(reset);
}

bool Component::removeReset(size_t index)
{
    if (index < mPimpl->mResets.size()) {
        mPimpl->mResets.erase(mPimpl->mResets.begin() + int64_t(index));
        return true;
    }

    return false;
}

bool Component::removeReset(const ResetPtr &reset)
{
    auto result = mPimpl->findReset(reset);
    if (result != mPimpl->mResets.end()) {
        mPimpl->mResets.erase(result);
        return true;
    }

    return false;
}

void Component::removeAllResets()
{
    mPimpl->mResets.clear();
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

} // namespace libcellml
