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

#include <vector>

#include "libcellml/importedentity.h"
#include "libcellml/importsource.h"
#include "libcellml/model.h"
#include "libcellml/types.h"

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
    std::vector<ImportedEntityPtr> mImportedEntities;
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

bool ImportSource::addEntity(const ImportedEntityPtr &item)
{
    if (std::find(mPimpl->mImportedEntities.begin(), mPimpl->mImportedEntities.end(), item) == mPimpl->mImportedEntities.end()) {
        return false;
    }
    mPimpl->mImportedEntities.push_back(item);
    return true;
}

ImportedEntityPtr ImportSource::entity(size_t index) const
{
    if (index < mPimpl->mImportedEntities.size()) {
        return mPimpl->mImportedEntities.at(index);
    }
    return nullptr;
}

size_t ImportSource::entityCount() const
{
    return mPimpl->mImportedEntities.size();
}

bool ImportSource::removeEntity(size_t index)
{
    if (index < mPimpl->mImportedEntities.size()) {
        auto entity = mPimpl->mImportedEntities[index];
        mPimpl->mImportedEntities.erase(mPimpl->mImportedEntities.begin() + int64_t(index));
        return true;
    }

    return false;
}

} // namespace libcellml
