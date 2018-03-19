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

#include "libcellml/model.h"

#include <algorithm>
#include <map>
#include <stack>
#include <utility>
#include <vector>

#include "libcellml/component.h"
#include "libcellml/importsource.h"
#include "libcellml/variable.h"
#include "libcellml/units.h"

namespace libcellml {

/**
 * @brief The Model::ModelImpl struct.
 *
 * This struct is the private implementation struct for the Model class.  Separating
 * the implementation from the definition allows for greater flexibility when
 * distributing the code.
 */
struct Model::ModelImpl
{
    std::vector<UnitsPtr>::iterator findUnits(const std::string &name);
    std::vector<UnitsPtr>::iterator findUnits(const UnitsPtr &units);
    std::vector<UnitsPtr> mUnits;
};

std::vector<UnitsPtr>::iterator Model::ModelImpl::findUnits(const std::string &name)
{
    return std::find_if(mUnits.begin(), mUnits.end(),
                        [=](const UnitsPtr& u) -> bool { return u->getName() == name; });
}

std::vector<UnitsPtr>::iterator Model::ModelImpl::findUnits(const UnitsPtr &units)
{
    return std::find_if(mUnits.begin(), mUnits.end(),
                        [=](const UnitsPtr& u) -> bool { return u == units; });
}

Model::Model()
    : mPimpl(new ModelImpl())
{
}

Model::~Model()
{
    delete mPimpl;
}

Model::Model(const Model& rhs)
    : ComponentEntity(rhs)
    , mPimpl(new ModelImpl())
{
    mPimpl->mUnits = rhs.mPimpl->mUnits;
}

Model::Model(Model &&rhs)
    : ComponentEntity(std::move(rhs))
    ,mPimpl(rhs.mPimpl)
{
    rhs.mPimpl = nullptr;
}

Model& Model::operator=(Model m)
{
    ComponentEntity::operator= (m);
    m.swap(*this);
    return *this;
}

void Model::swap(Model &rhs)
{
    std::swap(this->mPimpl, rhs.mPimpl);
}

void Model::doAddComponent(const ComponentPtr &c)
{
    // Check for cycles.
    if (!hasParent(c.get())) {
        c->setParent(this);
        ComponentEntity::doAddComponent(c);
    }
}

void Model::addUnits(const UnitsPtr & units)
{
    mPimpl->mUnits.push_back(units);
}

bool Model::removeUnits(size_t index)
{
    bool status = false;
    if (index < mPimpl->mUnits.size()) {
        mPimpl->mUnits.erase(mPimpl->mUnits.begin() + index);
        status = true;
    }

    return status;
}

bool Model::removeUnits(const std::string &name)
{
    bool status = false;
    auto result = mPimpl->findUnits(name);
    if (result != mPimpl->mUnits.end()) {
        mPimpl->mUnits.erase(result);
        status = true;
    }

    return status;
}

bool Model::removeUnits(const UnitsPtr &units)
{
    bool status = false;
    auto result = mPimpl->findUnits(units);
    if (result != mPimpl->mUnits.end()) {
        mPimpl->mUnits.erase(result);
        status = true;
    }

    return status;
}

void Model::removeAllUnits()
{
    mPimpl->mUnits.clear();
}

bool Model::hasUnits(const std::string &name) const
{
    return mPimpl->findUnits(name) != mPimpl->mUnits.end();
}

UnitsPtr Model::getUnits(size_t index) const
{
    UnitsPtr units = nullptr;
    if (index < mPimpl->mUnits.size()) {
        units = mPimpl->mUnits.at(index);
    }

    return units;
}

UnitsPtr Model::getUnits(const std::string &name) const
{
    UnitsPtr units = nullptr;
    auto result = mPimpl->findUnits(name);
    if (result != mPimpl->mUnits.end()) {
        units = *result;
    }

    return units;
}

UnitsPtr Model::takeUnits(size_t index)
{
    UnitsPtr units = nullptr;
    if (index < mPimpl->mUnits.size()) {
        units = mPimpl->mUnits.at(index);
        removeUnits(index);
        units->clearParent();
    }

    return units;
}

UnitsPtr Model::takeUnits(const std::string &name)
{
    return takeUnits(mPimpl->findUnits(name) - mPimpl->mUnits.begin());
}

bool Model::replaceUnits(size_t index, const UnitsPtr &units)
{
    bool status = false;
    if (removeUnits(index)) {
        mPimpl->mUnits.insert(mPimpl->mUnits.begin() + index, units);
        status = true;
    }

    return status;
}

bool Model::replaceUnits(const std::string &name, const UnitsPtr &units)
{
    return replaceUnits(mPimpl->findUnits(name) - mPimpl->mUnits.begin(), units);
}

bool Model::replaceUnits(const UnitsPtr &oldUnits, const UnitsPtr &newUnits)
{
    return replaceUnits(mPimpl->findUnits(oldUnits) - mPimpl->mUnits.begin(), newUnits);
}

size_t Model::unitsCount() const
{
    return mPimpl->mUnits.size();
}

}
