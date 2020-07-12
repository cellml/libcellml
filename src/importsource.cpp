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

#include <algorithm> // Adding because Ubuntu build complained?
#include <vector>

#include "libcellml/component.h"
#include "libcellml/importedentity.h"
#include "libcellml/importsource.h"
#include "libcellml/model.h"
#include "libcellml/types.h"
#include "libcellml/units.h"

namespace libcellml {

/**
 * @brief The ImportSource::ImportSourceImpl struct.
 *
 * The private implementation for the ImportSource class.
 */
struct ImportSource::ImportSourceImpl
{
    std::string mUrl;
    ModelPtr mModel;
    std::vector<ComponentPtr> mComponents;
    std::vector<UnitsPtr> mUnits;
};

ImportSource::ImportSource()
    : mPimpl(new ImportSourceImpl())
{
    mPimpl->mModel = nullptr;
}

ImportSource::~ImportSource()
{
    delete mPimpl;
}

ImportSourcePtr ImportSource::create() noexcept
{
    return std::shared_ptr<ImportSource> {new ImportSource {}};
}

std::string ImportSource::url() const
{
    return mPimpl->mUrl;
}

void ImportSource::setUrl(const std::string &url)
{
    mPimpl->mUrl = url;
}

ModelPtr ImportSource::model() const
{
    return mPimpl->mModel;
}

void ImportSource::setModel(const ModelPtr &model)
{
    mPimpl->mModel = model;
}

bool ImportSource::hasModel() const
{
    return mPimpl->mModel != nullptr;
}

ImportSourcePtr ImportSource::clone() const
{
    auto i = create();

    i->setId(id());
    i->setUrl(url());
    i->setModel(model());

    return i;
}

bool ImportSource::addComponent(const ComponentPtr &component)
{
    if (std::find(mPimpl->mComponents.begin(), mPimpl->mComponents.end(), component) != mPimpl->mComponents.end()) {
        return false;
    }
    mPimpl->mComponents.push_back(component);
    return true;
}

ComponentPtr ImportSource::component(size_t index) const
{
    if (index < mPimpl->mComponents.size()) {
        return mPimpl->mComponents.at(index);
    }
    return nullptr;
}

size_t ImportSource::componentCount() const
{
    return mPimpl->mComponents.size();
}

bool ImportSource::removeComponent(size_t index)
{
    // TODO Not sure whether it should be a two-way street between the ImportSource
    // and the thing added/removed.  Should removing a component from an import source
    // also remove the import source from the component? ditto imports?
    // ImportSourcePtr empty = nullptr;
    if (index < mPimpl->mComponents.size()) {
        auto component = mPimpl->mComponents[index];
        mPimpl->mComponents.erase(mPimpl->mComponents.begin() + int64_t(index));
        // component->setImportSource(empty);
        return true;
    }

    return false;
}

bool ImportSource::removeComponent(const ComponentPtr &component)
{
    // ImportSourcePtr empty = nullptr;
    auto result = std::find(mPimpl->mComponents.begin(), mPimpl->mComponents.end(), component);
    if (result != mPimpl->mComponents.end()) {
        mPimpl->mComponents.erase(result);
        // component->setImportSource(empty);
        return true;
    }

    return false;
}

bool ImportSource::addUnits(const UnitsPtr &units)
{
    if (std::find(mPimpl->mUnits.begin(), mPimpl->mUnits.end(), units) != mPimpl->mUnits.end()) {
        return false;
    }
    mPimpl->mUnits.push_back(units);
    return true;
}

UnitsPtr ImportSource::units(size_t index) const
{
    if (index < mPimpl->mUnits.size()) {
        return mPimpl->mUnits.at(index);
    }
    return nullptr;
}

size_t ImportSource::unitsCount() const
{
    return mPimpl->mUnits.size();
}

bool ImportSource::removeUnits(size_t index)
{
    if (index < mPimpl->mUnits.size()) {
        auto units = mPimpl->mUnits[index];
        mPimpl->mUnits.erase(mPimpl->mUnits.begin() + int64_t(index));
        return true;
    }

    return false;
}

bool ImportSource::removeUnits(const UnitsPtr &units)
{
    ImportSourcePtr empty = nullptr;
    auto result = std::find(mPimpl->mUnits.begin(), mPimpl->mUnits.end(), units);
    if (result != mPimpl->mUnits.end()) {
        mPimpl->mUnits.erase(result);
        units->setImportSource(empty);
        return true;
    }

    return false;
}

} // namespace libcellml
