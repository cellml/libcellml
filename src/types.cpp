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

#include "libcellml/types.h"

#include "libcellml/units.h"

#include "internaltypes.h"

namespace libcellml {

/**
 * @brief The UnitReference::UnitReferenceImpl struct.
 *
 * The private implementation for the UnitReference class.
 */
struct UnitReference::UnitReferenceImpl
{
    UnitsWeakPtr mUnits; /**< Variable 1 for the pair.*/
    size_t mIndex = 0; /**< Variable 2 for the pair.*/
};

/**
 * @brief The VariablePair::VariablePairImpl struct.
 *
 * The private implementation for the VariablePair class.
 */
struct VariablePair::VariablePairImpl
{
    VariableWeakPtr mVariable1; /**< Variable 1 for the pair.*/
    VariableWeakPtr mVariable2; /**< Variable 2 for the pair.*/
};

UnitReference::UnitReference()
    : mPimpl(new UnitReferenceImpl())
{
}

UnitReference::UnitReference(const UnitsPtr &units, size_t index)
    : mPimpl(new UnitReferenceImpl())
{
    mPimpl->mUnits = units;
    mPimpl->mIndex = index;
}

UnitReference::~UnitReference()
{
    delete mPimpl;
}

UnitReferencePtr UnitReference::create(const UnitsPtr &units, size_t index) noexcept
{
    return std::shared_ptr<UnitReference> {new UnitReference {units, index}};
}

UnitsPtr UnitReference::units() const
{
    return mPimpl->mUnits.lock();
}

size_t UnitReference::index() const
{
    return mPimpl->mIndex;
}

bool UnitReference::isValid() const
{
    auto units = mPimpl->mUnits.lock();
    if (units) {
        return mPimpl->mIndex < units->unitCount();
    }

    return false;
}

VariablePair::VariablePair()
    : mPimpl(new VariablePairImpl())
{
}

VariablePair::VariablePair(const VariablePtr &variable1, const VariablePtr &variable2)
    : mPimpl(new VariablePairImpl())
{
    mPimpl->mVariable1 = variable1;
    mPimpl->mVariable2 = variable2;
}

VariablePairPtr VariablePair::create(const VariablePtr &variable1, const VariablePtr &variable2) noexcept
{
    return std::shared_ptr<VariablePair> {new VariablePair {variable1, variable2}};
}

VariablePair::~VariablePair()
{
    delete mPimpl;
}

VariablePtr VariablePair::variable1() const
{
    return mPimpl->mVariable1.lock();
}

VariablePtr VariablePair::variable2() const
{
    return mPimpl->mVariable2.lock();
}

bool VariablePair::isValid() const
{
    return mPimpl->mVariable1.lock() != nullptr && mPimpl->mVariable2.lock() != nullptr;
}

} // namespace libcellml
