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
 * @brief The Unit::UnitImpl struct.
 *
 * The private implementation for the Unit class.
 */
struct Unit::UnitImpl
{
    UnitsWeakPtr mUnits; /**< Units that owns this unit.*/
    size_t mIndex = std::numeric_limits<size_t>::max(); /**< Index of this unit.*/
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

Unit::Unit(const UnitsPtr &units, size_t index)
    : mPimpl(new UnitImpl())
{
    mPimpl->mUnits = units;
    mPimpl->mIndex = index;
}

Unit::~Unit()
{
    delete mPimpl;
}

UnitPtr Unit::create(const UnitsPtr &units, size_t index) noexcept
{
    return std::shared_ptr<Unit> {new Unit {units, index}};
}

UnitsPtr Unit::units() const
{
    return mPimpl->mUnits.lock();
}

size_t Unit::index() const
{
    return mPimpl->mIndex;
}

bool Unit::isValid() const
{
    auto units = mPimpl->mUnits.lock();
    if (units != nullptr) {
        return mPimpl->mIndex < units->unitCount();
    }

    return false;
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
    return (mPimpl->mVariable1.lock() != nullptr) && (mPimpl->mVariable2.lock() != nullptr);
}

/**
 * @brief The AnyItemNew::AnyItemNewImpl struct.
 *
 * The private implementation for the AnyItemNew class.
 */
struct AnyItemNew::AnyItemNewImpl
{
    std::any mItem = nullptr; /**< std::any item cast for the item.*/
    CellmlElementType mType = CellmlElementType::UNDEFINED; /**< Type for the item.*/
};

AnyItemNew::AnyItemNew()
    : mPimpl(new AnyItemNewImpl())
{
}

AnyItemNew::AnyItemNew(const std::any &item, CellmlElementType type)
    : mPimpl(new AnyItemNewImpl())
{
    mPimpl->mItem = item;
    mPimpl->mType = type;
}

AnyItemNew::~AnyItemNew()
{
    delete mPimpl;
}

AnyItemNewPtr AnyItemNew::create() noexcept
{
    return std::shared_ptr<AnyItemNew> {new AnyItemNew {}};
}

AnyItemNewPtr AnyItemNew::create(const std::any &item, CellmlElementType type) noexcept
{
    return std::shared_ptr<AnyItemNew> {new AnyItemNew {item, type}};
}

std::any AnyItemNew::item() const
{
    return mPimpl->mItem;
}

CellmlElementType AnyItemNew::type() const
{
    return mPimpl->mType;
}

} // namespace libcellml
