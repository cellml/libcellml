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
    std::vector<size_t> mComponents;
    std::vector<size_t> mUnits;
    std::vector<ImportedEntityPtr> mImports;

    bool removeItem(ImportedEntityPtr &item);
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
    // KRM Do *not* duplicate stored imports (mComponents, mUnits, mImports) here.

    return i;
}

size_t ImportSource::componentCount() const
{
    return mPimpl->mComponents.size();
}

ComponentPtr ImportSource::component(size_t index) const
{
    ImportedEntityPtr import = nullptr;
    if (index < mPimpl->mComponents.size()) {
        import = mPimpl->mImports.at(mPimpl->mComponents.at(index));
    }
    return std::dynamic_pointer_cast<Component>(import);
}

bool ImportSource::addComponent(const ComponentPtr &component)
{
    auto import = std::dynamic_pointer_cast<ImportedEntity>(component);
    if (std::find(mPimpl->mImports.begin(), mPimpl->mImports.end(), import) != mPimpl->mImports.end()) {
        return false;
    }

    size_t index = mPimpl->mImports.size();
    mPimpl->mImports.push_back(import);
    mPimpl->mComponents.push_back(index);
    return true;
}

bool ImportSource::removeComponent(ComponentPtr &component)
{
    if (component == nullptr) {
        return false;
    }

    ImportSourcePtr empty = nullptr;
    component->setImportSource(empty);
    auto import = std::dynamic_pointer_cast<ImportedEntity>(component);
    return mPimpl->removeItem(import);
}

bool ImportSource::removeComponent(size_t index)
{
    if (index >= mPimpl->mComponents.size()) {
        return false;
    }

    auto c = component(index);
    ImportSourcePtr empty = nullptr;
    c->setImportSource(empty);
    auto import = std::dynamic_pointer_cast<ImportedEntity>(c);
    return mPimpl->removeItem(import);
}

size_t ImportSource::unitsCount() const
{
    return mPimpl->mUnits.size();
}

UnitsPtr ImportSource::units(size_t index) const
{
    ImportedEntityPtr import = nullptr;
    if (index < mPimpl->mUnits.size()) {
        import = mPimpl->mImports.at(mPimpl->mUnits.at(index));
    }
    return std::dynamic_pointer_cast<Units>(import);
}

bool ImportSource::addUnits(const UnitsPtr &units)
{
    auto import = std::dynamic_pointer_cast<ImportedEntity>(units);
    if (std::find(mPimpl->mImports.begin(), mPimpl->mImports.end(), import) != mPimpl->mImports.end()) {
        return false;
    }
    size_t index = mPimpl->mImports.size();
    mPimpl->mImports.push_back(import);
    mPimpl->mUnits.push_back(index);
    return true;
}

bool ImportSource::removeUnits(UnitsPtr &units)
{
    if (units == nullptr) {
        return false;
    }

    ImportSourcePtr empty = nullptr;
    units->setImportSource(empty);
    auto import = std::dynamic_pointer_cast<ImportedEntity>(units);
    return mPimpl->removeItem(import);
}

bool ImportSource::removeUnits(size_t index)
{
    if (index >= mPimpl->mUnits.size()) {
        return false;
    }

    auto u = units(index);
    ImportSourcePtr empty = nullptr;
    u->setImportSource(empty);
    auto import = std::dynamic_pointer_cast<ImportedEntity>(u);
    return mPimpl->removeItem(import);
}

bool ImportSource::ImportSourceImpl::removeItem(ImportedEntityPtr &item)
{
    auto it = std::find(mImports.begin(), mImports.end(), item);
    if (it == mImports.end()) {
        return false;
    }

    // Find current index for the item to remove.
    auto index = int(std::distance(mImports.begin(), it));
    auto itU = std::find(mUnits.begin(), mUnits.end(), index);
    if (itU != mUnits.end()) {
        mUnits.erase(itU);
    } else {
        auto itC = std::find(mComponents.begin(), mComponents.end(), index);
        if (itC != mComponents.end()) {
            mComponents.erase(itC);
        }
    }

    // Iterate through components index vector and decrement all indices above the importIndex.
    auto i = int(mComponents.size() - 1);
    while ((i >= 0) && (int(mComponents[size_t(i)]) > index)) {
        mComponents[size_t(i)]--;
        i--;
    }
    // Loop through units vector and decrease its indices too.
    i = int(mUnits.size() - 1);
    while ((i >= 0) && (int(mUnits[size_t(i)]) > index)) {
        mUnits[size_t(i)]--;
        i--;
    }
    // Remove the item from the imports.
    mImports.erase(it);

    return true;
}

} // namespace libcellml
