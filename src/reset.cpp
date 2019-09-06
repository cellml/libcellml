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

#include <algorithm>
#include <iostream>
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
    VariablePtr mTestVariable; /**< The associated test_variable for the reset.*/
    std::string mTestValue = ""; /**< The mathml string for the test_value.*/
    std::string mTestValueId = ""; /**< The id of the test_value block */
    std::string mResetValue = ""; /**< The mathml string for the reset_value.*/
    std::string mResetValueId = ""; /**< The id of the reset_value block */
};

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
    mPimpl->mTestVariable = rhs.mPimpl->mTestVariable;
    mPimpl->mTestValue = rhs.mPimpl->mTestValue;
    mPimpl->mResetValue = rhs.mPimpl->mResetValue;
    mPimpl->mTestValueId = rhs.mPimpl->mTestValueId;
    mPimpl->mResetValueId = rhs.mPimpl->mResetValueId;
}

Reset::Reset(Reset &&rhs) noexcept
    : OrderedEntity(std::move(rhs))
    , mPimpl(rhs.mPimpl)
{
    rhs.mPimpl = nullptr;
}

Reset &Reset::operator=(Reset rhs)
{
    OrderedEntity::operator=(rhs);
    rhs.swap(*this);
    return *this;
}

void Reset::swap(Reset &rhs)
{
    std::swap(this->mPimpl, rhs.mPimpl);
}

void Reset::setVariable(const VariablePtr &variable)
{
    mPimpl->mVariable = variable;
}

VariablePtr Reset::variable() const
{
    return mPimpl->mVariable;
}

void Reset::setTestVariable(const VariablePtr &variable)
{
    mPimpl->mTestVariable = variable;
}

VariablePtr Reset::testVariable() const
{
    return mPimpl->mTestVariable;
}

void Reset::appendTestValue(const std::string &math)
{
    mPimpl->mTestValue.append(math);
}

std::string Reset::testValue() const
{
    return mPimpl->mTestValue;
}

void Reset::setTestValueId(const std::string &id)
{
    mPimpl->mTestValueId = id;
}

std::string Reset::testValueId() const
{
    return mPimpl->mTestValueId;
}

void Reset::setTestValue(const std::string &math)
{
    mPimpl->mTestValue = math;
}

void Reset::appendResetValue(const std::string &math)
{
    mPimpl->mResetValue.append(math);
}

std::string Reset::resetValue() const
{
    return mPimpl->mResetValue;
}

void Reset::setResetValue(const std::string &math)
{
    mPimpl->mResetValue = math;
}

void Reset::setResetValueId(const std::string &id)
{
    mPimpl->mResetValueId = id;
}

std::string Reset::resetValueId() const
{
    return mPimpl->mResetValueId;
}

} // namespace libcellml
