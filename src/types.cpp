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

/**
 * @brief The ImportRequirement::ImportRequirementImpl struct.
 *
 * The private implementation for the ImportRequirement class.
 */
struct ImportRequirement::ImportRequirementImpl
{
    ModelWeakPtr mModel; /**< Model used to resolve this requirement.*/
    std::string mUrl; /**< URL that the model was found at, relative to the importing model.*/
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

ImportRequirement::ImportRequirement(const std::string &url, const ModelPtr &model)
    : mPimpl(new ImportRequirementImpl())
{
    if (model == nullptr) {
        mPimpl->mModel.reset();
    } else {
        mPimpl->mModel = model;
    }
    mPimpl->mUrl = url;
}

ImportRequirement::~ImportRequirement()
{
    delete mPimpl;
}

// bool ImportRequirement::operator<(ImportRequirementPtr &ir)
// {
//     std::string left = mPimpl->mUrl;
//     std::string right = ir->url();
//     return (left < right);
// }

ImportRequirementPtr ImportRequirement::create(const std::string &url, const ModelPtr &model) noexcept
{
    return std::shared_ptr<ImportRequirement> {new ImportRequirement {url, model}};
}

ModelPtr ImportRequirement::model() const
{
    if (mPimpl->mModel.expired()) {
        return nullptr;
    }
    return mPimpl->mModel.lock();
}

std::string ImportRequirement::url() const
{
    return mPimpl->mUrl;
}

} // namespace libcellml
