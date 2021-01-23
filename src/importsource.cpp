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

void ImportSource::removeModel()
{
    mPimpl->mModel.reset();
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

} // namespace libcellml
