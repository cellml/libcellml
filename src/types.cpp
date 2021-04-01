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

#include "libcellml/component.h"
#include "libcellml/importsource.h"
#include "libcellml/model.h"
#include "libcellml/reset.h"
#include "libcellml/units.h"
#include "libcellml/variable.h"

#include "anycellmlelement_p.h"
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

AnyCellmlElement::AnyCellmlElement()
    : mPimpl(new AnyCellmlElementImpl())
{
}

AnyCellmlElement::AnyCellmlElement(CellmlElementType type, const std::any &item)
    : mPimpl(new AnyCellmlElementImpl())
{
    mPimpl->mItem = item;
    mPimpl->mType = type;
}

AnyCellmlElement::AnyCellmlElement(CellmlElementType type, const ComponentPtr &item)
    : mPimpl(new AnyCellmlElementImpl())
{
    mPimpl->mItem = std::any(item);
    mPimpl->mType = type;
}

AnyCellmlElement::AnyCellmlElement(CellmlElementType type, const ImportSourcePtr &item)
    : mPimpl(new AnyCellmlElementImpl())
{
    mPimpl->mItem = std::any(item);
    mPimpl->mType = type;
}

AnyCellmlElement::AnyCellmlElement(CellmlElementType type, const ModelPtr &item)
    : mPimpl(new AnyCellmlElementImpl())
{
    mPimpl->mItem = std::any(item);
    mPimpl->mType = type;
}

AnyCellmlElement::AnyCellmlElement(CellmlElementType type, const ResetPtr &item)
    : mPimpl(new AnyCellmlElementImpl())
{
    mPimpl->mItem = std::any(item);
    mPimpl->mType = type;
}

AnyCellmlElement::AnyCellmlElement(CellmlElementType type, const UnitPtr &item)
    : mPimpl(new AnyCellmlElementImpl())
{
    mPimpl->mItem = std::any(item);
    mPimpl->mType = type;
}

AnyCellmlElement::AnyCellmlElement(CellmlElementType type, const UnitsPtr &item)
    : mPimpl(new AnyCellmlElementImpl())
{
    mPimpl->mItem = std::any(item);
    mPimpl->mType = type;
}

AnyCellmlElement::AnyCellmlElement(CellmlElementType type, const VariablePairPtr &item)
    : mPimpl(new AnyCellmlElementImpl())
{
    mPimpl->mItem = std::any(item);
    mPimpl->mType = type;
}

AnyCellmlElement::AnyCellmlElement(CellmlElementType type, const VariablePtr &item)
    : mPimpl(new AnyCellmlElementImpl())
{
    mPimpl->mItem = std::any(item);
    mPimpl->mType = type;
}

AnyCellmlElement::~AnyCellmlElement()
{
    delete mPimpl;
}

AnyCellmlElementPtr AnyCellmlElement::create() noexcept
{
    return std::shared_ptr<AnyCellmlElement> {new AnyCellmlElement {}};
}

AnyCellmlElementPtr AnyCellmlElement::create(CellmlElementType type, const std::any &item) noexcept
{
    return std::shared_ptr<AnyCellmlElement> {new AnyCellmlElement {type, item}};
}

AnyCellmlElementPtr AnyCellmlElement::create(CellmlElementType type, const ComponentPtr &item) noexcept
{
    return std::shared_ptr<AnyCellmlElement> {new AnyCellmlElement {type, item}};
}

AnyCellmlElementPtr AnyCellmlElement::create(CellmlElementType type, const ImportSourcePtr &item) noexcept
{
    return std::shared_ptr<AnyCellmlElement> {new AnyCellmlElement {type, item}};
}

AnyCellmlElementPtr AnyCellmlElement::create(CellmlElementType type, const VariablePtr &item) noexcept
{
    return std::shared_ptr<AnyCellmlElement> {new AnyCellmlElement {type, item}};
}

AnyCellmlElementPtr AnyCellmlElement::create(CellmlElementType type, const VariablePairPtr &item) noexcept
{
    return std::shared_ptr<AnyCellmlElement> {new AnyCellmlElement {type, item}};
}

AnyCellmlElementPtr AnyCellmlElement::create(CellmlElementType type, const ModelPtr &item) noexcept
{
    return std::shared_ptr<AnyCellmlElement> {new AnyCellmlElement {type, item}};
}

AnyCellmlElementPtr AnyCellmlElement::create(CellmlElementType type, const UnitsPtr &item) noexcept
{
    return std::shared_ptr<AnyCellmlElement> {new AnyCellmlElement {type, item}};
}

AnyCellmlElementPtr AnyCellmlElement::create(CellmlElementType type, const UnitPtr &item) noexcept
{
    return std::shared_ptr<AnyCellmlElement> {new AnyCellmlElement {type, item}};
}
AnyCellmlElementPtr AnyCellmlElement::create(CellmlElementType type, const ResetPtr &item) noexcept
{
    return std::shared_ptr<AnyCellmlElement> {new AnyCellmlElement {type, item}};
}

std::any AnyCellmlElement::item() const
{
    return mPimpl->mItem;
}

CellmlElementType AnyCellmlElement::type() const
{
    return mPimpl->mType;
}

} // namespace libcellml
