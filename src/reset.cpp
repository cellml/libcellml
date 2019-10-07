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
    VariablePtr mTestVariable; /**< The associated test_variable for the reset.*/
    std::string mTestValue = ""; /**< The mathml string for the test_value.*/
    std::string mTestValueId = ""; /**< The id of the test_value block */
    std::string mResetValue = ""; /**< The mathml string for the reset_value.*/
    std::string mResetValueId = ""; /**< The id of the reset_value block */
};

// std::vector<WhenPtr>::iterator Reset::ResetImpl::findWhen(const WhenPtr &when)
// {
//     return std::find_if(mWhens.begin(), mWhens.end(),
//                         [=](const WhenPtr &w) -> bool { return w == when; });
// }

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
    mPimpl->mTestVariable = rhs.mPimpl->mTestVariable; /**< The associated test_variable for the reset.*/
    mPimpl->mTestValue = rhs.mPimpl->mTestValue; /**< The mathml string for the test_value.*/
    mPimpl->mTestValueId = rhs.mPimpl->mTestValueId; /**< The id of the test_value block */
    mPimpl->mResetValue = rhs.mPimpl->mResetValue; /**< The mathml string for the reset_value.*/
    mPimpl->mResetValueId = rhs.mPimpl->mResetValueId; /**< The id of the reset_value block */
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
    std::swap(mPimpl, rhs.mPimpl);
}

void Reset::setVariable(const VariablePtr &variable)
{
    mPimpl->mVariable = variable;
}

VariablePtr Reset::variable() const
{
    return mPimpl->mVariable;
}

void Reset::setTestVariable(const VariablePtr &testVariable)
{
    mPimpl->mTestVariable = testVariable;
}

VariablePtr Reset::testVariable() const
{
    return mPimpl->mTestVariable;
}

} // namespace libcellml
