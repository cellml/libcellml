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

#include "libcellml/when.h"

namespace libcellml {

/**
 * @brief The When::WhenImpl struct.
 *
 * The private implementation for the When class.
 */
struct When::WhenImpl
{
    std::string mCondition; /**< A string of math for determining the condition for transitioning from False to True.*/
    std::string mValue; /**< A string of math for assigning.*/
};

When::When()
    : mPimpl(new WhenImpl())
{
}

When::~When()
{
    delete mPimpl;
}

When::When(const When &rhs)
    : OrderedEntity(rhs)
    , mPimpl(new WhenImpl())
{
    mPimpl->mCondition = rhs.mPimpl->mCondition;
    mPimpl->mValue = rhs.mPimpl->mValue;
}

When::When(When &&rhs)
    : OrderedEntity(std::move(rhs))
    , mPimpl(rhs.mPimpl)
{
    rhs.mPimpl = nullptr;
}

When& When::operator=(When rhs)
{
    OrderedEntity::operator= (rhs);
    rhs.swap(*this);
    return *this;
}

void When::swap(When &rhs)
{
    std::swap(this->mPimpl, rhs.mPimpl);
}

void When::setCondition(const std::string &condition)
{
    mPimpl->mCondition = condition;
}

std::string When::getCondition() const
{
    return mPimpl->mCondition;
}

void When::setValue(const std::string &value)
{
    mPimpl->mValue = value;
}

std::string When::getValue() const
{
    return mPimpl->mValue;
}

}
