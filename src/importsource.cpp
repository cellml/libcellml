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

namespace libcellml {

/**
 * @brief The ImportSource::ImportSourceImpl struct.
 *
 * The private implementation for the ImportSource class.
 */
struct ImportSource::ImportSourceImpl
{
    std::string mSource;
};

ImportSource::ImportSource()
    : mPimpl(new ImportSourceImpl())
{
}

ImportSource::~ImportSource()
{
    delete mPimpl;
}

ImportSource::ImportSource(const ImportSource& rhs)
    : Entity(rhs)
    , mPimpl(new ImportSourceImpl())
{
    mPimpl->mSource = rhs.mPimpl->mSource;
}

ImportSource::ImportSource(ImportSource &&rhs)
    : Entity(std::move(rhs))
    , mPimpl(rhs.mPimpl)
{
    rhs.mPimpl = nullptr;
}

ImportSource& ImportSource::operator=(ImportSource e)
{
    Entity::operator= (e);
    e.swap(*this);
    return *this;
}

void ImportSource::swap(ImportSource &rhs)
{
    std::swap(this->mPimpl, rhs.mPimpl);
}

void ImportSource::setSource(const std::string &source)
{
    mPimpl->mSource = source;
}

std::string ImportSource::getSource() const
{
    return mPimpl->mSource;
}

}
