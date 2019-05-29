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

#include "libcellml/reset.h"
#include "libcellml/when.h"

#include <algorithm>
#include <vector>

namespace libcellml {

/**
 * @brief The Reset::ResetImpl struct.
 *
 * The private implementation for the Reset class.
 */
struct Reset::ResetImpl
{
    int mOrder = 0; /**< An integer for determining relative order.*/
    VariablePtr mVariable; /**< The associated variable for the reset.*/
    std::vector<WhenPtr>::iterator findWhen(const WhenPtr &when);
    std::vector<WhenPtr> mWhens;
};

std::vector<WhenPtr>::iterator Reset::ResetImpl::findWhen(const WhenPtr &when)
{
    return std::find_if(mWhens.begin(), mWhens.end(),
                        [=](const WhenPtr &w) -> bool { return w == when; });
}

Reset::Reset()
    : mPimpl(new ResetImpl())
{
}

Reset::~Reset()
{
    delete mPimpl;
}

Reset::Reset(const Reset &rhs)
    : OrderedEntity(rhs)
    , mPimpl(new ResetImpl())
{
    mPimpl->mOrder = rhs.mPimpl->mOrder;
    mPimpl->mVariable = rhs.mPimpl->mVariable;
    mPimpl->mWhens = rhs.mPimpl->mWhens;
}

Reset::Reset(Reset &&rhs)
    : OrderedEntity(std::move(rhs))
    , mPimpl(rhs.mPimpl)
{
    rhs.mPimpl = nullptr;
}

Reset &Reset::operator=(Reset e)
{
    OrderedEntity::operator=(e);
    e.swap(*this);
    return *this;
}

void Reset::swap(Reset &rhs)
{
    std::swap(mPimpl, rhs.mPimpl);
}

void Reset::setVariable(VariablePtr variable)
{
    mPimpl->mVariable = variable;
}

VariablePtr Reset::getVariable() const
{
    return mPimpl->mVariable;
}

void Reset::addWhen(const WhenPtr &when)
{
    mPimpl->mWhens.push_back(when);
}

bool Reset::removeWhen(size_t index)
{
    bool status = false;

    if (index < mPimpl->mWhens.size()) {
        mPimpl->mWhens.erase(mPimpl->mWhens.begin() + index);
        status = true;
    }

    return status;
}

bool Reset::removeWhen(const WhenPtr &when)
{
    bool status = false;
    auto result = mPimpl->findWhen(when);
    if (result != mPimpl->mWhens.end()) {
        mPimpl->mWhens.erase(result);
        status = true;
    }

    return status;
}

void Reset::removeAllWhens()
{
    mPimpl->mWhens.clear();
}

bool Reset::containsWhen(const WhenPtr &when) const
{
    bool status = false;
    auto result = mPimpl->findWhen(when);
    if (result != mPimpl->mWhens.end()) {
        status = true;
    }

    return status;
}

WhenPtr Reset::getWhen(size_t index) const
{
    WhenPtr when = nullptr;
    if (index < mPimpl->mWhens.size()) {
        when = mPimpl->mWhens.at(index);
    }

    return when;
}

WhenPtr Reset::takeWhen(size_t index)
{
    WhenPtr when = nullptr;
    if (index < mPimpl->mWhens.size()) {
        when = mPimpl->mWhens.at(index);
        mPimpl->mWhens.erase(mPimpl->mWhens.begin() + index);
    }

    return when;
}

bool Reset::replaceWhen(size_t index, const WhenPtr &when)
{
    bool status = false;
    if (removeWhen(index)) {
        mPimpl->mWhens.insert(mPimpl->mWhens.begin() + index, when);
        status = true;
    }

    return status;
}

size_t Reset::whenCount() const
{
    return mPimpl->mWhens.size();
}

} // namespace libcellml
