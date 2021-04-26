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
    return mPimpl->mIndex < mPimpl->mUnits.lock()->unitCount();
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

void AnyCellmlElement::AnyCellmlElementImpl::setComponent(const ComponentPtr &component, CellmlElementType type)
{
    mType = type;
    mItem = component;
}

void AnyCellmlElement::AnyCellmlElementImpl::setComponentRef(const ComponentPtr &component)
{
    mType = CellmlElementType::COMPONENT_REF;
    mItem = component;
}

void AnyCellmlElement::AnyCellmlElementImpl::setEncapsulation(const ModelPtr &model)
{
    mType = CellmlElementType::ENCAPSULATION;
    mItem = model;
}

void AnyCellmlElement::AnyCellmlElementImpl::setImportSource(const ImportSourcePtr &importSource)
{
    mType = CellmlElementType::IMPORT;
    mItem = importSource;
}

void AnyCellmlElement::AnyCellmlElementImpl::setMath(const ComponentPtr &component)
{
    mType = CellmlElementType::MATH;
    mItem = component;
}

void AnyCellmlElement::AnyCellmlElementImpl::setModel(const ModelPtr &model, CellmlElementType type)
{
    mType = type;
    mItem = model;
}

void AnyCellmlElement::AnyCellmlElementImpl::setReset(const ResetPtr &reset, CellmlElementType type)
{
    mType = type;
    mItem = reset;
}

void AnyCellmlElement::AnyCellmlElementImpl::setResetValue(const ResetPtr &reset)
{
    mType = CellmlElementType::RESET_VALUE;
    mItem = reset;
}

void AnyCellmlElement::AnyCellmlElementImpl::setTestValue(const ResetPtr &reset)
{
    mType = CellmlElementType::TEST_VALUE;
    mItem = reset;
}

void AnyCellmlElement::AnyCellmlElementImpl::setUnit(const UnitPtr &unit)
{
    mType = CellmlElementType::UNIT;
    mItem = unit;
}

void AnyCellmlElement::AnyCellmlElementImpl::setUnits(const UnitsPtr &units)
{
    mType = CellmlElementType::UNITS;
    mItem = units;
}

void AnyCellmlElement::AnyCellmlElementImpl::setVariable(const VariablePtr &variable)
{
    mType = CellmlElementType::VARIABLE;
    mItem = variable;
}

void AnyCellmlElement::AnyCellmlElementImpl::setVariablePair(const VariablePairPtr &pair, CellmlElementType type)
{
    mType = type;
    mItem = pair;
}

void AnyCellmlElement::AnyCellmlElementImpl::setVariablePair(const VariablePtr &variable1, const VariablePtr &variable2, CellmlElementType type)
{
    mType = type;
    mItem = VariablePair::create(variable1, variable2);
}

AnyCellmlElement::AnyCellmlElement()
    : mPimpl(new AnyCellmlElementImpl())
{
}

AnyCellmlElement::~AnyCellmlElement()
{
    delete mPimpl;
}

CellmlElementType AnyCellmlElement::type() const
{
    return mPimpl->mType;
}

ComponentPtr AnyCellmlElement::component() const
{
    if ((mPimpl->mType == CellmlElementType::COMPONENT) ||
        (mPimpl->mType == CellmlElementType::COMPONENT_REF)) {
        return std::any_cast<ComponentPtr>(mPimpl->mItem);
    }

    return nullptr;
}

VariablePairPtr AnyCellmlElement::variablePair() const
{
    if ((mPimpl->mType == CellmlElementType::CONNECTION) ||
        (mPimpl->mType == CellmlElementType::MAP_VARIABLES)) {
        return std::any_cast<VariablePairPtr>(mPimpl->mItem);
    }

    return nullptr;
}

ImportSourcePtr AnyCellmlElement::importSource() const
{
    if (mPimpl->mType == CellmlElementType::IMPORT) {
        return std::any_cast<ImportSourcePtr>(mPimpl->mItem);
    }

    return nullptr;
}

ModelPtr AnyCellmlElement::model() const
{
    if ((mPimpl->mType == CellmlElementType::MODEL) ||
        (mPimpl->mType == CellmlElementType::ENCAPSULATION)) {
        return std::any_cast<ModelPtr>(mPimpl->mItem);
    }

    return nullptr;
}

ResetPtr AnyCellmlElement::reset() const
{
    if (mPimpl->mType == CellmlElementType::RESET) {
        return std::any_cast<ResetPtr>(mPimpl->mItem);
    }

    return nullptr;
}

ResetPtr AnyCellmlElement::resetValue() const
{
    if (mPimpl->mType == CellmlElementType::RESET_VALUE) {
        return std::any_cast<ResetPtr>(mPimpl->mItem);
    }

    return nullptr;
}

ResetPtr AnyCellmlElement::testValue() const
{
    if (mPimpl->mType == CellmlElementType::TEST_VALUE) {
        return std::any_cast<ResetPtr>(mPimpl->mItem);
    }

    return nullptr;
}

UnitPtr AnyCellmlElement::unit() const
{
    if (mPimpl->mType == CellmlElementType::UNIT) {
        return std::any_cast<UnitPtr>(mPimpl->mItem);
    }

    return nullptr;
}

UnitsPtr AnyCellmlElement::units() const
{
    if (mPimpl->mType == CellmlElementType::UNITS) {
        return std::any_cast<UnitsPtr>(mPimpl->mItem);
    }

    return nullptr;
}

VariablePtr AnyCellmlElement::variable() const
{
    if (mPimpl->mType == CellmlElementType::VARIABLE) {
        return std::any_cast<VariablePtr>(mPimpl->mItem);
    }

    return nullptr;
}

} // namespace libcellml
