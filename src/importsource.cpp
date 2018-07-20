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
#include "libcellml/model.h"

namespace libcellml {

/**
 * @brief The ImportSource::ImportSourceImpl struct.
 *
 * The private implementation for the ImportSource class.
 */
struct ImportSource::ImportSourceImpl
{
    std::string mUrl;
    libcellml::ModelPtr mModel;
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

ImportSource::ImportSource(const ImportSource& rhs)
    : Entity(rhs)
    , mPimpl(new ImportSourceImpl())
{
    mPimpl->mUrl = rhs.mPimpl->mUrl;
    mPimpl->mModel = rhs.mPimpl->mModel;
}

ImportSource::ImportSource(ImportSource &&rhs)
    : Entity(std::move(rhs))
    , mPimpl(rhs.mPimpl)
{
    rhs.mPimpl = nullptr;
}

ImportSource& ImportSource::operator=(ImportSource rhs)
{
    Entity::operator= (rhs);
    rhs.swap(*this);
    return *this;
}

void ImportSource::swap(ImportSource &rhs)
{
    std::swap(this->mPimpl, rhs.mPimpl);
}

std::string ImportSource::getUrl() const
{
    return mPimpl->mUrl;
}

void ImportSource::setUrl(const std::string &url)
{
    mPimpl->mUrl = url;
}

ModelPtr ImportSource::getModel() const
{
    return mPimpl->mModel;
}

void ImportSource::setModel(ModelPtr model)
{
    mPimpl->mModel = model;
}

bool ImportSource::hasModel() const
{
    return mPimpl->mModel != nullptr;
}

}
