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

#include "libcellml/importsource.h"

#include <algorithm>
#include <vector>

#include "libcellml/component.h"
#include "libcellml/importedentity.h"
#include "libcellml/model.h"
#include "libcellml/types.h"
#include "libcellml/units.h"

#include "internaltypes.h"

namespace libcellml {

using ImportedEntityWeakPtr = std::weak_ptr<ImportedEntity>;

/**
 * @brief The ImportSource::ImportSourceImpl struct.
 *
 * The private implementation for the ImportSource class.
 */
struct ImportSource::ImportSourceImpl
{
    std::string mUrl;
    ModelWeakPtr mModel;
    std::vector<size_t> mComponents;
    std::vector<size_t> mUnits;
    std::vector<ImportedEntityWeakPtr> mImports;

    void removeItem(std::vector<ImportedEntityWeakPtr>::iterator &it);
};

ImportSource::ImportSource()
    : mPimpl(new ImportSourceImpl())
{
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
    if (mPimpl->mModel.expired()) {
        return nullptr;
    }
    return mPimpl->mModel.lock();
}

void ImportSource::setModel(const ModelPtr &model)
{
    if (model == nullptr) {
        mPimpl->mModel.reset();
    } else {
        mPimpl->mModel = model;
    }
}

bool ImportSource::hasModel() const
{
    return !mPimpl->mModel.expired();
}

ImportSourcePtr ImportSource::clone() const
{
    auto i = create();

    i->setId(id());
    i->setUrl(url());
    i->setModel(model());

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
        import = mPimpl->mImports.at(mPimpl->mComponents.at(index)).lock();
    }
    return std::dynamic_pointer_cast<Component>(import);
}

bool ImportSource::addComponent(const ComponentPtr &component)
{
    auto import = std::dynamic_pointer_cast<ImportedEntity>(component);

    const auto it = std::find_if(mPimpl->mImports.begin(), mPimpl->mImports.end(), [&import](const std::weak_ptr<ImportedEntity> &p) {
        return p.lock() == import;
    });

    if (it != mPimpl->mImports.end()) {
        return false;
    }

    size_t index = mPimpl->mImports.size();
    mPimpl->mImports.push_back(import);
    mPimpl->mComponents.push_back(index);
    return true;
}

bool ImportSource::removeComponent(ComponentPtr &component, bool setEmpty)
{
    if (component == nullptr) {
        return false;
    }

    auto import = std::dynamic_pointer_cast<ImportedEntity>(component);
    auto it = std::find_if(mPimpl->mImports.begin(), mPimpl->mImports.end(), [&import](std::weak_ptr<ImportedEntity> &p) {
        return p.lock() == import;
    });

    if (it == mPimpl->mImports.end()) {
        return false;
    }

    mPimpl->removeItem(it);

    if (setEmpty) {
        ImportSourcePtr empty = nullptr;
        component->setImportSource(empty);
    }

    return true;
}

bool ImportSource::removeComponent(size_t index, bool setEmpty)
{
    if (index >= mPimpl->mComponents.size()) {
        return false;
    }

    auto c = component(index);

    auto import = std::dynamic_pointer_cast<ImportedEntity>(c);
    auto it = std::find_if(mPimpl->mImports.begin(), mPimpl->mImports.end(), [&import](std::weak_ptr<ImportedEntity> &p) {
        return p.lock() == import;
    });

    mPimpl->removeItem(it);

    if (setEmpty) {
        ImportSourcePtr empty = nullptr;
        c->setImportSource(empty);
    }

    return true;
}

bool ImportSource::removeAllComponents()
{
    bool status = true;
    for (size_t c = mPimpl->mComponents.size() - 1; c <= 0; --c) {
        status = status && removeComponent(c);
    }
    return status;
}

size_t ImportSource::unitsCount() const
{
    return mPimpl->mUnits.size();
}

UnitsPtr ImportSource::units(size_t index) const
{
    ImportedEntityPtr import = nullptr;
    if (index < mPimpl->mUnits.size()) {
        import = mPimpl->mImports.at(mPimpl->mUnits.at(index)).lock();
    }
    return std::dynamic_pointer_cast<Units>(import);
}

bool ImportSource::addUnits(const UnitsPtr &units)
{
    auto import = std::dynamic_pointer_cast<ImportedEntity>(units);
    const auto it = std::find_if(mPimpl->mImports.begin(), mPimpl->mImports.end(), [&import](const std::weak_ptr<ImportedEntity> &p) {
        return p.lock() == import;
    });

    if (it != mPimpl->mImports.end()) {
        return false;
    }

    size_t index = mPimpl->mImports.size();
    mPimpl->mImports.push_back(import);
    mPimpl->mUnits.push_back(index);
    return true;
}

bool ImportSource::removeUnits(UnitsPtr &units, bool setEmpty)
{
    if (units == nullptr) {
        return false;
    }

    auto it = mPimpl->mImports.begin();
    for (auto i : mPimpl->mUnits) {
        auto test = std::dynamic_pointer_cast<Units>(mPimpl->mImports.at(i).lock());
        if ((test == units) || (test->name() == units->name())) {
            std::advance(it, int(i));
            break;
        }
    }

    if (it == mPimpl->mImports.end()) {
        return false;
    }

    mPimpl->removeItem(it);

    if (setEmpty) {
        ImportSourcePtr empty = nullptr;
        units->setImportSource(empty);
    }

    return true;
}

bool ImportSource::removeUnits(size_t index, bool setEmpty)
{
    if (index >= mPimpl->mUnits.size()) {
        return false;
    }

    auto u = mPimpl->mUnits[index];
    auto it = mPimpl->mImports.begin() + int(u);
    auto units = std::dynamic_pointer_cast<Units>((*it).lock());

    mPimpl->removeItem(it);

    if (setEmpty) {
        ImportSourcePtr empty = nullptr;
        units->setImportSource(empty);
    }

    return true;
}

bool ImportSource::removeAllUnits()
{
    bool status = true;
    for (size_t u = mPimpl->mUnits.size() - 1; u <= 0; --u) {
        status = status && removeUnits(u);
    }
    return status;
}

void ImportSource::ImportSourceImpl::removeItem(std::vector<ImportedEntityWeakPtr>::iterator &it)
{
    // Find current index for the item to remove.
    auto index = size_t(std::distance(mImports.begin(), it));
    auto itU = std::find(mUnits.begin(), mUnits.end(), index);
    if (itU != mUnits.end()) {
        mUnits.erase(itU);
    } else {
        auto itC = std::find(mComponents.begin(), mComponents.end(), index);
        if (itC != mComponents.end()) {
            mComponents.erase(itC);
        }
    }

    // Iterate through components index vector and decrement all indices above the item's index.
    static const size_t MAX_SIZE_T = std::numeric_limits<size_t>::max();
    for (size_t i = mComponents.size() - 1; (i != MAX_SIZE_T) && (mComponents[i] > index); --i) {
        --mComponents[i];
    }
    // Loop through units vector and decrease its indices too.
    for (size_t i = mUnits.size() - 1; (i != MAX_SIZE_T) && (mUnits[i] > index); --i) {
        --mUnits[i];
    }
    // Remove the item from the imports.
    mImports.erase(it);
}

} // namespace libcellml
